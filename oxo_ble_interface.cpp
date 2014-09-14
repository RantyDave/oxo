#include "ble_oxo_interface.h"


const static char     DEVICE_NAME[]        = "0x05ECure";
static const uint16_t uuid16_list[]        = {BLE_UUID_OXO_SERVICE};

OxoBle::OxoBle()
{
		init();
	  accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, (uint8_t *)uuid16_list, sizeof(uuid16_list));
    accumulateAdvertisingPayload(GapAdvertisingData::GENERIC_TAG); //appearance
    accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    setAdvertisingInterval(500); /* in multiples of 0.625ms. */
}
