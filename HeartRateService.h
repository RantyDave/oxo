/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BLE_HEART_RATE_SERVICE_H__
#define __BLE_HEART_RATE_SERVICE_H__

#include "BLEDevice.h"

/* Heart Rate Service */
/* Service:  https://developer.bluetooth.org/gatt/services/Pages/ServiceViewer.aspx?u=org.bluetooth.service.heart_rate.xml */
/* HRM Char: https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.heart_rate_measurement.xml */
/* Location: https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.body_sensor_location.xml */
class HeartRateService {
public:
    enum {
        LOCATION_OTHER = 0,
        LOCATION_CHEST,
        LOCATION_WRIST,
        LOCATION_FINGER,
        LOCATION_HAND,
        LOCATION_EAR_LOBE,
        LOCATION_FOOT,
    };

public:
    HeartRateService(BLEDevice &_ble, uint8_t _hrmCounter, uint8_t _location) :
        ble(_ble),
        bpm(_hrmCounter),
        hrmRate(GattCharacteristic::UUID_HEART_RATE_MEASUREMENT_CHAR, bpm.getPointer(), HeartRateValueBytes::SIZEOF_ARRAY, HeartRateValueBytes::SIZEOF_ARRAY,
                GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY),
        hrmLocation(GattCharacteristic::UUID_BODY_SENSOR_LOCATION_CHAR, (uint8_t *)&_location, sizeof(_location), sizeof(_location),
                    GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ) {

        static bool serviceAdded = false; /* We should only ever need to add the heart rate service once. */
        if (serviceAdded) {
            return;
        }

        GattCharacteristic *hrmChars[] = {&hrmRate, &hrmLocation, };
        GattService         hrmService(GattService::UUID_HEART_RATE_SERVICE, hrmChars, sizeof(hrmChars) / sizeof(GattCharacteristic *));

        ble.addService(hrmService);
        serviceAdded = true;
    }

    void updateHeartRate(uint8_t hrmCounter) {
        if (ble.getGapState().connected) {
            bpm.updateHeartRate(hrmCounter);
            ble.updateCharacteristicValue(hrmRate.getValueAttribute().getHandle(), bpm.getPointer(), HeartRateValueBytes::SIZEOF_ARRAY);
        }
    }

private:
    /* Private internal representation for the bytes used to work with the vaulue of the heart-rate characteristic. */
    struct HeartRateValueBytes {
        static const unsigned SIZEOF_ARRAY = 2;

        HeartRateValueBytes(uint8_t hrmCounter) : beatsPerMinute() {
            updateHeartRate(hrmCounter);
        }

        void updateHeartRate(uint8_t hrmCounter) {
            beatsPerMinute[1] = hrmCounter;
        }

        uint8_t *getPointer(void) {
            return beatsPerMinute;
        }

        const uint8_t *getPointer(void) const {
            return beatsPerMinute;
        }

    private:
        /* First byte = 8-bit values, no extra info, Second byte = uint8_t HRM value */
        /* See --> https://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.heart_rate_measurement.xml */
        uint8_t beatsPerMinute[SIZEOF_ARRAY];
    };

private:
    BLEDevice           &ble;
    HeartRateValueBytes  bpm;
    GattCharacteristic   hrmRate;
    GattCharacteristic   hrmLocation;
};

#endif /* #ifndef __BLE_HEART_RATE_SERVICE_H__*/
