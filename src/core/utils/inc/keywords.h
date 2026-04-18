#ifndef __KEYWORDS_H__
#define __KEYWORDS_H__

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define PUBLIC
#define PROTECTED
#define PRIVATE static
#define STATIC

#ifdef DEBUG
#define LOOP
#else
#define LOOP for (;;)
#endif // DEBUG

#define CONTAINER_OF(pThis, Type, base) \
    ((Type *)((uint8_t *)(pThis) - offsetof(Type, base)))

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __KEYWORDS_H__
