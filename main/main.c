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

#include "main.h"

esp_err_t err;
int retry_num = 0;
bool WiFiGotIP = false;
char s[80]; // general purpose string input

static const char *TAG = "MqttHaSensor";

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_id == WIFI_EVENT_STA_START)
    {
        printf("WIFI CONNECTING....\n");
    }
    else if (event_id == WIFI_EVENT_STA_CONNECTED)
    {
        printf("WiFi CONNECTED\n");
    }
    else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        printf("WiFi lost connection\n");
        if (retry_num < 5)
        {
            esp_wifi_connect();
            retry_num++;
            printf("Retrying to Connect...\n");
        }
    }
    else if (event_id == IP_EVENT_STA_GOT_IP)
    {
        WiFiGotIP = true;
        printf("Wifi got IP...\n\n");
    }
}

void wifi_connection()
{
    err = nvs_flash_init();
    if (err != ESP_OK) { printf("Error at nvs_flash_init: %d = %s.\r\n", err, esp_err_to_name(err)); }
    err = esp_netif_init();                                                                    // network interdace initialization
    if (err != ESP_OK) { printf("Error at esp_netif_init: %d = %s.\r\n", err, esp_err_to_name(err)); }
    err = esp_event_loop_create_default();                                                     // responsible for handling and dispatching events
    if (err != ESP_OK) { printf("Error at esp_event_loop_create_default: %d = %s.\r\n", err, esp_err_to_name(err)); }
    esp_netif_create_default_wifi_sta();                                                 // sets up necessary data structs for wifi station interface
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();                     // sets up wifi wifi_init_config struct with default values
    err = esp_wifi_init(&wifi_initiation);                                                     // wifi initialised with dafault wifi_initiation
    if (err != ESP_OK) { printf("Error at esp_wifi_init: %d = %s.\r\n", err, esp_err_to_name(err)); }
    err = esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);  // creating event handler register for wifi
    if (err != ESP_OK) { printf("Error at esp_event_handler_register(WIFI_EVENT: %d = %s.\r\n", err, esp_err_to_name(err)); }
    err = esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL); // creating event handler register for ip event
    if (err != ESP_OK) { printf("Error at esp_event_handler_register(IP_EVENT: %d = %s.\r\n", err, esp_err_to_name(err)); }
    wifi_config_t wifi_configuration = {                                                 // struct wifi_config_t var wifi_configuration
        .sta = {
            // we are sending a const char of ssid and password which we will strcpy in following line so leaving it blank
            .ssid = "",
            .password = ""
        }
    };
    strcpy((char*)wifi_configuration.sta.ssid, config.ssid);    
    strcpy((char*)wifi_configuration.sta.password, config.pass);   
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);  // setting up configs when event ESP_IF_WIFI_STA
    esp_wifi_start();       // start connection with configurations provided in funtion
    esp_wifi_set_mode(WIFI_MODE_STA);   // station mode selected
    esp_wifi_connect(); // connect with saved ssid and pass
    printf( "wifi_init_softap finished. SSID:%s  password:%s", config.ssid, config.pass);
} 

/*
 * @brief Event handler registered to receive MQTT events
 *
 *  This function is called by the MQTT client event loop.
 *
 * @param handler_args user data registered to the event.
 * @param base Event base for the handler(always MQTT Base in this example).
 * @param event_id The id for the received event.
 * @param event_data The data for the event, esp_mqtt_event_handle_t.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    char topic[80];
    char payload[250];
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%" PRIi32 "", base, event_id);

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        sprintf(topic, "homeassistant/sensor/%s", config.Name);
        sprintf(payload, "{ i: 1 }");
        msg_id = esp_mqtt_client_publish(client, topic, payload, 0, 1, 0);
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

static void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .network = {
        },
        .broker.address.uri = config.mqttBrokerUrl,
        .credentials = { 
            .username = config.mqttUsername, 
            .authentication = { 
                .password = config.mqttPassword
            }, 
        },
        .session = {
            .protocol_ver = MQTT_PROTOCOL_V_3_1_1
        },
    };
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

void app_main(void)
{
    bool doBatteryCal = false;

    // GPIO setup
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);

    if (gpio_get_level(BUTTON_PIN) == 0) {
        printf("Button was pushed.\r\n");
        doBatteryCal = true;
    }

    // Initialise the SPIFFS system
    esp_vfs_spiffs_conf_t spiffs_conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true};
    
    err = esp_vfs_spiffs_register(&spiffs_conf);
    if (err != ESP_OK)
    {
        printf("SPIFFS Mount Failed: %s\r\n", esp_err_to_name(err));
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
        printf("               UID: %s, battVCalFactor: %fV\r\n", config.UID, config.battVCalFactor);
        printf("               WiFi SSID: %s, WiFi Password: %s\r\n", config.ssid, config.pass);
        printf("               MQTT URL: %s, Username: %s, Password: %s\r\n", config.mqttBrokerUrl, config.mqttUsername, config.mqttPassword);
    }
    
    // Start WiFi, wait for WiFi to connect and get IP
    wifi_connection();
    int loops = 0;
    while (loops < 10000 && !WiFiGotIP) {
        vTaskDelay(10 / portTICK_PERIOD_MS); // Wait 10 millseconds
    }

    // Start mqtt
    mqtt_app_start();


    // Initialise the SHT20 driver
    err = SHT20_Initialise(SHT20_SCL, SHT20_SDA);
    if (err != ESP_OK) {
        printf ("Error initialising the SHT20 driver: %s.\r\n", esp_err_to_name(err));
    }

    // Read the current temperature from the SHT20
    float temperature = 0.0;
    float humidity = 0.0;
    err = SHT20_TakeReadings(&temperature, &humidity);
    if (err != ESP_OK) {
        printf ("Error reading from the SHT20: %s.\r\n", esp_err_to_name(err));
    } else {
        printf ("The current temperature is %f C and the current humidity is %f %%RH.\r\n", temperature, humidity);
    }

    // Remove the SHT20 driver
    err = SHT20_Remove();
    if (err != ESP_OK) {
        printf ("Error removing the SHT20 driver: %s.\r\n", esp_err_to_name(err));
    }

    // Read the battery voltage
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // Pin 34 -set attenuation tp let us read to about 2.5V at the pin
    esp_adc_cal_characteristics_t adc1_chars;
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);   // 12 bits
    //int adc_value = adc1_get_raw(ADC1_CHANNEL_6);   // Get the raw ADC value
    uint32_t mV = esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC1_CHANNEL_6), &adc1_chars); // convert to volts
    float battVolts =  ((float)mV / 1000.0) * 2.0; // We have a /2 resistive divider from the battery

    // Check if we are in calibration mode
    if (doBatteryCal) {
        float calVal = 0.0;
        printf("Battery voltage from ADC = %fV\r\n", battVolts);
        printf("Please enter the actual measured voltage, no units : ");
        if(getLineInput(s, sizeof(s)) > 0) {
            float val = atof(s);
            calVal = val / battVolts;
        }        
        printf("\r\nThe corrected battery voltage is %fV. Should I save it? (y/n)? ", (float)(battVolts * calVal));
        char c = 'n';
        if (getLineInput(s, 1) > 0) { c = s[0]; }
        if (c == 'y' || c == 'Y') {
            config.battVCalFactor = calVal;
            if (SaveConfiguration() == true) {
                printf("\r\nConfiguration saved successfully.\r\n");
            } else {
                printf("\r\nError saving configuration.\r\n");
            }
        }
    }

    // Final battery voltage measurement
    battVolts = battVolts * config.battVCalFactor;
    if (DEBUG) { printf("Current battery voltage = %.2fV\r\n", battVolts); }

    // All done, unmount partition and disable SPIFFS
    err = esp_vfs_spiffs_unregister(spiffs_conf.partition_label);
    if ( err != ESP_OK) {
        printf("SPIFFS deregistration: Error %d = %s.\r\n", err, esp_err_to_name(err));
    }
    printf("SPIFFS unmounted.\r\n");

    printf("Sleep for 10 seconds to process WiFi connections.\r\n");
    vTaskDelay(10000 / portTICK_PERIOD_MS); 

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
