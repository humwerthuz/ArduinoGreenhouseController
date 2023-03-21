#ifndef _MDEFINES
#define _MDEFINES

// PinOut
#define PIN_DS18 13
#define PIN_FAN_RELAY1 4
#define PIN_RTC_SDA 21
#define PIN_RTC_SCL 23

// Old pinout using moded gpio
//#define PIN_MZH19_RX 22
//#define PIN_MZH19_TX 19

// new pinout using rs232 interface
#define PIN_MZH19_RX 16
#define PIN_MZH19_TX 17

#define CO2_RELAY_PIN 5
#define TIMED_RELAY_PIN 15


// Temperature
#define TEMP_PRECISION_9 9
#define TEMP_PRECISION_10 10
#define TEMP_PRECISION_12 12
#define TEMPERATURE_PRECISION TEMP_PRECISION_12
#if TEMPERATURE_PRECISION == TEMP_PRECISION_12
  #define TEMPERATURE_STRING_BYTES 8
#elif TEMPERATURE_PRECISION == TEMP_PRECISION_10
  #define TEMPERATURE_STRING_BYTES 7
#else
  #define TEMPERATURE_STRING_BYTES 6
#endif /* TEMPERATURE_PRECISION == TEMP_PRECISION_12 */


// API
#define API_ENDPOINT "https://snoopie-edge-aclwzeqo.uc.gateway.dev/snoopieEdgeSink"
#endif