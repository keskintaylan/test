#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include "oss.h"
#include "PUS.h"

uint8_t buf[1000] = {0x30, 0x21, 0x80, 0x02, 0x04, 0xF5, 0x81, 0x06, 0x46, 0x61, 0x6C, 0x63, 0x6F, 0x6E, 0x83, 0x01, 0x00, 0xA4, 0x04, 0x80, 0x02, 0x46, 0x50, 0xA5, 0x0A, 0x0C, 0x03, 0x43, 0x61, 0x72, 0x0C, 0x03, 0x47, 0x50, 0x53};
Rocket rocket;
//MySeq mySeq;
ByteStream byteStream =
{
    .buf = buf,
    .count = sizeof(buf),
    .currentByte = 0,
    .EncodeWhiteSpace = false
};
BitStream bitStream =
{
    .buf = buf,
    .count = sizeof(buf)*8,
    .currentByte = 0,
    .currentBit = 0
};
int err;

void main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
  
    while(true)
    {
        //Rocket_BER_Decode(&rocket, &byteStream, &err);
        //Rocket_ACN_Decode(&rocket, &bitStream, &err);
        // encode
        { 
            rocket.range = 0x04F5;
            strcpy(rocket.name, "Falcon");
            strcpy(rocket.message, "hello");
            rocket.fuel = gas;
            rocket.exist.speed = true;
            rocket.speed.kind = kmph_PRESENT;
            rocket.speed.u.kmph = 18000;
            rocket.payload.nCount = 2;
            strcpy(rocket.payload.arr[0], "Car");
            strcpy(rocket.payload.arr[1], "GPS");

            Rocket_ACN_Encode(&rocket, &bitStream, &err, false);
        }
        //MySeq_ACN_Decode(&mySeq, &bitStream, &err);
        _NOP();
    }
}
