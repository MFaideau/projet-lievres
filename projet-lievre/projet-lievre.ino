#include "LoRa.h"
#include "RTC.h"

extern char* receptionData;
extern uint8_t len; 
extern uint8_t snr; 
extern int8_t rssi;

void setup() {
  setupLoRa();
}

// the loop function runs over and over again forever
void loop() {
  sendMessage("QUENTIN LEVERT N'EST PAS CONTENT");
  delay(100);
}
