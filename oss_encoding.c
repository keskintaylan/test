#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "asn1crt.h"
#include "ber.h"
#include "oss.h"

#define ARRAY_SIZE(x)   (sizeof(x)/sizeof(x[0]))

flag Rocket_BER_Encode(const Rocket* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    //BerTag tag;

    /* Encode range */
    BerEncodeInteger(pByteStrm, 0x80, pVal->xrange, pErrCode);
    /* Encode name */
    BerEncodeIA5String(pByteStrm, 0x81, pVal->name, strlen(pVal->name), pErrCode);
    /* Encode message */
    BerEncodeIA5String(pByteStrm, 0x82, pVal->message, strlen(pVal->message), pErrCode);
    /* Encode fuel */
    BerEncodeInteger(pByteStrm, 0x83, pVal->fuel, pErrCode);
    /* Encode speed */
    if (pVal->exist.speed) {
        BerEncodeNull(pByteStrm, 0xA4, pErrCode);
        if(pVal->speed.kind == mph_PRESENT)
            BerEncodeInteger(pByteStrm, 0x80, pVal->speed.u.mph, pErrCode);
        else if(pVal->speed.kind == kmph_PRESENT)
            BerEncodeInteger(pByteStrm, 0x81, pVal->speed.u.kmph, pErrCode);
    }
    /* Encode payload */
    BerEncodeNull(pByteStrm, 0xA5, pErrCode);
    int i1;
    for(i1=0; i1 < pVal->payload.nCount; i1++) 
    {
        BerEncodeIA5String(pByteStrm, 0x16, pVal->payload.arr[i1], strlen(pVal->payload.arr[i1]), pErrCode);
    }

    return ret;
}

flag Rocket_BER_Decode(Rocket* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    //BerTag tag;

    /* Decode range */
    ret = BerDecodeInteger(pByteStrm, 0x80, &pVal->xrange, pErrCode);
    if(ret)
    {
        /* Decode name */
        BerDecodeIA5String(pByteStrm, 0x81, pVal->name, sizeof(pVal->name), pErrCode);
        /* Decode message */
        BerDecodeIA5String(pByteStrm, 0x82, pVal->message, sizeof(pVal->message), pErrCode);
        /* Decode fuel */
        BerDecodeInteger(pByteStrm, 0x83, (byte*)&pVal->fuel, pErrCode);
        /* Decode speed */
        if(BerDecodeNull(pByteStrm, 0xA4, pErrCode))
        {
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
        }
        /* Decode payload */
        BerDecodeNull(pByteStrm, 0xA5, pErrCode);
        int i1;
        for(i1=0; i1 < ARRAY_SIZE(pVal->payload.arr); i1++) 
        {
            if(BerDecodeIA5String(pByteStrm, 0x16, pVal->payload.arr[i1], sizeof(pVal->payload.arr[0]), pErrCode))
            {
                pVal->payload.nCount++;
            }
            else
            {
                break;
            }
        }
    }

    return ret;
}

flag Coordinate_BER_Encode(const Coordinate* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    //BerTag tag;
    
    /* Encode x */
    BerEncodeReal(pByteStrm, 0x80, pVal->x, pErrCode);
    /* Encode y */
    BerEncodeReal(pByteStrm, 0x81, pVal->y, pErrCode);
    
    return ret;
}

flag Coordinate_BER_Decode(Coordinate* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    //BerTag tag;
    
    /* Decode x */
    ret = BerDecodeReal(pByteStrm, 0x80, &pVal->x, pErrCode);
    if(ret)
    {
        /* Decode y */
        BerDecodeReal(pByteStrm, 0x81, &pVal->y, pErrCode);
    }
    
    return ret;
}

flag ArmoryInfo_BER_Encode(const ArmoryInfo* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    //BerTag tag;
    
    /* Encode isExist */
    BerEncodeBoolean(pByteStrm, 0x80, pVal->isExist, pErrCode);
    /* Encode coordinate */
    if(pVal->exist.xcoordinate)
    {
        BerEncodeNull(pByteStrm, 0xA1, pErrCode);
        Coordinate_BER_Encode(&pVal->xcoordinate, pByteStrm, pErrCode);
    }
    
    return ret;
}

flag ArmoryInfo_BER_Decode(ArmoryInfo* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    //BerTag tag;
    
    /* Decode isExist */
    ret = BerDecodeBoolean(pByteStrm, 0x80, &pVal->isExist, pErrCode);
    if(ret)
    {
        /* Decode coordinate */
        if(BerDecodeNull(pByteStrm, 0xA1, pErrCode))
        {
            if(Coordinate_BER_Decode(&pVal->xcoordinate, pByteStrm, pErrCode))
            {
                pVal->exist.xcoordinate = TRUE;
            }
        }
    }
    
    return ret;
}

flag Armory_BER_Encode(const Armory* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    //BerTag tag;
    
    /* Encode ArmoryInfo */
    BerEncodeNull(pByteStrm, 0xA0, pErrCode);
    ArmoryInfo_BER_Encode(&pVal->info, pByteStrm, pErrCode);
    /* Encode count */
    BerEncodeInteger(pByteStrm, 0x81, pVal->count, pErrCode);
    /* Encode Sequence of Rocket */
    if(pVal->exist.list)
    {
        BerEncodeNull(pByteStrm, 0xA2, pErrCode);
        int i1;
        for(i1=0; i1 < sizeof(pVal->list.nCount); i1++) 
        {
            Rocket_BER_Encode(&pVal->list.arr[i1], pByteStrm, pErrCode);
        }
    }
    
    return ret;
}

flag Armory_BER_Decode(Armory* pVal, ByteStream* pByteStrm, int* pErrCode)
{
    flag ret = TRUE;
    //BerTag tag;
    
    ret = BerDecodeNull(pByteStrm, 0xA0, pErrCode);
    if(ret)
    {
        /* Decode ArmoryInfo */
        ArmoryInfo_BER_Decode(&pVal->info, pByteStrm, pErrCode);
        /* Decode count */
        BerDecodeInteger(pByteStrm, 0x81, &pVal->count, pErrCode);
        /* Decode Sequence of Rocket */
        if(BerDecodeNull(pByteStrm, 0xA2, pErrCode))
        {
            pVal->exist.list = TRUE;
            int i1;
            for(i1=0; i1 < ARRAY_SIZE(pVal->list.arr); i1++) 
            {
                if(Rocket_BER_Decode(&pVal->list.arr[i1], pByteStrm, pErrCode))
                {
                    pVal->list.nCount++;
                }
                else
                {
                    break;
                }
            }
        }
    }
    return ret;
}