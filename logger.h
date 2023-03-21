#ifndef _LOGGER_H
#define _LOGGER_H
#include <Arduino.h>
#include <DS3231.h>
class Logger {
  private:
    HardwareSerial *_serial;
    DS3231 *_clock;
    void logLine(char*, char*);
  public:
    Logger(HardwareSerial*, DS3231*);
    void logInfo(char*);
    void logError(char*);
    void logDebug(char*);
    void logWarn(char*);
};
#endif