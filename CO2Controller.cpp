#include "CO2Controller.h"

CO2Controller::CO2Controller(int txPin, int rxPin, int co2ValveRelayPin) {
	this->_mhz19 = new MHZ19();
	this->_ticksCount = 0;
	// default serial
	this->_rxPin = rxPin;
	this->_txPin = txPin;
	this->_co2ValveRelayPin = co2ValveRelayPin;
	pinMode(this->_co2ValveRelayPin, OUTPUT);
	this->setDeviceName("CO2Controller");
}

void CO2Controller::init(){
	Serial1.begin(ZH_BAUDRATE, SERIAL_8N1, this->_rxPin, this->_txPin, false, 20000UL); 
	this->_mhz19->begin(Serial1);
	this->_mhz19->autoCalibration(false);
}

void CO2Controller::tick(){
	if (this->_ticksCount % 6000 == 0) { // exerimentally, 100 ticks is like 12 min, so we'll increase it to 12 hours
		this->_mhz19->autoCalibration(false);
		this->logger->logInfo("ABC off command sent. Skipping read this time.");
		this->_ticksCount ++;
		return;
	}
	
	int co2reading = this->_mhz19->getCO2();
	if ( this->logger != NULL ) {
		char buff[64];
		snprintf(buff, sizeof(buff), "Device %s got reading %d", this->getDeviceName(), co2reading);
		this->logger->logInfo(buff);
	}
	if ( this->apiSink != NULL ) {
		char buff[5];
		snprintf(buff, sizeof(buff), "%d", co2reading);
		this->sinkData("co2_reading", buff, this->getDeviceName());
	}
	if ( co2reading >= this->_stopCO2 ) {
		digitalWrite(this->_co2ValveRelayPin, LOW);
		this->sinkData("co2_injection", "off", this->getDeviceName());
	} else if ( co2reading <= this->_startCO2 ) {
		digitalWrite(this->_co2ValveRelayPin, HIGH);
		this->sinkData("co2_injection", "on", this->getDeviceName());
	}
	this->_ticksCount ++;
}

void CO2Controller::setCO2Range(int startCO2, int stopCO2) {
	this->_startCO2 = startCO2;
	this->_stopCO2 = stopCO2;
}