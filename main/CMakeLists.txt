
idf_component_register(SRCS "config.c" "main.c" "utilities.c" "sht20.c"
                       INCLUDE_DIRS "."
                       REQUIRES mqtt 
                                esp_adc 
                                spiffs 
                                esp_driver_gpio 
                                esp_driver_i2c 
                                driver 
                                esp_wifi
                                esp_event
                                nvs_flash)
