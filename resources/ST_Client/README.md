# Client for Linux hosts that connects and reads data from ST devices

To configure:
Edit the constants.py file, adding in the device list the devices you want to connect to. Please notice that there are different type of devices:
 - sensortile: to work with the custom firmware for the ST SensorTile.box
 - bluetile: to work with the custom firmware for the ST BlueTile that streams sensor data
 - bluevoice: to work with the custom firmware for the ST BlueTile that streams compressed audio data

To launch:
sudo python multiple_client_bluepy.py

## Important: BluePy fix
The BluePy library has a little misbehaviour if you want to send data while waiting for notifications. 
To solve that: 
1. Open the file /usr/lib/python3.10/site-packages/bluepy
2. Add on line 374 the following:

elif respType == 'wr'
  continue

3. Modify line 546 as follows:

return 'wr'
