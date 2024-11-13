#ifndef __BASE_SERIAL_H__
#define __BASE_SERIAL_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"
#include "core/common/inc/ring_buffer.h"

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
    unsigned int (*Read)(
        BaseSerial *self,
        uint8_t *buffer,
        unsigned int size);

    unsigned int (*Write)(
        BaseSerial *self,
        const uint8_t *buffer,
        unsigned int size);

    void (*SetRxHandler)(
        BaseSerial *self,
        RingBufferEventHandler handler);
} BaseSerialVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBaseSerial(
    BaseSerial *instance,
    BaseSerialParameter *parameter);

PROTECTED void DestructBaseSerial(
    BaseSerial *instance);

//  Public method(s)
PUBLIC unsigned int ReadBaseSerial(
    BaseSerial *self,
    uint8_t *buffer,
    unsigned int size);

PUBLIC unsigned int WriteBaseSerial(
    BaseSerial *self,
    const uint8_t *buffer,
    unsigned int size);

PUBLIC void SetRxHandlerToBaseSerial(
    BaseSerial *self,
    RingBufferEventHandler handler);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_SERIAL_H__
