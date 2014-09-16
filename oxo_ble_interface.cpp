#include "ble_oxo_interface.h"
#include "mbed_assert.h"


#define BLE_UUID_OXO_SERVICE 0x2AFF
#define BLE_UUID_OXO_AK 0x2AEE

const static char DEVICE_NAME[]= "0x05ECure";

OxoBle::OxoBle()
{
	init();
	
	//setup the advertising
	accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    accumulateAdvertisingPayload(GapAdvertisingData::GENERIC_TAG); //appearance
    accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    setAdvertisingInterval(1000); /* in multiples of 0.625ms. */
	
	//services and characteristics themselves
	GattCharacteristic ak((UUID)BLE_UUID_OXO_AK, in_buffer, 4, 4, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE);
	GattCharacteristic* chars[]={&ak};
	GattService svc(BLE_UUID_OXO_SERVICE, chars, 1);
	ble_error_e err=addService(svc);
	MBED_ASSERT(err==BLE_ERROR_NONE);
}
