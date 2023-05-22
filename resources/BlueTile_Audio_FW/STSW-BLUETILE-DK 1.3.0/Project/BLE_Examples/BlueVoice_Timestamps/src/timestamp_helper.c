#include "timestamp_helper.h"

uint8_t bluevoice_timestamp_uuid_array[16] = {0x1b,0xc5,0xd5,0xa5,0x02,0x00,0x36,0xac,0xe1,0x11,0x01,0x00,0x00,0x00,0x00,0x48};
static uint16_t TimestampCharHandle, TimestampServiceHandle;
uint16_t currentTime;
uint8_t outBuffTime[2];

void addTimestampCharacteristic(uint16_t serviceHandle) {
	
	TimestampServiceHandle = serviceHandle;
	
	Char_UUID_t timestamp_char_uuid;
	Osal_MemCpy(&timestamp_char_uuid.Char_UUID_128, bluevoice_timestamp_uuid_array, 16);
	
	aci_gatt_add_char(serviceHandle,
											UUID_TYPE_128,
											&timestamp_char_uuid, 2,
											CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 16, 1,
											&TimestampCharHandle);
}

void updateTimestampCharacteristic(void) {
	currentTime = getTimestamp();
	outBuffTime[0] = currentTime;
	outBuffTime[1] = currentTime >> 8;
	aci_gatt_update_char_value(TimestampServiceHandle, TimestampCharHandle, 0, 2, outBuffTime);
}
