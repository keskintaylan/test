#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#include "asn1crt.h"

flag OctetString_equal(int len1, int len2, const byte arr1[], const byte arr2[])
{
	return (len1 == len2) && (memcmp(arr1, arr2, len1) == 0);
}

/***********************************************************************************************/
/*   Byte Stream Functions                                                                      */
/***********************************************************************************************/
void ByteStream_Init(ByteStream* pStrm, byte* buf, long count) 
{
    pStrm->count = count;
    pStrm->buf = buf;
    memset(pStrm->buf,0x0,(size_t)count);
    pStrm->currentByte = 0;
    pStrm->EncodeWhiteSpace = FALSE;
}

void ByteStream_AttachBuffer(ByteStream* pStrm, unsigned char* buf, long count)
{
    pStrm->count = count;
    pStrm->buf = buf;
    pStrm->currentByte = 0;
}

asn1SccSint ByteStream_GetLength(ByteStream* pStrm)
{
    return pStrm->currentByte;
}


/***********************************************************************************************/
/*   Integer Functions                                                                         */
/***********************************************************************************************/

static int GetNumberOfBitsForNonNegativeInteger32(asn1SccUint32 v)
{
	int ret = 0;

	if (v<0x100) {
		ret = 0;
	}
	else if (v<0x10000) {
		ret = 8;
		v >>= 8;
	}
	else if (v<0x1000000) {
		ret = 16;
		v >>= 16;
	}
	else {
		ret = 24;
		v >>= 24;
	}
	while (v>0) {
		v >>= 1;
		ret++;
	}
	return ret;
}

int GetNumberOfBitsForNonNegativeInteger(asn1SccUint v)
{
#if WORD_SIZE==8
	if (v<0x100000000LL)
		return GetNumberOfBitsForNonNegativeInteger32((asn1SccUint32)v);
	else {
		asn1SccUint32 hi = (asn1SccUint32)(v >> 32);
		return 32 + GetNumberOfBitsForNonNegativeInteger32(hi);
	}
#else
	return GetNumberOfBitsForNonNegativeInteger32(v);
#endif
}

int GetLengthInBytesOfUInt(asn1SccUint64 v)
{
	int ret = 0;
	asn1SccUint32 v32 = (asn1SccUint32)v;
#if WORD_SIZE==8
	if (v>0xFFFFFFFF) {
		ret = 4;
		v32 = (asn1SccUint32)(v >> 32);
	}
#endif

	if (v32<0x100)
		return ret + 1;
	if (v32<0x10000)
		return ret + 2;
	if (v32<0x1000000)
		return ret + 3;
	return ret + 4;
}

static int GetLengthSIntHelper(asn1SccUint v)
{
	int ret = 0;
	asn1SccUint32 v32 = (asn1SccUint32)v;
#if WORD_SIZE==8
	if (v>0x7FFFFFFF) {
		ret = 4;
		v32 = (asn1SccUint32)(v >> 32);
	}
#endif

	if (v32 <= 0x7F)
		return ret + 1;
	if (v32 <= 0x7FFF)
		return ret + 2;
	if (v32 <= 0x7FFFFF)
		return ret + 3;
	return ret + 4;
}

int GetLengthInBytesOfSInt(asn1SccSint v)
{
	if (v >= 0)
		return GetLengthSIntHelper((asn1SccUint)v);

	return GetLengthSIntHelper((asn1SccUint)(-v - 1));
}




#ifndef INFINITY
#ifdef __GNUC__
#define INFINITY (__builtin_inf())
#endif
#endif

/*
Bynary encoding will be used
REAL = M*B^E
where
M = S*N*2^F

ENCODING is done within three parts
part 1 is 1 byte header
part 2 is 1 or more byte for exponent
part 3 is 3 or more byte for mantissa (N)

First byte
S :0-->+, S:1-->-1
Base will be always be 2 (implied by 6th and 5th bit which are zero)
ab: F  (0..3)
cd:00 --> 1 byte for exponent as 2's complement
cd:01 --> 2 byte for exponent as 2's complement
cd:10 --> 3 byte for exponent as 2's complement
cd:11 --> 1 byte for encoding the length of the exponent, then the expoent

8 7 6 5 4 3 2 1
+-+-+-+-+-+-+-+-+
|1|S|0|0|a|b|c|d|
+-+-+-+-+-+-+-+-+
*/

#if FP_WORD_SIZE==8

#define ExpoBitMask  0x7FF0000000000000ULL
#define MantBitMask  0x000FFFFFFFFFFFFFULL
#define MantBitMask2 0xFFE0000000000000ULL
#define MantisaExtraBit 0x0010000000000000ULL
#elif FP_WORD_SIZE==4

#define ExpoBitMask  0x7F800000U
#define MantBitMask  0x007FFFFFU
#define MantBitMask2 0xF0000000U
#define MantisaExtraBit 0x00800000U
#else

#define ExpoBitMask  0x7F80U
#define MantBitMask  0x007FU
#define MantBitMask2 0xF000U
#define MantisaExtraBit 0x0080U
#endif


void CalculateMantissaAndExponent(asn1Real d, int* exponent, asn1SccUint64* mantissa)
{

#if FP_WORD_SIZE==8
	union {
		asn1Real in;
		asn1SccUint64 out;
	} double2uint;
	asn1SccUint64 ll = 0;
#elif FP_WORD_SIZE==4
	union {
		asn1Real in;
		asn1SccUint32 out;
	} double2uint;
	asn1SccUint32 ll = 0;
#else
	union {
		asn1Real in;
		asn1SccUint16 out;
	} double2uint;
	asn1SccUint16 ll = 0;
#endif

	double2uint.in = d;
	ll = double2uint.out;

	*exponent = 0;
	*mantissa = 0;

#if FP_WORD_SIZE==8
	* exponent = (int)(((ll & ExpoBitMask) >> 52) - 1023 - 52);
	*mantissa = ll & MantBitMask;
	(*mantissa) |= MantisaExtraBit;
#elif FP_WORD_SIZE==4
	*exponent = (int)(((ll & ExpoBitMask) >> 23) - 127 - 23);

	*mantissa = ll & MantBitMask;
	(*mantissa) |= MantisaExtraBit;
#else
	*exponent = (int)(((ll & ExpoBitMask) >> 10) - 15 - 10);

	*mantissa = ll & MantBitMask;
	(*mantissa) |= MantisaExtraBit;
#endif
}

asn1Real GetDoubleByMantissaAndExp(asn1SccUint mantissa, int exponent)
{
#ifdef USE_LDEXP
	return (asn1Real)ldexp((double)mantissa, exponent);
#else
	asn1Real ret = 1.0;
	if (mantissa == 0)
		return 0.0;

	if (exponent >= 0) {
		while (exponent) {
			ret = ret * 2.0;
			exponent--;
		}
		return (asn1Real)mantissa*ret;
	}
	else {
		exponent = -exponent;
		while (exponent) {
			ret = ret * 2.0;
			exponent--;
		}
		return ((asn1Real)mantissa) / ret;
	}
#endif
}
