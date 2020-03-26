#ifndef ASN1SCC_ASN1CRT_ENCODING_H_
#define ASN1SCC_ASN1CRT_ENCODING_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef  __cplusplus
extern "C" {
#endif

flag OctetString_equal(int len1, int len2, const byte arr1[], const byte arr2[]);

/* Byte stream functions */
void ByteStream_Init(ByteStream* pStrm, byte* buf, long count);
void ByteStream_AttachBuffer(ByteStream* pStrm, unsigned char* buf, long count);
asn1SccSint ByteStream_GetLength(ByteStream* pStrm);

int GetNumberOfBitsForNonNegativeInteger(asn1SccUint v);

void CalculateMantissaAndExponent(asn1Real d, int* exp, asn1SccUint64* mantissa);
asn1Real GetDoubleByMantissaAndExp(asn1SccUint mantissa, int exp);

int GetLengthInBytesOfSInt(asn1SccSint v); 
int GetLengthInBytesOfUInt(asn1SccUint64 v);


#ifdef  __cplusplus
}
#endif

#endif
