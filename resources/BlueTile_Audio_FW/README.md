# Firmware for BlueTile device that has BlueVoice enabled
Provides BlueVoice services (audio + sync), with an added characteristic that is updated with the current timestamp
every time BlueVoice sends audio. It also includes the time synchronization mechanism. 

## How to Build
1. Download the ARM KEIL IDE. If you search "KEIL for BlueNRG", you can find a free activation key provided by ST.
2. Open the project file inside STSW-BLUETILE-DK 1.3.0/Project/BLE_Examples/BlueVoice_Timestamps/MDK-ARM.
3. Clean Project and then Build
4. Inside the Release folder, you will find the compiled firmware. 

## How to Flash
1. Connect the BlueTile to the computer with the provided adapter.
2. Download and open the BlueNRG Flasher Utility from ST.
3. Select the .hex firmware, the board you want to flash, and press Flash.
4. You're ready to go!
