#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include "utils/influx.h"
#include "utils/ota.h"
#include <ArduinoOTA.h>
#include <vector>
#include "secrets.h"

using std::vector; 

OTA ota;
Influx influx;

const char *ssid = STASSID;
const char *password = STAPSK;

int getSoilMoistureValue() {
  return rand() % 10 + 1;
}

int getLightIntensity() {
  return rand() % 50 + 75;
}

void setup()
{
  Sensor soilMoisture("soil_moisture", "wetness", getSoilMoistureValue);
  Sensor lightIntensity("light_intensity", "lumens", getLightIntensity);

  influx.add_sensor(soilMoisture);
  influx.add_sensor(lightIntensity);

  ota.setup_ota(ssid, password);
  influx.setup_influx("ESP8266");
}

void loop()
{
  ota.handle_ota();
  influx.run_influx();
}
