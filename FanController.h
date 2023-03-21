#ifndef _FANCONTROLLER_H
#define _FANCONTROLLER_H
#include "DeviceController.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include "logger.h"
#include "defines.h"

class FanController : public DeviceController {
  private:
    int _fanControlPin;
    float _startTemp;
    float _stopTemp;
    DallasTemperature *_ds18;
    uint8_t *_address;
    uint8_t _lastState;
  public:
    FanController(int, char*);
    void setTemperatureProbe(DallasTemperature *, uint8_t*);
    void setTemperatureRange(float, float);
    void tick();
};

#endif