#ifndef _BOARDCONTROLLER_H
#define _BOARDCONTROLLER_H
#include "DeviceController.h"
#include "logger.h"
#include "ApiClient.h"
#define MAX_DEVICES 5
class BoardController {
  private:
    DeviceController *registeredControllers[MAX_DEVICES];
    int currentDeviceCount;
    APIClient *apiSink;
    Logger *logger;
  public:
    BoardController();
    int registerController(DeviceController*);
    void setApiSink(APIClient*);
    void setLogger(Logger*);
    void tick();
};
#endif