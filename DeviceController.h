#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H
#include "logger.h"
#include "ApiClient.h"

class DeviceController {
  private:
    char *_deviceName;
  public:
    Logger *logger;
    APIClient *apiSink;
    virtual void tick();
    char *getDeviceName();
    void setDeviceName(char*);
    void setLogger(Logger*);
    void setApiSink(APIClient*);
    void sinkData(char*, char*, char*); // char *event_type, char *event_value, cahr* event_location
};
#endif