#ifndef __BASE_SERIAL_H__
#define __BASE_SERIAL_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/event/inc/event_handler.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/ring_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BASE_SERIAL_PARAMETER_RESERVED 0U

#define BASE_SERIAL_EVENT_ARGS_BASE { \
    ._reserved = EVENT_ARGS_RESERVED, \
}

#define EventArgs2BaseSerialEventArgs(pThis) \
    CONTAINER_OF(pThis, BaseSerialEventArgs, base)

struct BaseSerialVtbl;

typedef struct {
    const struct BaseSerialVtbl *vtbl;
} BaseSerial;

typedef struct {
    unsigned int _reserved;
} BaseSerialParameter;

typedef enum {
    BASE_SERIAL_EVENT_DATA_RECEIVED,
} BaseSerialEvent;

typedef struct {
    EventArgs base;
    BaseSerialEvent event;
    RingBuffer *buffer;
} BaseSerialEventArgs;

typedef struct BaseSerialVtbl {
    size_t (*Read)(BaseSerial *, uint8_t *, size_t);
    size_t (*Write)(BaseSerial *, const uint8_t *, size_t);
    void (*SetEventHandler)(BaseSerial *, EventHandler);
} BaseSerialVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void BaseSerial_Construct(
    BaseSerial *pThis,
    BaseSerialParameter *parameter);

PROTECTED void BaseSerial_Destruct(BaseSerial *pThis);

// Public method(s)
PUBLIC size_t BaseSerial_Read(
    BaseSerial *pThis,
    uint8_t *buffer,
    size_t bufferSize);

PUBLIC size_t BaseSerial_Write(
    BaseSerial *pThis,
    const uint8_t *buffer,
    size_t bufferLength);

PUBLIC void BaseSerial_SetEventHandler(BaseSerial *pThis, EventHandler handler);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_SERIAL_H__
