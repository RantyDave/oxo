//Connecting the oxo security stuff to BLE

#ifndef _BLE_OXO_INTERFACE
#define _BLE_OXO_INTERFACE

#include "BLEDevice.h"

#define BLE_UUID_OXO_SERVICE 0x2AFF

class OxoBle : public BLEDevice
{
	public:
		OxoBle();
	
};

#endif

