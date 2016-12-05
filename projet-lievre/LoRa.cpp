#include "SX1272.h"
#include <SPI.h>

int ADDRESS = 1;
int ADDRESS_RECEIVER = 8;
byte pinRX = 6;
byte pinTX = 5;
byte pinRESET = 7;
char* receptionData;
uint8_t len; 
uint8_t snr; 
int8_t rssi;
void setupLoRa()
{
  pinMode(pinRX, OUTPUT);
  pinMode(pinTX, OUTPUT);
  pinMode(pinRESET, OUTPUT);
  digitalWrite(pinRESET, LOW);
  //digitalWrite(pinRX, HIGH);
  //digitalWrite(pinTX, LOW);
  sx1272.ON();
  sx1272.setMode(10);
  sx1272.setChannel(CH_17_868);
  sx1272.setPower('P');
  sx1272.setRfOutPin(1);
  sx1272.setNodeAddress(ADDRESS);
}

void sendMessage(byte message[]) {
  sx1272.sendPacketTimeout(ADDRESS_RECEIVER, message);
}

bool messageAvailable() {
  sx1272.receivePacket(0, &receptionData, &len, &snr, &rssi);
  return (len != 0);
}

