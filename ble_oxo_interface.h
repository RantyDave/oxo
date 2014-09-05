//Connecting the oxo security stuff to BLE

#ifndef _BLE_OXO_INTERFACE
#define _BLE_OXO_INTERFACE

#define BLE_UUID_OXO 0x2AFF

class BLEDevice;

class OxoBle
{
	public:
		OxoBle(BLEDevice*);
	
};

#endif

