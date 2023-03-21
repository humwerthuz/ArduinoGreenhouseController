#include "DeviceController.h"

void DeviceController::setLogger(Logger *logger) {
  this->logger = logger;
}

char* DeviceController::getDeviceName() {
  return this->_deviceName;
}

void DeviceController::setDeviceName(char *name) {
  this->_deviceName = name;
}

void DeviceController::setApiSink(APIClient *sink) {
  this->apiSink = sink;
}

void DeviceController::sinkData(char *eventType, char *eventValue, char *eventLocation) {
  char buff[256];
  snprintf(buff, sizeof(buff), "{\"eventType\":\"%s\", \"eventValue\":\"%s\", \"eventLocation\":\"%s\"}", eventType, eventValue, eventLocation);
  this->apiSink->send(buff);
}