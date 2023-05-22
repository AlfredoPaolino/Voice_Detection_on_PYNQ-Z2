#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "osal.h"
#include "bluenrg1_api.h"
#include "gatt_db.h"
#include "bluenrg1_gatt_server.h"

void addTimestampCharacteristic(uint16_t serviceHandle);
void updateTimestampCharacteristic(void);
