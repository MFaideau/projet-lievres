#include "LoRa.h"
#include "RTC.h"
#include "Trame.h"

extern char* receptionData;
extern uint8_t len;
extern uint8_t snr;
extern int8_t rssi;

void setup() {
  Serial.begin(9600);
  setupLoRa(6, 5, 7);
  setupRTC(2, 2016, 12, 5, 1, 10, 0, 0);
}

void loop() {
  Date myDate = Date(14, 10, 16, 11, 4, 28);
  Position myPosition = Position(true, false, false, true, 27, 35, 48.32, 72.32, 108.42, 332.332);
  Content myContent = Content(36, &myPosition, &myDate);
  byte* myBytes = CreateMessageBytes(&myContent);
  sendMessage("Bonjour Quentin LEVERT!",32);
  free(myBytes);
  delay(500);
}
