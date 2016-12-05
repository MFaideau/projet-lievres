#include "LoRa.h"
#include "RTC.h"

extern char* receptionData;
extern uint8_t len;
extern uint8_t snr;
extern int8_t rssi;

void setup() {
  Serial.begin(9600);
  setupLoRa();
  setupRTC(2, 2016, 12, 5, 1, 10, 0, 0);
}

// the loop function runs over and over again forever
void loop() {
  startSleeping(5);
  Serial.println("frrr");
  delay(100);
}
