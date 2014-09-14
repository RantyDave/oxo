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

#include "mbed.h"
#include "ble_oxo_interface.h"

#define NEED_CONSOLE_OUTPUT 1 /* Set this if you need debug messages on the console;
                               * it will have an impact on code-size and power consumption. */

#if NEED_CONSOLE_OUTPUT
Serial  pc(USBTX, USBRX);
#define DEBUG(...) { pc.printf(__VA_ARGS__); }
#else
#define DEBUG(...) /* nothing */
#endif /* #if NEED_CONSOLE_OUTPUT */

OxoBle oxo;

void connectionCallback(Gap::Handle_t handle, const Gap::ConnectionParams_t* params)
{
    DEBUG("Connected with handle %u\n\r", handle);	
}

void disconnectionCallback(Gap::Handle_t handle, Gap::DisconnectionReason_t reason)
{
    DEBUG("Disconnected handle %u!\n\r", handle);
    DEBUG("Restarting the advertising process\n\r");
    oxo.startAdvertising();
}

int main(void)
{
    DEBUG("Initialising the nRF51822\n\r");
	oxo.onConnection(connectionCallback);
    oxo.onDisconnection(disconnectionCallback);
    oxo.startAdvertising();
    while (true) {
        oxo.waitForEvent();
    }
}
