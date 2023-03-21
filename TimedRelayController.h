#ifndef TIMEDRELAYCONTROLLER_H
#define TIMEDRELAYCONTROLLER_H
#include "DeviceController.h"
#include <DS3231.h>

class TimedRelayController : public DeviceController {
private:
	DS3231 *_clock;
	uint8_t _startHH;
	uint8_t _stopHH;
	uint8_t _startMM;
	uint8_t _stopMM;
	uint8_t _relayPin;
	uint8_t _lastState;
	bool timeInRange(uint8_t, uint8_t);
public:
	TimedRelayController(uint8_t, DS3231*);
	void setStartTime(uint8_t, uint8_t);
	void setStopTime(uint8_t, uint8_t);
	void tick();
};
#endif