#ifndef __FAST_ITOA_H__
#define __FAST_ITOA_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Convert an integer to a string. Returns the number of characters written.
// The string is not null-terminated. Input buffer must be at least 11 bytes.
size_t int2a(int32_t value, char *dest);

// Convert an unsigned integer to a string. Returns the number of characters
// written. The string is not null-terminated. Input buffer must be at least 10 bytes.
size_t uint2a(uint32_t value, char *dest);

#ifdef __cplusplus
}
#endif

#endif
