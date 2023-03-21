#include "TimedRelayController.h"

TimedRelayController::TimedRelayController(uint8_t relayPin, DS3231 *clock){
	this->_relayPin = relayPin;
	this->_clock = clock;
	this->setDeviceName("TimedRelay");
	pinMode(this->_relayPin, OUTPUT);
	this->_lastState = LOW;
	digitalWrite(this->_relayPin, this->_lastState);
}

void TimedRelayController::setStartTime(uint8_t hh, uint8_t mm) {
	this->_startHH = hh;
	this->_startMM = mm;
}

void TimedRelayController::setStopTime(uint8_t hh, uint8_t mm) {
	this->_stopHH = hh;
	this->_stopMM = mm;
}

//input 13:00
//start: 16:00
//stop: 12:00

//12 <= 13 >= 16 --> false
//12 >= 13 <= 16 --> false

//input 12:00
//12 <= 12 >= 16 --> false
//12 >= 12 <= 16 --> true
bool TimedRelayController::timeInRange(uint8_t hh, uint8_t mm) {
	return ( this->_stopHH <= hh >= this->_startHH && this->_stopMM <= mm >= this->_startMM ) 
	|| ( this->_stopHH >= hh <= this->_startHH && this->_stopMM >= mm <= this->_stopMM );
}

void TimedRelayController::tick(){
	bool is12HMode = false;
	uint8_t nowHH = this->_clock->getHour(is12HMode, is12HMode);
	uint8_t nowMM = this->_clock->getMinute();
	if ( this->logger != NULL ) {
		char buff[64];
		snprintf(buff, sizeof(buff), "Device %s got reading %d:%d", this->getDeviceName(), nowHH, nowMM);
		this->logger->logInfo(buff);
	}
	bool isTimeInRange = this->timeInRange(nowHH, nowMM);
	if ( isTimeInRange && this->_lastState != HIGH ) {
		this->logger->logInfo("turning relay on");
		digitalWrite(this->_relayPin, HIGH);
		this->_lastState = HIGH;
		if ( this->apiSink != NULL ) this->sinkData("relay_event", "on", this->getDeviceName());
	} else if ( !isTimeInRange && this->_lastState != LOW ) {
		this->logger->logInfo("turning relay off");
		digitalWrite(this->_relayPin, LOW);
		this->_lastState = LOW;
		if ( this->apiSink != NULL ) this->sinkData("relay_event", "off", this->getDeviceName());
	}
}