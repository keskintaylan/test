#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include "oss.h"
#include "oss_encoding.h"
//#include "PUS.h"

uint8_t buf_data[500] = {0x30, 0x21, 0x80, 0x02, 0x04, 0xF5, 0x81, 0x06, 0x46, 0x61, 0x6C, 0x63, 0x6F, 0x6E, 0x83, 0x01, 0x00, 0xA4, 0x04, 0x80, 0x02, 0x46, 0x50, 0xA5, 0x0A, 0x0C, 0x03, 0x43, 0x61, 0x72, 0x0C, 0x03, 0x47, 0x50, 0x53};
uint8_t buf[500];
Rocket rocket,rocket2;
Rocket rocketDec;
Armory armory;
Armory armoryDec;
//MySeq mySeq;
int err;
ByteStream byteStream =
{
    .buf = buf,
    .count = sizeof(buf),
    .currentByte = 0,
    .EncodeWhiteSpace = false
};

void main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
  
    while(true)
    {
        ByteStream_Init(&byteStream, buf, sizeof(buf));
        
        // encode/decode Rocket
        { 
            rocket.xrange = 1234;
            strcpy(rocket.name, "Falcon");
            strcpy(rocket.message, "hello");
            rocket.fuel = gas;
            rocket.exist.speed = true;
            rocket.speed.kind = kmph_PRESENT;
            rocket.speed.u.kmph = 18000;
            rocket.payload.nCount = 2;
            strcpy(rocket.payload.arr[0], "Car");
            strcpy(rocket.payload.arr[1], "GPS");

            ByteStream_AttachBuffer(&byteStream, buf, sizeof(buf)); // to init current byte etc...
            Rocket_BER_Encode(&rocket, &byteStream, &err);
            
            ByteStream_AttachBuffer(&byteStream, buf, sizeof(buf)); // to init current byte etc...
            Rocket_BER_Decode(&rocketDec, &byteStream, &err);
        }
        rocket2.xrange = 566;
        strcpy(rocket2.name, "Titan");
        strcpy(rocket2.message, "hi");
        rocket2.fuel = liquid;
        rocket2.exist.speed = true;
        rocket2.speed.kind = mph_PRESENT;
        rocket2.speed.u.kmph = 100;
        rocket2.payload.nCount = 3;
        strcpy(rocket2.payload.arr[0], "Plane");
        strcpy(rocket2.payload.arr[1], "Truck");
        strcpy(rocket2.payload.arr[2], "Moto");
        // encode/decode Armory
        { 
            armory.info.exist.xcoordinate = TRUE,
            armory.info.isExist = TRUE;
            armory.info.xcoordinate.x = 1.2;
            armory.info.xcoordinate.y = 4.8;
            armory.count = 1;
            armory.exist.list = TRUE;
            armory.list.nCount = 2;
            memcpy(&armory.list.arr[0], &rocket, sizeof(rocket));
            memcpy(&armory.list.arr[1], &rocket2, sizeof(rocket));

            ByteStream_AttachBuffer(&byteStream, buf, sizeof(buf)); // to init current byte etc...
            Armory_BER_Encode(&armory, &byteStream, &err);
            
            ByteStream_AttachBuffer(&byteStream, buf, sizeof(buf)); // to init current byte etc...
            Armory_BER_Decode(&armoryDec, &byteStream, &err);
        }
        _NOP();
    }
}
