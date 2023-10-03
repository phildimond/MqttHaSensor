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

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "sht20.h"

static const char* TAG = "SHT20 Driver";

bool SHT20_Initialised = false;
int i2c_master_port = I2C_NUM_0;

esp_err_t SHT20_Initialise(gpio_num_t sclPin, gpio_num_t sdaPin)
{
    // Initialise the SHT20 Sensor

    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sdaPin, 
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = sclPin, 
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,  // select frequency specific to your project
        // .clk_flags = 0,           // Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here.
    };

    esp_err_t err = i2c_param_config(i2c_master_port, &i2c_conf);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "I2C init failed: Error %d = %s.\r\n", err, esp_err_to_name(err));
        return err;
    }

    err = i2c_driver_install(i2c_master_port, i2c_conf.mode, 0, 0, 0);
    if ( err != ESP_OK) {
        ESP_LOGW(TAG, "I2C driver install failed: Error %d = %s.\r\n", err, esp_err_to_name(err));
        return err;
    }

    SHT20_Initialised = true;
    return ESP_OK;
}

esp_err_t SHT20_TakeReadings(float* temperature, float* humidity)
{
    uint8_t command[1];
    uint8_t rx_data[3];  
    memset(rx_data, 0x00, sizeof(rx_data));

    command[0] = 0xF3;    // Read Temperature, no hold

    esp_err_t err = i2c_master_write_to_device(i2c_master_port, 0x40, command, 1, 10/portTICK_PERIOD_MS);
    if ( err != ESP_OK) {
        ESP_LOGW(TAG, "I2C error sending command: Error %d = %s.\r\n", err, esp_err_to_name(err));
        return err;
    }

    vTaskDelay(200 / portTICK_PERIOD_MS); // Sleep 200ms to allow the device to process the read

    int loops = 0;
    while (true) {
        err = i2c_master_read_from_device(i2c_master_port, 0x40, rx_data, 3, 10/portTICK_PERIOD_MS);
        if (++loops > 5 || err == ESP_OK) { break; }
    }
    if ( err != ESP_OK) {
        ESP_LOGW(TAG, "I2C error reading data: Error %d = %s.\r\n", err, esp_err_to_name(err));
        return err;
    } else {
        uint32_t tval = (rx_data[0] << 8) + (rx_data[1] & 0xFC);
        *temperature = -46.85 + 175.72 * ((float)(tval) / (float)pow(2 , 16));
    }

    command[0] = 0xF5;    // Read Humidity, no hold

    err = i2c_master_write_to_device(i2c_master_port, 0x40, command, 1, 10/portTICK_PERIOD_MS);
    if ( err != ESP_OK) {
        ESP_LOGW(TAG, "I2C error sending command: Error %d = %s.\r\n", err, esp_err_to_name(err));
        return err;
    }

    vTaskDelay(200 / portTICK_PERIOD_MS); // Sleep 200ms to allow the device to process the read

    loops = 0;
    while (true) {
        err = i2c_master_read_from_device(i2c_master_port, 0x40, rx_data, 3, 10/portTICK_PERIOD_MS);
        if (++loops > 5 || err == ESP_OK) { break; }
    }
    if ( err != ESP_OK) {
        ESP_LOGW(TAG, "I2C error reading data: Error %d = %s.\r\n", err, esp_err_to_name(err));
        return err;
    } else {
        uint32_t hval = (rx_data[0] << 8) + (rx_data[1] & 0xFC);
        *humidity = -6.0 + 125.0 * ((float)(hval) / (float)pow(2 , 16));
    }

    return ESP_OK;
}

esp_err_t SHT20_Remove(void)
{
    esp_err_t err = i2c_driver_delete(i2c_master_port);
    if ( err != ESP_OK) {        
        ESP_LOGW(TAG, "I2C driver deletion failed: Error %d = %s.\r\n", err, esp_err_to_name(err));
        return err;
    }

    SHT20_Initialised = false;

    return ESP_OK;
}
