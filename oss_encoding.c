#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "asn1crt.h"
#include "ber.h"
#include "oss.h"


flag Rocket_BER_Encode(const Rocket* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    BerTag tag;

    /* Encode range */
    BerEncodeInteger(pByteStrm, 0x80, pVal->xrange, pErrCode);
    /* Encode name */
    BerEncodeIA5String(pByteStrm, 0x81, pVal->name, strlen(pVal->name), pErrCode);
    /* Encode message */
    BerEncodeIA5String(pByteStrm, 0x82, pVal->message, strlen(pVal->message), pErrCode);
    /* Encode fuel */
    BerDecodeInteger(pByteStrm, 0x83, pVal->fuel, pErrCode);
    /* Encode speed */
    BerEncodeNull(pByteStrm, 0xA4, pErrCode);
    if (pVal->exist.speed) {
        if(pVal->speed.kind == mph_PRESENT)
            BerEncodeInteger(pByteStrm, 0x80, pVal->speed.u.mph, pErrCode);
        else if(pVal->speed.kind == kmph_PRESENT)
            BerEncodeInteger(pByteStrm, 0x81, pVal->speed.u.kmph, pErrCode);
    }
    /* Encode payload */
    BerEncodeNull(pByteStrm, 0xA5, pErrCode);
    int i1;
    for(i1=0; (i1 < pVal->payload.nCount); i1++) 
    {
        BerEncodeIA5String(pByteStrm, 0x16, pVal->payload.arr[i1], strlen(pVal->payload.arr[i1]), pErrCode);
        tag++;
    }

    return ret;
}

flag Rocket_BER_Decode(Rocket* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    BerTag tag;

    /* Decode range */
    BerDecodeInteger(pByteStrm, 0x80, &pVal->xrange, pErrCode);
    /* Decode name */
    BerDecodeIA5String(pByteStrm, 0x81, pVal->name, sizeof(pVal->name), pErrCode);
    /* Decode message */
    BerDecodeIA5String(pByteStrm, 0x82, pVal->message, sizeof(pVal->message), pErrCode);
    /* Decode fuel */
    BerDecodeInteger(pByteStrm, 0x83, (byte*)&pVal->fuel, pErrCode);
    /* Decode speed */
    BerDecodeNull(pByteStrm, 0xA4, pErrCode);
    if(BerDecodeInteger(pByteStrm, 0x80, &pVal->speed.u.mph, pErrCode))
    {
        pVal->exist.speed = TRUE;
        pVal->speed.kind = mph_PRESENT;
    }
    if(BerDecodeInteger(pByteStrm, 0x81, &pVal->speed.u.kmph, pErrCode))
    {
        pVal->exist.speed = TRUE;
        pVal->speed.kind = kmph_PRESENT;
    }
    /* Decode payload */
    BerDecodeNull(pByteStrm, 0xA5, pErrCode);
    int i1;
    for(i1=0; (i1 < sizeof(pVal->payload.arr[0])); i1++) 
    {
        if(BerDecodeIA5String(pByteStrm, 0x16, pVal->payload.arr[i1], sizeof(pVal->payload.arr[0]), pErrCode))
        {
            tag++;
            pVal->payload.nCount++;
        }
        else
        {
            break;
        }
    }

    return ret;
}