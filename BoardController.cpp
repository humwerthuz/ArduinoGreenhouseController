#include "BoardController.h"

BoardController::BoardController() {
  currentDeviceCount = 0;
  apiSink = NULL;
}

int BoardController::registerController(DeviceController *ctrlr) {
  if ( currentDeviceCount >= MAX_DEVICES ) {
    return -1;
  }
  registeredControllers[currentDeviceCount] = ctrlr;

  if (this->apiSink != NULL) {
    registeredControllers[currentDeviceCount]->setApiSink(this->apiSink);
  }

  return ++ currentDeviceCount;
}

void BoardController::tick(){
  char buff[32];
  for(int i = 0; i <= (currentDeviceCount - 1); i++){
    snprintf(buff, sizeof(buff), "ticking device # %d", i);
    logger->logDebug(buff);
    registeredControllers[i]->tick();
  }
}

void BoardController::setLogger(Logger *logger) {
  this->logger = logger;
}

void BoardController::setApiSink(APIClient *sink) {
  this->apiSink = sink;
}