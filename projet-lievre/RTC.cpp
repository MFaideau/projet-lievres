#include <Time.h>

// ce programme teste le fonctionnement du RTC
// avec son oscillateur

#include <avr/sleep.h>
//#include <Wire.h>
#include "MCP7940.h"
#include "RTClib.h"

uint8_t mfp;
uint16_t secondes, minutes, heures, jourSem, date, mois, annee;
uint16_t aSecondes, aMinutes, aHeures, aJourSem, aDate, aMois, aAnnee;
MCP7940 rtc(0x6F);

void GetCurrentTime() {
  aSecondes = rtc.bcd2int(rtc.byteRead(RTCSEC) - 128);
  aMinutes = rtc.bcd2int(rtc.byteRead(RTCMIN));
  aHeures = rtc.bcd2int(rtc.byteRead(RTCHOUR));
  aDate = rtc.bcd2int(rtc.byteRead(RTCDATE));
  aJourSem = rtc.bcd2int(rtc.byteRead(RTCWKDAY)) - 20;
  aAnnee = rtc.bcd2int(rtc.byteRead(RTCYEAR)) + 2000;
  aMois = rtc.bcd2int(rtc.byteRead(RTCMTH)) - 20;
}

void wakeup_rtc() {
  //Serial.println("Je me reveille !!");
}

void sleepNow()         // here we put the arduino to sleep
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
  sleep_enable();          // enables the sleep bit in the mcucr register so sleep is possible. just a safety pin
  attachInterrupt(digitalPinToInterrupt(mfp), wakeup_rtc, HIGH);  // use interrupt 0 (pin 2) and run function wakeUpNow when pin 2 gets LOW attachInterrupt(digitalPinToInterrupt(interrupt), interruptFct, LOW);
  sleep_mode();            // here the device is actually put to sleep!! THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
  sleep_disable(); // first thing after waking from sleep: disable sleep...
  detachInterrupt(digitalPinToInterrupt(mfp));      // disables interrupt 0 on pin 2 so the detachInterrupt(digitalPinToInterrupt(interrupt)); wakeUpNow code will not be executed during normal running time.
}

void setupRTC(int mfpPin, int annee, int mois, int date, int jourSem, int heures, int minutes, int secondes) {
  mfp = mfpPin;
  pinMode(mfp, INPUT);

  rtc.byteWrite(RTCSEC, (128 + rtc.int2bcd(secondes)));
  rtc.byteWrite(RTCMIN, rtc.int2bcd(minutes));
  rtc.byteWrite(RTCHOUR, rtc.int2bcd(heures));
  rtc.byteWrite(RTCWKDAY, rtc.int2bcd(jourSem));
  rtc.byteWrite(RTCDATE, rtc.int2bcd(date));
  rtc.byteWrite(RTCMTH, rtc.int2bcd(mois));
  rtc.byteWrite(RTCYEAR, rtc.int2bcd(annee - 2000));
}

void startSleeping(int seconds) {
  GetCurrentTime();
  DateTime now(aAnnee, aMois, aDate, aHeures, aMinutes, aSecondes);
  DateTime futureDate(now.unixtime() + seconds);
  rtc.set_alm0(7, futureDate.second(), futureDate.minute(), futureDate.hour(), futureDate.dayOfTheWeek(), futureDate.day(), futureDate.month());
  sleepNow();
}


