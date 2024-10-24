#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/common/inc/keywords.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct RingBuffer;

typedef enum {
    RING_BUFFER_EVENT_READY_TO_READ
} RingBufferEvent;

typedef struct {
    struct RingBuffer *buffer;
} RingBufferEventParameter;

typedef struct RingBuffer {
    uint8_t *_buffer;
    unsigned int _bufferLength;
    unsigned int _freeLength;

    unsigned int _readIndex;
    unsigned int _writeIndex;

    void (*_callback)(
        RingBufferEvent event,
        RingBufferEventParameter *parameter);
} RingBuffer;

typedef struct {
    const uint8_t *header;
    unsigned int headerLength;
    const uint8_t *footer;
    unsigned int footerLength;
} RingBufferPacketParameter;

typedef struct {
    unsigned int packetLength;
    unsigned int invalidLength;
} RingBufferPacketResult;

typedef void (*RingBufferCallback)(
    RingBufferEvent,
    RingBufferEventParameter *);

// Constructor(s) and Destructor(s)
PUBLIC void ConstructRingBuffer(
    RingBuffer *instance,
    uint8_t *buffer,
    unsigned int bufferLength);

PUBLIC void DestructRingBuffer(
    RingBuffer *instance);

// Public method(s)
PUBLIC unsigned int ReadRingBuffer(
    RingBuffer *self,
    uint8_t *buffer,
    unsigned int bufferLength);

PUBLIC bool WriteRingBuffer(
    RingBuffer *self,
    uint8_t *buffer,
    unsigned int bufferLength);

PUBLIC void SetCallbackToRingBuffer(
    RingBuffer *self,
    RingBufferCallback callback);

PUBLIC RingBufferPacketResult FindPacketInRingBuffer(
    RingBuffer *self,
    RingBufferPacketParameter *parameter);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __RING_BUFFER_H__
