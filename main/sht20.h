/* SHT20 Temp & Humidity Sensor Driver for Home Assistant: configuration
   
   Provides the functionality for communicating with the Sensirion SHT20
   Sensor.

   Copyright 2023 Phillip C Dimond

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#ifndef __SHT20_H__
#define __SHT20_H__

#include "esp_err.h"
#include "driver/gpio.h"

esp_err_t SHT20_Initialise(gpio_num_t sclPin, gpio_num_t sdaPin);
esp_err_t SHT20_ReadTemp(float* tempVal);
esp_err_t SHT20_Remove(void);

#endif // __SHT20_H__

