#ifndef __CONFIG_H
#define __CONFIG_H

#define filename "/spiffs/config.txt"
#define VinPerBitDefault (3.30/2.0)/4095.0   // ADC FS split in two / resolution
#define USER_INPUT_TIMEOUT_MS 60000

typedef struct {
  bool configOK;
  char Name[40];
  char DeviceID[40];
  char UID[80];
  char ssid[40];
  char pass[40];
  char mqttBrokerUrl[160];
  char mqttUsername[40];
  char mqttPassword[160];
  float vinPerBit;
} Configuration;

extern Configuration config;

void SetDefaultConfig(void);
bool LoadConfiguration();
bool SaveConfiguration();
void UserConfigEntry();

#endif // #ifndef __CONFIG_H
