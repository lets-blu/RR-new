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

#define BASE2SUB(instance, SubType, baseMember) \
    ((SubType *)((uint8_t *)(instance) - offsetof(SubType, baseMember)))

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __KEYWORDS_H__
