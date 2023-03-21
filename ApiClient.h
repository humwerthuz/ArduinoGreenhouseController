#ifndef APICLIENT_H
#define APICLIENT_H

#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "logger.h"

class APIClient {
	private:
		String _url;
		WiFiClientSecure *_wifiClient;
	public:
		Logger *logger;
		APIClient(String);
		int send(char*);
		void setLogger(Logger*);

};

#endif /* APICLIENT_H */