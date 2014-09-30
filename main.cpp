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
 
 //bits and pieces from mbed
 //  http://mbed.org/platforms/Nordic-nRF51822/
 //  http://mbed.org/teams/Nordic-Semiconductor/code/nRF51822/
 //  http://mbed.org/teams/Bluetooth-Low-Energy/code/BLE_API/
 

#include "mbed.h"
#include "debug.h"
#include "ble_oxo_interface.h"

void connectionCallback(Gap::Handle_t handle, const Gap::ConnectionParams_t* params)
{
    DEBUG("Connected with handle %u, stopping advertising\n", handle);	
	oxo.stopAdvertising();
}

void disconnectionCallback(Gap::Handle_t handle, Gap::DisconnectionReason_t reason)
{
    DEBUG("Disconnected handle %u!\n", handle);
    DEBUG("Restarting the advertising process\n");
    oxo.startAdvertising();
}

int main(void)
{
	DEBUG("Initialising the nRF51822\n");
	oxo.onConnection(connectionCallback);
    oxo.onDisconnection(disconnectionCallback);
    oxo.startAdvertising();
	
	DEBUG("Starting the event loop\n");
    while (true) {
        oxo.waitForEvent();
    }
}
