#ifndef __BASE_SERIAL_H__
#define __BASE_SERIAL_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BASE_SERIAL_PARAMETER_RESERVED 0

#define LinkedListNode2BaseSerial(instance) \
    BASE2SUB(instance, BaseSerial, base)

struct BaseSerialVtbl;

typedef struct {
    LinkedListNode base;
    const struct BaseSerialVtbl *vtbl;
} BaseSerial;

typedef struct {
    unsigned int _reserved;
} BaseSerialParameter;

typedef struct BaseSerialVtbl {
    size_t (*Read)(
        BaseSerial *self,
        uint8_t *buffer,
        size_t size);

    size_t (*Write)(
        BaseSerial *self,
        const uint8_t *buffer,
        size_t size);
} BaseSerialVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBaseSerial(
    BaseSerial *instance,
    BaseSerialParameter *parameter);

PROTECTED void DestructBaseSerial(
    BaseSerial *instance);

//  Public method(s)
PUBLIC size_t ReadBaseSerial(
    BaseSerial *self,
    uint8_t *buffer,
    size_t size);

PUBLIC size_t WriteBaseSerial(
    BaseSerial *self,
    const uint8_t *buffer,
    size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_SERIAL_H__
