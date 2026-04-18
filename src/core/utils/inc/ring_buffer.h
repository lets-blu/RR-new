#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/utils/inc/keywords.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define RING_BUFFER_IS_CONSTRUCTED(pThis) \
    ((pThis)->_buffer != NULL)

typedef struct {
    uint8_t *_buffer;
    size_t _bufferSize;
    size_t _usedLength;

    size_t _readIndex;
    size_t _writeIndex;
} RingBuffer;

typedef struct {
    const uint8_t *header;
    size_t headerLength;
    const uint8_t *footer;
    size_t footerLength;
} RingBufferPacketParameter;

typedef struct {
    size_t invalidLength;
    size_t packetLength;
} RingBufferPacketResult;

// Constructor(s) and Destructor(s)
PUBLIC void RingBuffer_Construct(
    RingBuffer *pThis,
    uint8_t *buffer,
    size_t bufferSize);

PUBLIC void RingBuffer_Destruct(RingBuffer *pThis);

// Public method(s)
PUBLIC size_t RingBuffer_Read(
    RingBuffer *pThis,
    uint8_t *buffer,
    size_t bufferSize);

PUBLIC size_t RingBuffer_Write(
    RingBuffer *pThis,
    const uint8_t *buffer,
    size_t bufferLength);

PUBLIC RingBufferPacketResult RingBuffer_FindPacket(
    RingBuffer *pThis,
    RingBufferPacketParameter *parameter);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __RING_BUFFER_H__
