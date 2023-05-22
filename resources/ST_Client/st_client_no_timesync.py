from bluepy import btle
from threading import Thread
import signal
import os
import time
from time import sleep

from constants import devices, services_uuid, characteristics_uuid
from data_processing import process_raw_data, process_sync_variables, process_audio, process_timestamp
from repeated_timer import RepeatedTimer

# REMEMBER TO MODIFY THE BLUEPY LIBRARY BEFORE RUNNING

# Variables for notification waiting
waiting = True
waiting_threads = []
delegates_list = []

# Variables for time sync mechanism
time_sync_var = 0
time_sync_handles = []

# Variable to count % of packet loss
first_packet = [True, True]
lost_packets = [0, 0]
total_packets = [0, 0]
expected_packet = [0, 0]
bluevoice_packets = 0


def update_time_sync():
    global time_sync_var, time_sync_handles, devices

    if waiting:
        output_buffer = time_sync_var.to_bytes(5, 'little')
        for dev in devices:
            dev['handle'].writeCharacteristic(time_sync_handles[devices.index(dev)], output_buffer)
    time_sync_var = time_sync_var + 1


def stop_notifications(signum, frame):
    global waiting
    waiting = False


def wait_for_notifications(device):
    global waiting
    while waiting:
        device.waitForNotifications(5.0)


# The delegate is an object that will take care of all the events received from the device after the connection has
# been completed.
# In this implementation, a delegate is created for each device.
# Every delegate takes care of opening the files relative to the device it's working with, and write inside them.


class MyDelegate(btle.DefaultDelegate):
    def __init__(self, params):
        btle.DefaultDelegate.__init__(self)
        # Device details
        self.deviceNumber = params[0]
        self.deviceName = params[1]
        self.deviceType = params[2]
        # Time synchro details that are updated at each time sync packet.
        self.deviceTimeSync = 0
        self.lastEpoch = time.time_ns() // 1000000
        self.lastTimestamp = 0
        self.time_sync_done = False
        # Notification handles to recognize the data received from the current device
        self.imu_handle = 0
        self.env_handle = 0
        self.bv_aud_handle = 0
        self.bv_sync_handle = 0
        self.bv_time_handle = 0
        self.audlvl_handle = 0
        self.audfft_handle = 0
        self.time_sync_handle = 0
        # File handles for the data received from the current device
        self.acc_file = 0
        self.gyro_file = 0
        self.mag_file = 0
        self.temp_file = 0
        self.press_file = 0
        self.hum_file = 0
        self.audio_file = 0
        self.freq_file = 0
        # Create files and subscribe to notifications
        if self.deviceType == 'bluetile' or self.deviceType == 'sensortile':
            # Open files
            name = "output/acc_" + str(self.deviceNumber) + '.csv'
            os.makedirs(os.path.dirname(name), exist_ok=True)
            self.acc_file = open(name, "w")
            self.acc_file.write("timestamp,valueX,valueY,valueZ,timesync\n")
            name = "output/gyro_" + str(self.deviceNumber) + '.csv'
            self.gyro_file = open(name, "w")
            self.gyro_file.write("timestamp,valueX,valueY,valueZ,timesync\n")
            name = "output/mag_" + str(self.deviceNumber) + '.csv'
            self.mag_file = open(name, "w")
            self.mag_file.write("timestamp,valueX,valueY,valueZ,timesync\n")
            name = "output/temp_" + str(self.deviceNumber) + '.csv'
            self.temp_file = open(name, "w")
            self.temp_file.write("timestamp,temperature,timesync\n")
            name = "output/hum_" + str(self.deviceNumber) + '.csv'
            self.hum_file = open(name, "w")
            self.hum_file.write("timestamp,humidity,timesync\n")
            name = "output/press_" + str(self.deviceNumber) + '.csv'
            self.press_file = open(name, "w")
            self.press_file.write("timestamp,pressure,timesync\n")

        if self.deviceType == 'sensortile':
            name = "output/aud_freq_" + str(self.deviceNumber) + '.csv'
            self.freq_file = open(name, "w")
            self.freq_file.write("timestamp,value,timesync\n")

        if self.deviceType == 'bluevoice':
            name = "output/aud_" + str(self.deviceNumber) + '.csv'
            os.makedirs(os.path.dirname(name), exist_ok=True)
            self.audio_file = open(name, "w")
            self.audio_file.write('timestamp,')
            for j in range(0, 40):
                self.audio_file.write('audio' + str(j) + ',')
            self.audio_file.write('timesync' + '\n')

    def close_files(self):
        if self.acc_file != 0:
            self.acc_file.close()
        if self.gyro_file != 0:
            self.gyro_file.close()
        if self.mag_file != 0:
            self.mag_file.close()
        if self.temp_file != 0:
            self.temp_file.close()
        if self.hum_file != 0:
            self.hum_file.close()
        if self.press_file != 0:
            self.press_file.close()
        if self.audio_file != 0:
            self.audio_file.close()

    def handleNotification(self, cHandle, data):
        global time_sync_var
        global lost_packets, expected_packet, total_packets, first_packet, bluevoice_packets

        # AUDFRQ notifications
        if cHandle == self.audfft_handle:
            self.freq_file.write(
                process_raw_data(data, "audfft", self.deviceTimeSync, self.lastEpoch, self.lastTimestamp))

        # IMU notifications
        if cHandle == self.imu_handle:
            if (not self.time_sync_done) or (data[0] + (data[1] << 8) < 2000):
                self.time_sync_done = True
                self.lastTimestamp = data[0] + (data[1] << 8)
                self.lastEpoch = time.time_ns() // 1000000
            strings_to_write = process_raw_data(data, "imu", self.deviceTimeSync, self.lastEpoch, self.lastTimestamp)
            self.acc_file.write(strings_to_write[0])
            self.gyro_file.write(strings_to_write[1])
            self.mag_file.write(strings_to_write[2])
        # ENV notifications
        if cHandle == self.env_handle and self.time_sync_done:
            strings_to_write = process_raw_data(data, "env", self.deviceTimeSync, self.lastEpoch, self.lastTimestamp)
            self.temp_file.write(strings_to_write[0])
            self.press_file.write(strings_to_write[1])
            self.hum_file.write(strings_to_write[2])
        # BlueVoice notifications
        if cHandle == self.bv_sync_handle and self.time_sync_done:
            process_sync_variables(data)
        if cHandle == self.bv_aud_handle and self.time_sync_done:
            process_audio(data, self.audio_file)
        if cHandle == self.bv_time_handle and self.time_sync_done:
            process_timestamp(data, self.audio_file, self.deviceTimeSync, self.lastEpoch, self.lastTimestamp)
        # Time Sync notifications
        if cHandle == self.time_sync_handle:
            self.lastEpoch = time.time_ns() // 1000000
            self.lastTimestamp = data[0] + (data[1] << 8)
            self.deviceTimeSync = data[2] + (data[3] << 8) + (data[4] << 16) + (data[5] << 24) + (data[6] << 32)


# Initialization  -------


# Define the signal Ctrl+C to stop
signal.signal(signal.SIGINT, stop_notifications)

# Connect
for i in devices:
    print("Connecting to: " + i['name'])
    connected = False
    while not connected:
        try:
            i['handle'] = btle.Peripheral(i['address'], btle.ADDR_TYPE_RANDOM, iface=i['iface'])
        except:
            print("Error trying to connect to " + i['name'] + " - retrying in 2 seconds...")
            print(
                "Verify the device is ON and ready to be paired, that the chosen interface is available and that Bluetooth is ON.")
            sleep(2)
        else:
            connected = True
    d = MyDelegate([devices.index(i), i['name'], i['type']])
    i['handle'].setDelegate(d)
    delegates_list.append(d)

# Subscribe to notifications
for i in devices:
    print("Subscribing to notifications from device " + str(devices.index(i)))
    if i['type'] == 'bluetile':
        # Subscribe to IMU, and save the handle inside the device delegate
        svc = i['handle'].getServiceByUUID(services_uuid['sensors'])
        ch = svc.getCharacteristics(characteristics_uuid['imu'])[0]
        delegates_list[devices.index(i)].imu_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to environmental
        ch = svc.getCharacteristics(characteristics_uuid['env_bt'])[0]
        delegates_list[devices.index(i)].env_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to time sync
        # svc = i['handle'].getServiceByUUID(services_uuid['timesync'])
        # ch = svc.getCharacteristics(characteristics_uuid['timesync'])[0]
        # time_sync_handles.append(ch.valHandle)
        # delegates_list[devices.index(i)].time_sync_handle = ch.valHandle
        # i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
    if i['type'] == 'sensortile':
        # Subscribe to IMU
        svc = i['handle'].getServiceByUUID(services_uuid['sensors'])
        ch = svc.getCharacteristics(characteristics_uuid['imu'])[0]
        delegates_list[devices.index(i)].imu_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to environmental
        ch = svc.getCharacteristics(characteristics_uuid['env_st'])[0]
        delegates_list[devices.index(i)].env_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to audio level
        ch = svc.getCharacteristics(characteristics_uuid['aud_lvl'])[0]
        delegates_list[devices.index(i)].audlvl_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to audio fft
        svc = i['handle'].getServiceByUUID(services_uuid['audio_fft'])
        ch = svc.getCharacteristics(characteristics_uuid['aud_fft'])[0]
        delegates_list[devices.index(i)].audfft_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to time sync
        # svc = i['handle'].getServiceByUUID(services_uuid['timesync'])
        # ch = svc.getCharacteristics(characteristics_uuid['timesync'])[0]
        # time_sync_handles.append(ch.valHandle)
        # delegates_list[devices.index(i)].time_sync_handle = ch.valHandle
        # i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
    if i['type'] == 'bluevoice':
        # Subscribe to bluevoice sync
        svc = i['handle'].getServiceByUUID(services_uuid['sensors'])
        ch = svc.getCharacteristics(characteristics_uuid['bluevoice_sync'])[0]
        delegates_list[devices.index(i)].bv_sync_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to bluevoice audio
        ch = svc.getCharacteristics(characteristics_uuid['bluevoice_aud'])[0]
        delegates_list[devices.index(i)].bv_aud_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to bluevoice timestamps
        ch = svc.getCharacteristics(characteristics_uuid['bluevoice_time'])[0]
        delegates_list[devices.index(i)].bv_time_handle = ch.valHandle
        i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # Subscribe to time sync mechanism
        # svc = i['handle'].getServiceByUUID(services_uuid['timesync'])
        # ch = svc.getCharacteristics(characteristics_uuid['timesync'])[0]
        # time_sync_handles.append(ch.valHandle)
        # i['handle'].writeCharacteristic(ch.valHandle + 1, b"\x01\x00")
        # delegates_list[devices.index(i)].time_sync_handle = ch.valHandle

# Create the timer that will send the synchronization packet
# rt = RepeatedTimer(1, update_time_sync)

print("Everything is ready - Will now read data")

# Create threads to wait for notifications from the devices
for i in devices:
    t = Thread(target=wait_for_notifications, args=(i['handle'],))
    waiting_threads.append(t)
    t.start()

# Wait for the threads to finish (due to timeout or being interrupted by Ctrl+C)
for t in waiting_threads:
    t.join()
# rt.stop()

# Then disconnect, close files and print sum up
for i in devices:
    i['handle'].disconnect()

for d in delegates_list:
    d.close_files()
