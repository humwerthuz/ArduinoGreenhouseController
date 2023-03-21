#include "FanController.h"

FanController::FanController(int fanControllPin, char *name) {
    this->setDeviceName(name);
    this->_fanControlPin = fanControllPin;
    this->_stopTemp = 0;
    this->_startTemp = 0;
    // Ensure pin is in output mode
    pinMode(this->_fanControlPin, OUTPUT);
    // Start off
    this->_lastState = LOW;
    digitalWrite(this->_fanControlPin, this->_lastState);
}

void FanController::setTemperatureRange(float startTemp, float stopTemp) {
  this->_startTemp = startTemp;
  this->_stopTemp = stopTemp;
}

void FanController::tick(){
  this->_ds18->requestTemperaturesByAddress(this->_address);
  delay(1);
  float actualTemp = this->_ds18->getTempC(this->_address);
  if (this->logger != NULL) {
    char buff[64];
    snprintf(buff, sizeof(buff), "Device %s got temperature %f", this->getDeviceName(), actualTemp);
    logger->logInfo(buff);
  }

  if ( this->apiSink != NULL ) {
    char buff[TEMPERATURE_STRING_BYTES];
    snprintf(buff, sizeof(buff), "%f", actualTemp);
    this->sinkData("temp_reading", buff, this->getDeviceName());
  }

  if ( actualTemp >= this->_startTemp && this->_lastState != HIGH) {
    this->_lastState = HIGH;
    digitalWrite(this->_fanControlPin, this->_lastState);
    if ( this->apiSink != NULL ) this->sinkData("fan_event", "on", this->getDeviceName());
  } else if ( actualTemp <= this->_stopTemp && this->_lastState != LOW) {
    this->_lastState = LOW;
    digitalWrite(this->_fanControlPin,  this->_lastState);
    if ( this->apiSink != NULL ) this->sinkData("fan_event", "off", this->getDeviceName());
  }
}

void FanController::setTemperatureProbe(DallasTemperature *ds18, uint8_t *address) {
  this->_ds18 = ds18;
  this->_address = address;
}
