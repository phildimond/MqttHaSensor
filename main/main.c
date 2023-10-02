/* MQTT Sensor Sender for Home Assistant
   
   Reads a temperature & humidity probe (SHT20, SDA on IO21 and SCL on IO22)
   and sends the data to Home Assistant (or anything else) via MQTT. Hold a 
   button low on IO27 at boot to set the configuration variables. Also sends
   the current battery voltage read from IO34 via a divider network of 
   2 x 1M resistors. Config allows you to calibrate the battery voltage by
   measuring it and entering the real value. Uses a DF Robot Firebeetle 
   ESP32-E board which has the button and battery divider on board, but
   will operate with any ESP32 if properly compiled.

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
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "utilities.h"
#include "config.h"

#define DEBUG 1
#define SLEEPTIME 15
#define BUTTON_PIN  GPIO_NUM_27
#define S_TO_uS(s) (s * 1000000)

// static const char *TAG = "example";

void app_main(void)
{
    // GPIO setup
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    if (gpio_get_level(BUTTON_PIN) == 0) {
        printf("Button was pushed.\r\n");
    }

    // Initialise the SPIFFS system
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true};
    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK)
    {
        printf("SPIFFS Mount Failed: %s\r\n", esp_err_to_name(ret));
        printf("Reformatting the SPIFFs partition, please restart.");
        return;
    }

    // Load the configuration from the file system
    bool configLoad = LoadConfiguration();
    if (configLoad == false || config.configOK == false) // || digitalRead(USER_BUTTON) == LOW)
    {
        if (configLoad == false)
        {
            if (DEBUG)
            {
                printf("Loading the configuration failed. Please enter the configuration details.\r\n");
            }
        }
        else if (config.configOK == false)
        {
            if (DEBUG)
            {
                printf("The stored configuration is marked as invalid. Please enter the configuration details.\r\n");
            }
        }
        UserConfigEntry();
        SaveConfiguration();
    }
    else if (DEBUG)
    {
        printf("Loaded config: configOK: %d, Name: %s, Device ID: %s\r\n", config.configOK, config.Name, config.DeviceID);
        printf("               UID: %s, vinPerBit: %fV\r\n", config.UID, config.vinPerBit);
        printf("               WiFi SSID: %s, WiFi Password: %s\r\n", config.ssid, config.pass);
        printf("               MQTT URL: %s, Username: %s, Password: %s\r\n", config.mqttBrokerUrl, config.mqttUsername, config.mqttPassword);
    }

    // All done, unmount partition and disable SPIFFS
    esp_vfs_spiffs_unregister(conf.partition_label);
    printf("SPIFFS unmounted.\r\n");

    // Go to sleep
    if (DEBUG) { printf("Time to sleep for %d seconds.\r\n", SLEEPTIME); }
    if (esp_sleep_enable_timer_wakeup(S_TO_uS(SLEEPTIME)) != ESP_OK)
    {
        while (true)
        {
            printf ("Error setting sleep time. Value must be out of range.\r\n");
        }
    } 
    esp_deep_sleep_start();

    // If we got here the deep sleep function failed
    while (true)
    {
        printf("Deep sleep initiation failed!\r\n");
        vTaskDelay(250 / portTICK_PERIOD_MS); // 250ms sleep
    } 
}
