#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#include <stdlib.h>

#include "asn1crt.h"
#include "asn1crt_encoding.h"

//defined in asn1crt.c

flag ByteStream_PutByte(ByteStream* pStrm, byte v) 
{
    if (pStrm->currentByte+1>pStrm->count+1)
        return FALSE;

    pStrm->buf[pStrm->currentByte] = v;
    pStrm->currentByte++;
    return TRUE;
}

byte GetUIntLength(asn1SccUint value) {
    byte ret = 0;
    while(value>0) {
        ret++;
        value>>=8;
    }
    return ret;
}

flag ByteStream_GetByte(ByteStream* pStrm, byte* v)  {
    if (pStrm->currentByte+1>pStrm->count+1)
        return FALSE;
    *v = pStrm->buf[pStrm->currentByte];
    pStrm->currentByte++;
    return TRUE;
}


flag BerEncodeUInt(ByteStream* pByteStrm, asn1SccUint value, int *pErrCode) {
    int i;
    byte curByte=0;
    flag wFlag = FALSE;

    if (value == 0) {
        if (!ByteStream_PutByte(pByteStrm, curByte)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
        return TRUE;
    }

    for (i=WORD_SIZE-1; i>=0; i--) 
    {
        curByte = (byte)((value & ber_aux[i])>>(8*i));
        if (curByte != 0)
            wFlag = TRUE;
        if (wFlag)
            if (!ByteStream_PutByte(pByteStrm, curByte)) {
                *pErrCode = ERR_INSUFFICIENT_DATA;
                return FALSE;
            }
    }
    
    return TRUE;
}

flag BerEncodeUInt2(ByteStream* pByteStrm, asn1SccUint value, int intSize, int *pErrCode) {
    int i;
    byte curByte=0;

    for (i=intSize-1; i>=0; i--)    {
        curByte = (byte)((value & ber_aux[i])>>(8*i));
        if (!ByteStream_PutByte(pByteStrm, curByte)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
    }
    
    return TRUE;
}


flag BerEncodeTag(ByteStream* pByteStrm, BerTag tag, int *pErrCode) {
    return BerEncodeUInt(pByteStrm, tag, pErrCode);
}

flag BerDecodeTag(ByteStream* pByteStrm, BerTag tag, int *pErrCode) {

    int tagSize = 0;
    BerTag tgCopy = tag;
    BerTag PrimitiveBit=0;
    byte curByte=0;
    long currentByteBak = pByteStrm->currentByte;

    while(tgCopy>0) {
        tgCopy>>=8;
        tagSize++;
    }
    PrimitiveBit = (BerTag)(0x20<<((tagSize-1)*8));

    while(tagSize>0) {
        if (!ByteStream_GetByte(pByteStrm, &curByte)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            pByteStrm->currentByte = currentByteBak;
            return FALSE;
        }
        tgCopy<<=8;
        tgCopy|=curByte;
        tagSize--;
    }

    if ( (tag|PrimitiveBit)  != (tgCopy|PrimitiveBit)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        pByteStrm->currentByte = currentByteBak;
        return FALSE;
    }

    return TRUE;
}

flag BerEncodeLengthStart(ByteStream* pByteStrm, int *pErrCode) {
    
    if (!ByteStream_PutByte(pByteStrm, 0x80)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    
    return TRUE;
}
flag BerEncodeLengthEnd(ByteStream* pByteStrm, int *pErrCode) {
    if (!ByteStream_PutByte(pByteStrm, 0x0)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    if (!ByteStream_PutByte(pByteStrm, 0x0)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    
    return TRUE;
}

flag BerDecodeLength(ByteStream* pByteStrm, int* value, int *pErrCode)
{
    byte curByte=0;
    byte lenlen = 0;
    unsigned int ret=0;
    int i;

    if (!ByteStream_GetByte(pByteStrm, &curByte)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }

    if ( (curByte & 0x80) == 0) {
        *value = curByte & 0x7F;
        return TRUE;
    } else {
        lenlen = curByte & 0x7F;
        if (lenlen == 0) {
            *value = -1;
            return TRUE;
        }
    }
    
    for(i=0; i<lenlen; i++) {

        if (!ByteStream_GetByte(pByteStrm, &curByte)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
        ret <<= 8;
        ret |= curByte;
    }
    *value = (int) ret;
    return TRUE;
}

flag BerEncodeLength(ByteStream* pByteStrm, int value, int *pErrCode)
{
    asn1SccUint uv = (asn1SccUint)value;
    unsigned int uv1 = (unsigned int)value;
    byte lenlen=0;

    if (value <= 0x7F) {
        if (!ByteStream_PutByte(pByteStrm, (byte)value)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
        return TRUE;
    }

    while (uv1>0) {
        lenlen++;
        uv1>>=8;
    }
    if (!ByteStream_PutByte(pByteStrm, lenlen|0x80)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    return BerEncodeUInt(pByteStrm, uv, pErrCode);
}

flag BerDecodeTwoZeroes(ByteStream* pByteStrm, int *pErrCode) {

    byte curByte=0;

    if (!ByteStream_GetByte(pByteStrm, &curByte)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    if (curByte != 0){
        *pErrCode = ERR_BER_LENGTH_MISMATCH;
        return FALSE;
    }

    if (!ByteStream_GetByte(pByteStrm, &curByte)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    if (curByte != 0){
        *pErrCode = ERR_BER_LENGTH_MISMATCH;
        return FALSE;
    }
    return TRUE;
}

/*flag BerDecodeByte(ByteStream* pByteStrm, BerTag tag, byte *value, int *pErrCode) {

    int length;
    byte ret=0;
    
    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    if (!BerDecodeLength(pByteStrm, &length, pErrCode)) // just dummy to get rid of length byte
        return FALSE;
    
    if (!ByteStream_GetByte(pByteStrm, &ret)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    
    *value = ret;
    return TRUE;
}

flag BerEncodeByte(ByteStream* pByteStrm, BerTag tag, byte value, int *pErrCode) {
    
    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    if (!ByteStream_PutByte(pByteStrm, 1)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }

    return BerEncodeUInt2(pByteStrm, (asn1SccUint)value, 1, pErrCode);
}*/

flag BerEncodeInteger(ByteStream* pByteStrm, BerTag tag, asn1SccUint value, int *pErrCode) {
    byte length = 0;
    asn1SccUint v;

    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    length = (byte)GetLengthInBytesOfSInt(value);
    
    if (!ByteStream_PutByte(pByteStrm, length)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }

    v = int2uint(value);

    return BerEncodeUInt2(pByteStrm, v, length, pErrCode);
}

flag BerDecodeInteger(ByteStream* pByteStrm, BerTag tag, void *value, int *pErrCode) {

    int length = 0;
    int i;
    asn1SccUint64 ret=0;
    
    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    if (!BerDecodeLength(pByteStrm, &length, pErrCode))
        return FALSE;
    
    for(i=0; i<length; i++) {
        byte curByte;

        if (!ByteStream_GetByte(pByteStrm, &curByte)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
        ret <<= 8;
        ret |= curByte;
    }
    
    if(length == 1) *(uint8_t*)value = (uint8_t)ret;
    else if(length == 2) *(uint16_t*)value = (uint16_t)ret;
    else if(length == 4) *(uint32_t*)value = (uint32_t)ret;
    else *(uint64_t*)value = (uint64_t)ret;
    //*value = uint2int(ret, length);
    return TRUE;
}

flag BerEncodeBoolean(ByteStream* pByteStrm, BerTag tag, flag value, int *pErrCode) {

    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    if (!ByteStream_PutByte(pByteStrm, 1)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }

    if (!ByteStream_PutByte(pByteStrm, value!=0?0xFF:0x0 )) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    return TRUE;
}

flag BerDecodeBoolean(ByteStream* pByteStrm, BerTag tag, flag *value, int *pErrCode) {
    int length=0;
    byte data;

    *value = FALSE;

    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    if (!BerDecodeLength(pByteStrm, &length, pErrCode))
        return FALSE;
    
    if (length != 1) {
        *pErrCode = ERR_BER_LENGTH_MISMATCH;
        return FALSE;
    }
    
    if (!ByteStream_GetByte(pByteStrm, &data)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }

    *value = data;
    
    return TRUE;
}

flag BerEncodeReal(ByteStream* pByteStrm, BerTag tag, asn1Real value, int *pErrCode) {
    union{
        asn1Real realVal;
        asn1RealHex realValHex;
    }u;
    
    u.realVal = value;
    return BerEncodeInteger(pByteStrm, tag, u.realValHex, pErrCode);
    /*byte buf[100];
    ByteStream tmp;
    byte length;
    int i=0;
    
    ByteStream_Init(&tmp, buf, sizeof(buf));
    ByteStream_EncodeReal(&tmp, value);
    length = (byte)ByteStream_GetLength(&tmp);

    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    //if (!ByteStream_PutByte(pByteStrm, length)) {
    //  *pErrCode = ERR_INSUFFICIENT_DATA;
    //  return FALSE;
    //}
    
    for(i=0; i<length; i++) {
        if (!ByteStream_PutByte(pByteStrm, buf[i])) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
    }

    return TRUE;*/
}

flag BerDecodeReal(ByteStream* pByteStrm, BerTag tag, asn1Real *value, int *pErrCode) {
    union{
        asn1Real realVal;
        asn1RealHex realValHex;
    }u;
    
    flag ret = BerDecodeInteger(pByteStrm, tag, &u.realValHex, pErrCode);
    *value = u.realVal;
    return ret;
/*//  int length=0;
//  byte buf[100];
    ByteStream tmp;
//  int i;

    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    //if (!BerDecodeLength(pByteStrm, &length, pErrCode))
    //  return FALSE;

    ByteStream_AttachBuffer(&tmp, &pByteStrm->buf[pByteStrm->currentByte], pByteStrm->count - pByteStrm->currentByte);


    if (!ByteStream_DecodeReal(&tmp, value)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
    }

    pByteStrm->currentByte += (long)ByteStream_GetLength(&tmp);

    return TRUE;*/
         
}

flag BerEncodeIA5String(ByteStream* pByteStrm, BerTag tag, const char* value, int length, int *pErrCode) {
    int i;
    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    if (!BerEncodeLength(pByteStrm, length, pErrCode))
        return FALSE;

    for(i=0; i<length; i++) {
        if (!ByteStream_PutByte(pByteStrm, (byte)value[i])) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
    }

    return TRUE;
}

flag BerDecodeIA5String(ByteStream* pByteStrm, BerTag tag, char* value, int maxLength, int *pErrCode) {
    int i;
    int length=0;
    byte curByte;

    memset(value, 0x0, (size_t)maxLength);

    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    if (!BerDecodeLength(pByteStrm, &length, pErrCode))
        return FALSE;
    

    for(i=0; i<length; i++) {
        if (!ByteStream_GetByte(pByteStrm, &curByte)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
        if (i<maxLength)
            value[i] = (char)curByte;
    }

    return TRUE;

}

#define lenByteStackSize 10
typedef struct{
    asn1SccUint buf[lenByteStackSize];
    uint8_t top;
}lenByteStack_t; 
lenByteStack_t lenByteStack;

void LenByteStackInit()
{
    lenByteStack.top = 0;
}
asn1SccUint LenBytePop()
{
    if(lenByteStack.top == 0) return 0;
    return lenByteStack.buf[--lenByteStack.top];
}
bool LenBytePush(asn1SccUint val)
{
    if(lenByteStack.top == lenByteStackSize) return false;
    lenByteStack.buf[lenByteStack.top++] = val;
    return true;
}

// pop latestbyte and put length value
void BerEncodeHeadPop(ByteStream* pByteStrm) {
    asn1SccUint lenByte = LenBytePop();
    asn1SccUint len = pByteStrm->currentByte - lenByte - 2; // -2 : lenbyte
    // put 2byte length value; <length value size must be changed according to WORD_SIZE>
    pByteStrm->buf[lenByte] = len >> 8;
    pByteStrm->buf[lenByte+1] = len & 0xFF;
}
// push currentbyte
flag BerEncodeHeadPush(ByteStream* pByteStrm, BerTag tag, int *pErrCode) {
    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    ByteStream_PutByte(pByteStrm, 0x82); // 0x82 for 2byte length value
    LenBytePush(pByteStrm->currentByte);
    
    // 2Byte reserve for length value; <reserve byte size must be changed according to WORD_SIZE>
    ByteStream_PutByte(pByteStrm, 0);
    if (!ByteStream_PutByte(pByteStrm, 0)) 
    {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    
    return TRUE;
}

flag BerDecodeHead(ByteStream* pByteStrm, BerTag tag, int *pErrCode) {
    int length=0;

    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    if (!BerDecodeLength(pByteStrm, &length, pErrCode))
        return FALSE;
    
    return TRUE;
}

flag BerEncodeNull(ByteStream* pByteStrm, BerTag tag, int *pErrCode) {
    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    if (!ByteStream_PutByte(pByteStrm, 0)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }
    return TRUE;
}

flag BerDecodeNull(ByteStream* pByteStrm, BerTag tag, int *pErrCode) {
    int length=0;

    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    
    if (!BerDecodeLength(pByteStrm, &length, pErrCode))
        return FALSE;
    
    if (length != 0) {
        *pErrCode = ERR_BER_LENGTH_MISMATCH;
        return FALSE;
    }
    
    return TRUE;
}

flag BerEncodeBitString(ByteStream* pByteStrm, BerTag tag, const byte* value, int bitCount, int *pErrCode) {
    int i;
    int length = bitCount/8;
    int lastByteUnusedBits = 8 - bitCount % 8;
    if (lastByteUnusedBits == 8)
        lastByteUnusedBits = 0;
    if ((bitCount % 8) != 0)
        length++;

    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;

    if (!BerEncodeLength(pByteStrm, length+1, pErrCode))
        return FALSE;

    if (!ByteStream_PutByte(pByteStrm, (byte)lastByteUnusedBits)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }

    for(i=0; i<length; i++) {
        if (!ByteStream_PutByte(pByteStrm, value[i])) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
    }

    return TRUE;

}

flag BerDecodeBitString(ByteStream* pByteStrm, BerTag tag, byte* value, int *bitCount, int maxBitCount, int *pErrCode){

    int i;
    int length;
    byte lastByteUnusedBits, curByte;
    int nbitCnt=0;
    int maxBytesLen = maxBitCount/8;
    if ( (maxBitCount%8) != 0)
        maxBytesLen++;

    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;

    if (!BerDecodeLength(pByteStrm, &length, pErrCode))
        return FALSE;

    if (!ByteStream_GetByte(pByteStrm, &lastByteUnusedBits)) {
        *pErrCode = ERR_INSUFFICIENT_DATA;
        return FALSE;
    }

    for(i=0; i<length-1; i++) {
        if (!ByteStream_GetByte(pByteStrm, &curByte)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
        if (i<maxBytesLen) {
            nbitCnt+=8;
            value[i] = curByte;
        } else {
            lastByteUnusedBits = 0;
        }
    }

    nbitCnt-=lastByteUnusedBits;

    if (bitCount!= NULL)
        *bitCount = nbitCnt;

    return TRUE;

}


flag BerEncodeOctetString(ByteStream* pByteStrm, BerTag tag, const byte* value, int octCount, int *pErrCode) {
    int i;

    if (!BerEncodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    if (!BerEncodeLength(pByteStrm, octCount, pErrCode))
        return FALSE;

    for(i=0; i<octCount; i++) {
        if (!ByteStream_PutByte(pByteStrm, value[i])) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
    }

    return TRUE;
}

flag BerDecodeOctetString(ByteStream* pByteStrm, BerTag tag, byte* value, int *octCount, int maxOctCount, int *pErrCode) {
    int i;
    int length=0;
    byte curByte;

    memset(value, 0x0, (size_t)maxOctCount);

    if (!BerDecodeTag(pByteStrm, tag, pErrCode)) 
        return FALSE;
    if (!BerDecodeLength(pByteStrm, &length, pErrCode))
        return FALSE;
    
    if (octCount != NULL)
        *octCount = length<=maxOctCount?length:maxOctCount;

    for(i=0; i<length; i++) {
        if (!ByteStream_GetByte(pByteStrm, &curByte)) {
            *pErrCode = ERR_INSUFFICIENT_DATA;
            return FALSE;
        }
        if (i<maxOctCount)
            value[i] = curByte;
    }

    return TRUE;
}


flag NextTagMatches(ByteStream* pByteStrm, BerTag tag) {
    long currentByte =  pByteStrm->currentByte;
    int err;

    flag ret = BerDecodeTag(pByteStrm, tag, &err);
    pByteStrm->currentByte = currentByte;
    
    return ret;
}

int GetStrmPos(ByteStream* pByteStrm) {
    return pByteStrm->currentByte;
}


flag LA_Next_Two_Bytes_00(ByteStream* pByteStrm) 
{
    long currentByte =  pByteStrm->currentByte;
    int err;

    flag ret = BerDecodeTwoZeroes(pByteStrm, &err);
    pByteStrm->currentByte = currentByte;
    
    return ret;
}
