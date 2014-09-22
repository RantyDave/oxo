//Connecting the oxo security stuff to BLE

#ifndef _BLE_OXO_INTERFACE
#define _BLE_OXO_INTERFACE

#include "BLEDevice.h"

class OxoBle : public BLEDevice
{
friend void write_callback(uint16_t, const GattCharacteristicWriteCBParams*);
public:
	OxoBle();

private:
	uint8_t in_buffer[1024];

	void new_app(const GattCharacteristicWriteCBParams*); //the software using the service
	void new_peer(const GattCharacteristicWriteCBParams*); //the peer the message is apparently from
	void incoming_message(const GattCharacteristicWriteCBParams*);
};

extern OxoBle oxo;

#endif

