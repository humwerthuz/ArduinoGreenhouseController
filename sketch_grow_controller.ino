#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "defines.h"
#include "logger.h"
#include "FanController.h"
#include "BoardController.h"
#include "CO2Controller.h"
#include "TimedRelayController.h"
#include "ApiClient.h"

// Clock
DS3231  rtcClock(Wire);

// Logger
Logger logger = Logger(&Serial, &rtcClock);

// Controllers
BoardController boardController = BoardController();
FanController fan1Control = FanController(PIN_FAN_RELAY1, "Fan1");
CO2Controller co2Control = CO2Controller(PIN_MZH19_TX, PIN_MZH19_RX, CO2_RELAY_PIN);
TimedRelayController timedRelayControl = TimedRelayController(TIMED_RELAY_PIN, &rtcClock);

// Temp Probes
uint8_t TemperatureProbeAddresses[][8] = {
  {0x28, 0x58, 0xB8, 0x14, 0x00, 0x00, 0x00, 0xD6} //28 58 B8 14 00 00 00 D6
};
OneWire ds18Wire(PIN_DS18);
DallasTemperature ds18probes(&ds18Wire);

// Network Stuff
APIClient APIClient(API_ENDPOINT);

void setup(){
  Serial.begin(115200);
  logger.logInfo("board starting");
  Wire.begin(PIN_RTC_SDA, PIN_RTC_SCL);

  //Temp probes
  ds18probes.begin();
  ds18probes.setResolution(TEMPERATURE_PRECISION);
  // do not wait for conversion, actual temperature will be read in next tick
  ds18probes.setWaitForConversion(false);

  //Fan
  fan1Control.setLogger(&logger);
  fan1Control.setTemperatureProbe(&ds18probes, TemperatureProbeAddresses[0]);
  fan1Control.setTemperatureRange(28, 26);

  //CO2
  co2Control.setLogger(&logger);
  co2Control.setCO2Range(950, 1100);
  co2Control.init();

  //LEDs
  timedRelayControl.setLogger(&logger);
  timedRelayControl.setStartTime(16, 00);
  timedRelayControl.setStopTime(12, 00);

  //BoardController
  boardController.setLogger(&logger);
  // First set api sink, so boardcontroller can inject this value into each device
  boardController.setApiSink(&APIClient);
  boardController.registerController(&fan1Control);
  boardController.registerController(&co2Control);
  boardController.registerController(&timedRelayControl);

  // setup network stuff
  WiFi.mode(WIFI_STA);
  WiFi.begin("harc157", "paralelepipedo");

  logger.logInfo("Waiting for WiFi to connect.");
  while ((WiFi.status() != WL_CONNECTED)) {
    Serial.print(".");
  }

  logger.logInfo("Wifi connected");
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  logger.logInfo("boot complete");
}



void loop(){
    boardController.tick();
    delay(1000);
}