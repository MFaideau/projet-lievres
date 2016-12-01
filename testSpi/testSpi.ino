//Choose appropriate module
//#define AlbaTracker
//#define LoraComModule

//REMEMBER to change SS pin in SX1272.h file accordingly
#include "SX1272.h"
#include <SPI.h>

byte readRegister(byte address)
{
  byte value = 0x00;

  digitalWrite(SX1272_SS, LOW);
  bitClear(address, 7);   // Bit 7 cleared to read in registers
  SPI.transfer(address);
  value = SPI.transfer(0x00);
  digitalWrite(SX1272_SS, HIGH);

  return value;
}

void writeRegister(byte address, byte data)
{
  digitalWrite(SX1272_SS, LOW);
  bitSet(address, 7);     // Bit 7 set to write from registers
  SPI.transfer(address);
  SPI.transfer(data);
  //Serial.println(address);
  digitalWrite(SX1272_SS, HIGH);
}

int _reset = 7;


void setup() {
  Serial.begin(9600);
  Serial.println("Test SPI LoRa MBED sans lib\r\n");
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV64);
  SPI.setDataMode(SPI_MODE0);
  pinMode(SX1272_SS, OUTPUT);
  pinMode(_reset, OUTPUT);
  digitalWrite(_reset, LOW);
  delay(100);
  //writeRegister(REG_OP_MODE, FSK_SLEEP_MODE);    // Sleep mode (mandatory to set LoRa mode)
  //writeRegister(REG_OP_MODE, LORA_SLEEP_MODE);    // LoRa sleep mode
  //writeRegister(REG_OP_MODE, FSK_SLEEP_MODE);
  //regfsk();
  //writeRegister(REG_OP_MODE, LORA_SLEEP_MODE);
  //  writeRegister(REG_OP_MODE, LORA_STANDBY_MODE);  // LoRa standby mode
  //  writeRegister(REG_MAX_PAYLOAD_LENGTH,MAX_LENGTH);
  delay(100);
}

void loop() {
 // Serial.println(readRegister(0x42));
  writeRegister(0x02, 0x55);
  bool test1 = readRegister(0x02) == 0x55;
  if(!test1){
    Serial.println("oops1");
  }
  writeRegister(0x02, 0xAA);
 bool test2 = readRegister(0x02) == 0xAA;
   if(!test2){
    Serial.println("oops1");
  }
}





