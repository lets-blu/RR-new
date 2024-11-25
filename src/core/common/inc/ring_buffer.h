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

typedef struct RingBuffer {
    uint8_t *_buffer;
    unsigned int _bufferLength;
    unsigned int _usedLength;

    unsigned int _readIndex;
    unsigned int _writeIndex;
} RingBuffer;

typedef struct {
    const uint8_t *header;
    unsigned int headerLength;
    const uint8_t *footer;
    unsigned int footerLength;
} RingBufferPacketParameter;

typedef struct {
    unsigned int invalidLength;
    unsigned int packetLength;
} RingBufferPacketResult;

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

PUBLIC RingBufferPacketResult FindPacketInRingBuffer(
    RingBuffer *self,
    RingBufferPacketParameter *parameter);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __RING_BUFFER_H__
