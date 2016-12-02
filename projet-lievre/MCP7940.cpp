// B.Stefanelli le 10 fev 2016
// Version 1

#include "MCP7940.h"
#include <Wire.h>






/*---------------------------------------------------------------------------------
 Set up MCP7940 device address
		deviceAddr : fixed device address, must be 0x6f
---------------------------------------------------------------------------------*/
MCP7940::MCP7940(uint8_t devAdd) {
  Wire.begin(); 						// join i2c bus as master device
  _deviceAddr = devAdd;						
}

/*---------------------------------------------------------------------------------
 Write data to the MCP7940 registers (byte write)
		reg : any register
		val : data value
---------------------------------------------------------------------------------*/
void MCP7940::byteWrite(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(_deviceAddr);			// begin transmission
  Wire.write(reg);							// select register
  Wire.write(val);							// data to write
  Wire.endTransmission();					// send all bytes, stop issued

}

/*---------------------------------------------------------------------------------
 Read data from any MCP7940 register (random read)
		reg : any register 
		return : data value
---------------------------------------------------------------------------------*/
uint8_t MCP7940::byteRead(uint8_t reg) {

  Wire.beginTransmission(_deviceAddr);			// begin transmission 
  Wire.write(reg);							// select register
  Wire.endTransmission(false);				// send all bytes, restart issued

  Wire.requestFrom(_deviceAddr, (uint8_t)1);   	// request 1 byte from slave device #_deviceAddr, stop issued

  if (Wire.available())   	 					// slave may send less than requested
  { 
    return Wire.read(); 						// get 1 byte
  } 
  else {
	return 0;
  }
}

// *******************************************************************************
// converts an integer into BCD format (integer < 99)
// *******************************************************************************
unsigned int MCP7940::int2bcd(int vale)
{
  return 16 * (vale / 10) + (vale % 10);
}

// *******************************************************************************
// converts a BCD format into an integer (integer < 99)
// *******************************************************************************
unsigned int MCP7940::bcd2int(int vale)
{
  return 10 * (vale / 16) + (vale % 16);
}

void MCP7940::set_alm0(uint8_t match, uint8_t sec, uint8_t minu, uint8_t hr, uint8_t jSem, uint8_t d, uint8_t mth)
// match: 0 -> seconds match // 1 -> minutes match // 2 -> hours match // 3 -> day of week match // 4 -> date match // 5, 6 unused // 7 -> Seconds, Minutes, Hour, Day of Week, Date and Month
{
  byteWrite(CONTROL, 1+2+16/*B0010011*/);
  
  byteWrite(ALM0SEC, int2bcd(sec));
  byteWrite(ALM0MIN, int2bcd(minu));
  byteWrite(ALM0HOUR, int2bcd(hr));
  byteWrite(ALM0WKDAY, 128 + int2bcd(jSem) + (match << 4));	// change MSB for high / low logic input
  byteWrite(ALM0DATE, int2bcd(d));
  byteWrite(ALM0MTH, int2bcd(mth));
}

void MCP7940::set_alm1(uint8_t match, uint8_t sec, uint8_t minu, uint8_t hr, uint8_t jSem, uint8_t d, uint8_t mth)
// match: 0 -> seconds match // 1 -> minutes match // 2 -> hours match // 3 -> day of week match // 4 -> date match // 5, 6 unused // 7 -> Seconds, Minutes, Hour, Day of Week, Date and Month
{
  byteWrite(CONTROL, 1+2+16/*B0010011*/);
  
  byteWrite(ALM1SEC, int2bcd(sec));
  byteWrite(ALM1MIN, int2bcd(minu));
  byteWrite(ALM1HOUR, int2bcd(hr));
  byteWrite(ALM1WKDAY, int2bcd(jSem) + match << 4);
  byteWrite(ALM1DATE, int2bcd(d));
  byteWrite(ALM1MTH, int2bcd(mth));
}
