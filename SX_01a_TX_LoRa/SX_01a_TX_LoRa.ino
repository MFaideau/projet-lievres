/*
    LoRa 868 / 915MHz SX1272 LoRa module

    Copyright (C) Libelium Comunicaciones Distribuidas S.L.
    http://www.libelium.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.

    Version:           1.2
    Design:            David Gascón
    Implementation:    Covadonga Albiñana, Victor Boria, Ruben Martin
*/

//Choose appropriate module
//#define AlbaTracker
#define LoraComModule

//REMEMBER to change SS pin in SX1272.h file accordingly

#include "SX1272.h"
#include <SPI.h>

int e;
char my_packet[100];
char message1 [] = "Au revoir Baudouin";

int ADDRESS = 1;
int ADDRESS_RECEIVER = 8;

#define debug 2 //1 - get packet info, 2 get program debug info

unsigned long int timer = 0;
int delayTime = 10000;
char messageWaiting = 0;
byte pinRX = 6;
byte pinTX = 5;
byte pinRESET = 7;

void setup()
{
  pinMode(pinRX, OUTPUT);
  pinMode(pinTX, OUTPUT);
  pinMode(pinRESET, OUTPUT);
  digitalWrite(pinRESET, LOW);
  //digitalWrite(pinRX, HIGH);
  //digitalWrite(pinTX, LOW);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // Print a start message
  Serial.println(F("SX1272 module and Arduino: send packets without ACK"));

  // Power ON the module
  sx1272.ON();

  // Set transmission mode and print the result
  e = sx1272.setMode(10);
#if (debug > 1)
  Serial.print(F("Setting mode: state "));
  Serial.println(e, DEC);
#endif

  // Select frequency channel
  e = sx1272.setChannel(CH_17_868);
#if (debug > 1)
  Serial.print(F("Setting Channel: state "));
  Serial.println(e, DEC);
#endif

  // Select output power (Max, High or Low)
  e = sx1272.setPower('P');
#if (debug > 1)
  Serial.print(F("Setting Power: state "));
  Serial.println(e);
#endif

  //  // Set value for over current protection (0x1B if 20dBm output power - 0x0B is default!)
  //  e = sx1272.setMaxCurrent(0x1B); // Only set this if 20dBm power is used
  //  #if (debug > 1)
  //  Serial.print(F("Setting Over Current Protection: state "));
  //  Serial.println(e);
  //  #endif

  //Select signal output pin
#if defined(AlbaTracker)
  e = sx1272.setRfOutPin(0);
#endif

#if defined(LoraComModule)
  e = sx1272.setRfOutPin(1);
#endif

#if (debug > 1)
  Serial.print(F("Setting output pin: state "));
  Serial.println(e);
#endif

  // Set the node address and print the result
  e = sx1272.setNodeAddress(ADDRESS);
#if (debug > 1)
  Serial.print(F("Setting node address: state "));
  Serial.println(e, DEC);
#endif

  // Print a success message
#if (debug > 1)
  Serial.println(F("SX1272 successfully configured "));
#endif
}
char* data;
uint8_t len; uint8_t snr; int8_t rssi;
void loop()
{
  sx1272.sendPacketTimeout(ADDRESS_RECEIVER, message1);
}

bool receive() {
  sx1272.receivePacket(0, &data, &len, &snr, &rssi);
  return (len != 0);
}

