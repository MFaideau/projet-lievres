#ifndef MCP7940_h
#define MCP7940_h

#include <inttypes.h>
//#include "Time.h"

#define RTCSEC	0x00
#define RTCMIN	0x01
#define RTCHOUR	0x02
#define RTCWKDAY	0x03
#define RTCDATE	0x04
#define RTCMTH	0x05
#define RTCYEAR	0x06
#define CONTROL	0x07
#define OSCTRIM	0x08

#define ALM0SEC	0x0A
#define ALM0MIN	0x0B
#define ALM0HOUR	0x0C
#define ALM0WKDAY	0x0D
#define ALM0DATE	0x0E
#define ALM0MTH	0x0F

#define ALM1SEC	0x11
#define ALM1MIN	0x12
#define ALM1HOUR	0x13
#define ALM1WKDAY	0x14
#define ALM1DATE	0x15
#define ALM1MTH	0x16

class MCP7940 {
protected:
  uint8_t _deviceAddr;
  
public:
	MCP7940(uint8_t);
	uint8_t byteRead(uint8_t);
	void byteWrite(uint8_t, uint8_t);
	unsigned int bcd2int(int vale);
	unsigned int int2bcd(int vale);
	void set_alm0(uint8_t match, uint8_t sec = 0, uint8_t minu = 0, uint8_t hr = 0, uint8_t jSem = 0, uint8_t d = 0, uint8_t mth = 0);
// match: 0 -> seconds match // 1 -> minutes match // 2 -> hours match // 3 -> day of week match // 4 -> date match // 5, 6 unused // 7 -> Seconds, Minutes, Hour, Day of Week, Date and Month
	void set_alm1(uint8_t match, uint8_t sec = 0, uint8_t minu = 0, uint8_t hr = 0, uint8_t jSem = 0, uint8_t d = 0, uint8_t mth = 0);
// match: 0 -> seconds match // 1 -> minutes match // 2 -> hours match // 3 -> day of week match // 4 -> date match // 5, 6 unused // 7 -> Seconds, Minutes, Hour, Day of Week, Date and Month
};
                                   


#endif
