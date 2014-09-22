#include "debug.h"
#include "ble_oxo_interface.h"
#include "GattServer.h"
#include "app_error.h"

#define BLE_UUID_OXO_SERVICE 0x2AFF

#define BLE_UUID_OXO_APP 0x2AE0
#define BLE_UUID_OXO_PEER 0x2AE1
#define BLE_UUID_OXO_MESSAGE 0x2AE2
#define DEVICE_NAME "0X05ECURE"

#define APP_HANDLE 0
#define PEER_HANDLE 1
#define MESSAGE_HANDLE 2

OxoBle oxo;



void write_callback(uint16_t attribute_handle, const GattCharacteristicWriteCBParams* write_params)
{
	DEBUG("Write to %d offset=%d len=%d data=%x\n", attribute_handle, write_params->offset, write_params->len, write_params->data);
	
	if (attribute_handle==APP_HANDLE) oxo.new_app(write_params);
	if (attribute_handle==PEER_HANDLE) oxo.new_peer(write_params);
	if (attribute_handle==MESSAGE_HANDLE) oxo.incoming_message(write_params);
}

OxoBle::OxoBle()
{
	init();
	
	//setup the advertising
	accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    accumulateAdvertisingPayload(GapAdvertisingData::GENERIC_TAG); //appearance
    accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    setAdvertisingInterval(1000); /* in multiples of 0.625ms. */
	
	//add the service
	GattCharacteristic app((UUID)BLE_UUID_OXO_APP, NULL, 2, 2, 
							GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE);
	GattCharacteristic peer((UUID)BLE_UUID_OXO_PEER, NULL, 32, 32, 
							GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE);
	GattCharacteristic message((UUID)BLE_UUID_OXO_MESSAGE, NULL, 0, 32, 
							GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE | 
							GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_INDICATE);
	GattCharacteristic* chars[]={&app, &peer, &message};
	GattService svc(BLE_UUID_OXO_SERVICE, chars, 3);
	ble_error_e err=addService(svc);
	APP_ERROR_CHECK(err);
	
	//callback when data arrives but hasn't been classified yet
	onDataWritten(write_callback);
}

void OxoBle::new_app(const GattCharacteristicWriteCBParams* write_params)
{
	DEBUG("Switching to a new app.\n");
}

void OxoBle::new_peer(const GattCharacteristicWriteCBParams* write_params)
{
	DEBUG("Switching to a new peer.\n");
}

void OxoBle::incoming_message(const GattCharacteristicWriteCBParams* write_params)
{
	DEBUG("Incoming message (woop woop).\n");
}
