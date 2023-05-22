import array
from collections import deque
import numpy
import struct


timeSyncVar = 0
# Sync Variables - Definition and Initialization
sync_index = struct.pack("h", 0)[0]
sync_predSample = struct.pack("i", 0)[0]
sync_intra_flag = False

# Audio Variables - Definition and Initialization
audio_dataPkt = []
audio_audioPkt = deque()

audio_StepSizeTable = [7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
                       19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
                       50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
                       130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
                       337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
                       876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
                       2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
                       5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
                       15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767]

audio_IndexTable = [-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8]
audio_index = 0
audio_predsample = 0

audio_queue = []
timestamp_queue = []

# --------------------------------------
# SENSORS
# --------------------------------------


def process_raw_data(value, sensor_type, timeSyncVar, lastEpoch, lastTimestamp):
    if sensor_type == 'audfft':
        timestamp = value[0] + (value[1] << 8)
        if timestamp < lastTimestamp:
            # Manage overflow of the timestamp sent from the device
            timestamp = lastEpoch + timestamp + 65536 - lastTimestamp
        else:
            timestamp = lastEpoch + timestamp - lastTimestamp
        frequency = value[2] + (value[3] << 8)
        return str(timestamp) + ',' + str(frequency) + ',' + str(timeSyncVar) + '\n'

    if sensor_type == 'env':
        timestamp = value[0] + (value[1] << 8)
        if timestamp < lastTimestamp:
            # Manage overflow of the timestamp sent from the device
            timestamp = lastEpoch + timestamp + 65536 - lastTimestamp
        else:
            timestamp = lastEpoch + timestamp - lastTimestamp
        pressure = value[2] + (value[3] << 8) + (value[4] << 16) + (value[5] << 24)  # already in Pa
        humidity = value[6] + (value[7] << 8)
        temperature = value[8] + (value[9] << 8)
        temperature = temperature / 10  # conversion in Celsius

        temp_string = (str(timestamp) + ',' + str(temperature) + ',' + str(timeSyncVar) + '\n')
        press_string = (str(timestamp) + ',' + str(pressure) + ',' + str(timeSyncVar) + '\n')
        hum_string = (str(timestamp) + ',' + str(humidity) + ',' + str(timeSyncVar) + '\n')

        return [temp_string, press_string, hum_string]

    if sensor_type == 'imu':
        timestamp = value[0] + (value[1] << 8)
        if timestamp < lastTimestamp:
            # Manage overflow of the timestamp sent from the device
            timestamp = lastEpoch + timestamp + 65536 - lastTimestamp
        else:
            timestamp = lastEpoch + timestamp - lastTimestamp

        accelerationX = value[2] + (value[3] << 8)
        accelerationX = numpy.int16(accelerationX)
        accelerationX = accelerationX / 1000  # Convert from mg to g
        accelerationY = value[4] + (value[5] << 8)
        accelerationY = numpy.int16(accelerationY)
        accelerationY = accelerationY / 1000  # Convert from mg to g
        accelerationZ = value[6] + (value[7] << 8)
        accelerationZ = numpy.int16(accelerationZ)
        accelerationZ = accelerationZ / 1000  # Convert from mg to g

        acc_string = (
            str(timestamp) + ',' + str(accelerationX) + ',' + str(accelerationY) + ',' + str(accelerationZ) + ',' + str(
                timeSyncVar) + '\n')

        gyroscopeX = value[8] + (value[9] << 8)
        gyroscopeX = numpy.int16(gyroscopeX)
        gyroscopeX = gyroscopeX / 1000  # Convert from mdps to dps
        gyroscopeY = value[10] + (value[11] << 8)
        gyroscopeY = numpy.int16(gyroscopeY)
        gyroscopeY = gyroscopeY / 1000  # Convert from mdps to dps
        gyroscopeZ = value[12] + (value[13] << 8)
        gyroscopeZ = numpy.int16(gyroscopeZ)
        gyroscopeZ = gyroscopeZ / 1000  # Convert from mdps to dps

        gyro_string = (str(timestamp) + ',' + str(gyroscopeX) + ',' + str(gyroscopeY) + ',' + str(gyroscopeZ) + ',' + str(
            timeSyncVar) + '\n')

        magnetoX = value[14] + (value[15] << 8)
        magnetoX = numpy.int16(magnetoX)
        magnetoX = magnetoX * 10  # Convert from mG to uT
        magnetoY = value[16] + (value[17] << 8)
        magnetoY = numpy.int16(magnetoY)
        magnetoY = magnetoY * 10  # Convert from mG to uT
        magnetoZ = value[18] + (value[19] << 8)
        magnetoZ = numpy.int16(magnetoZ)
        magnetoZ = magnetoZ * 10  # Convert from mG to uT

        mag_string = (str(timestamp) + ',' + str(magnetoX) + ',' + str(magnetoY) + ',' + str(magnetoZ) + ',' + str(
            timeSyncVar) + '\n')

        return [acc_string, gyro_string, mag_string]

# ---------------------------------------
# AUDIO
# ---------------------------------------


def write_to_file(output_file):
    global timeSyncVar

    while len(audio_queue) > 0 and len(timestamp_queue) > 0:
        got_time = timestamp_queue.pop(0)
        audio = audio_queue.pop(0)
        output_file.write(got_time + ',' + audio + str(timeSyncVar) + '\n')


def audio_decode(code):
    global audio_predsample, sync_predSample, sync_intra_flag, audio_index, sync_index

    if sync_intra_flag:
        audio_predsample = sync_predSample
        audio_index = sync_index
        sync_intra_flag = False

    step = audio_StepSizeTable[audio_index]

    # 2. inverse code into diff
    diffq = step >> 3
    if (code & 4) != 0:
        diffq += step

    if (code & 2) != 0:
        diffq += step >> 1

    if (code & 1) != 0:
        diffq += step >> 2

    # 3. add diff to predicted sample
    if (code & 8) != 0:
        audio_predsample -= diffq

    else:
        audio_predsample += diffq

    # check for overflow
    if audio_predsample > 32767:
        audio_predsample = 32767

    elif audio_predsample < -32768:
        audio_predsample = -32768

    # 4. find new quantizer step size
    audio_index += audio_IndexTable[code]

    # check for overflow
    if audio_index < 0:
        audio_index = 0

    if audio_index > 88:
        audio_index = 88

    # 5. return new speech sample
    return audio_predsample


def process_audio(data, output_file):
    global audio_queue

    if len(data) != 20:
        raise NameError('error: pkt data length wrong')

    for b in data:
        audio_dataPkt.append(audio_decode(b & 0x0F))
        audio_dataPkt.append(audio_decode((b >> 4) & 0x0F))

    audio_audioPkt.append(array.array('h', audio_dataPkt).tobytes())
    tofile_string = ''
    for a in audio_dataPkt:
        tofile_string = tofile_string + str(a) + ','
    audio_queue.append(tofile_string)
    audio_dataPkt.clear()

    write_to_file(output_file)


def process_timestamp(data, output_file, time_sync, lastEpoch, lastTimestamp):
    global timestamp_queue, timeSyncVar

    timeSyncVar = time_sync
    timestamp = data[0] + (data[1] << 8)
    if timestamp < lastTimestamp:
        # Manage overflow of the timestamp sent from the device
        timestamp = lastEpoch + timestamp + 65536 - lastTimestamp
    else:
        timestamp = lastEpoch + timestamp - lastTimestamp
    timestamp_queue.append(str(timestamp))

    write_to_file(output_file)


def process_sync_variables(data):
    global sync_index, sync_predSample, sync_intra_flag

    if len(data) != 6:
        raise NameError('error')

    sync_index = struct.unpack("h", data[0:2])[0]
    sync_predSample = struct.unpack("i", data[2:6])[0]
    sync_intra_flag = True
