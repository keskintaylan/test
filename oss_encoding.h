#ifndef OSS_ENCODING_H_
#define OSS_ENCODING_H_

#include <stdint.h>
#include <stdbool.h>

#include "oss.h"

#ifdef  __cplusplus
extern "C" {
#endif

flag Rocket_BER_Encode(const Rocket* pVal, ByteStream* pByteStrm, int* pErrCode);
flag Rocket_BER_Decode(Rocket* pVal, ByteStream* pByteStrm, int* pErrCode);
    
#ifdef  __cplusplus
}
#endif

#endif