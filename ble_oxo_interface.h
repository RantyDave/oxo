//Connecting the oxo security stuff to BLE

#ifndef _BLE_OXO_INTERFACE
#define _BLE_OXO_INTERFACE

#include "BLEDevice.h"


class OxoBle : public BLEDevice
{
public:
	OxoBle();
private:
	uint8_t in_buffer[1024];
};

#endif

