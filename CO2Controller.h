#ifndef	_CO2_CONTROLLER_H
#define _CO2_CONTROLLER_H

#define ZH_BAUDRATE 9600

#include "DeviceController.h"
#include <MHZ19.h>
#include <HardwareSerial.h>

class CO2Controller : public DeviceController {
private:
	uint8_t _txPin;
	uint8_t _rxPin;
	uint8_t _co2ValveRelayPin;
	uint32_t _ticksCount;
	int _startCO2;
	int _stopCO2;
	MHZ19 *_mhz19;
public:
	CO2Controller(int, int, int);
	void setCO2Range(int, int);
	void init();
	void tick();
};
#endif