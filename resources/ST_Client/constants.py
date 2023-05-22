from bluepy import btle

devices = [{'name': 'bluetile_CB_6D', 'type': 'bluetile', 'address': 'F0:8A:E6:C4:CB:6D', 'iface': 3,
           'handle': btle.Peripheral()},
           {'name': 'sensortile_D3_40', 'type': 'sensortile', 'address': 'CF:74:4F:5B:D3:40', 'iface': 2,
           'handle': btle.Peripheral()},
           {'name': 'sensortile_FE_60', 'type': 'sensortile', 'address': 'F6:45:77:69:FE:60', 'iface': 1,
           'handle': btle.Peripheral()},
           {'name': 'bluetile_E6_84', 'type': 'bluevoice', 'address': 'F8:71:17:CE:E6:84', 'iface': 0,
           'handle': btle.Peripheral()}
           ]

services_uuid = {'sensors': '00000000-0001-11e1-9ab4-0002a5d5c51b',
                 'timesync': '00000000-000f-11e1-9ab4-0002a5d5c51b',
                 'audio_fft': '00000000-0002-11e1-9ab4-0002a5d5c51b'}
characteristics_uuid = {'imu': '00e00000-0001-11e1-ac36-0002a5d5c51b',
                        'bluevoice_sync': '40000000-0001-11e1-ac36-0002a5d5c51b',
                        'bluevoice_aud': '08000000-0001-11e1-ac36-0002a5d5c51b',
                        'bluevoice_time': '48000000-0001-11e1-ac36-0002a5d5c51b',
                        'timesync': '00000002-000f-11e1-ac36-0002a5d5c51b',
                        'env_st': '001f0000-0001-11e1-ac36-0002a5d5c51b',
                        'env_bt': '001c0000-0001-11e1-ac36-0002a5d5c51b',
                        'aud_fft': '00040000-0002-11e1-ac36-0002a5d5c51b',
                        'aud_lvl': '04000000-0001-11e1-ac36-0002a5d5c51b'}
