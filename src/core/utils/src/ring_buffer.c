#include "core/utils/inc/ring_buffer.h"

// Private method(s)
PRIVATE bool RingBuffer_FindSequence(
    RingBuffer *pThis,
    size_t offset,
    const uint8_t *sequence,
    size_t sequenceLength);

// Method implement(s)
PUBLIC void RingBuffer_Construct(
    RingBuffer *pThis,
    uint8_t *buffer,
    size_t bufferSize)
{
    if (pThis == NULL || buffer == NULL || bufferSize == 0) {
        return;
    }

    pThis->_buffer = buffer;
    pThis->_bufferSize = bufferSize;
    pThis->_usedLength = 0;

    pThis->_readIndex = 0;
    pThis->_writeIndex = 0;
}

PUBLIC void RingBuffer_Destruct(RingBuffer *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(RingBuffer));
    }
}

PUBLIC size_t RingBuffer_Read(
    RingBuffer *pThis,
    uint8_t *buffer,
    size_t bufferSize)
{
    size_t copyLength = 0;
    size_t rightLength = 0;

    // 1. Check parameters
    if (pThis == NULL || buffer == NULL || bufferSize == 0) {
        return 0;
    }

    // 2. Check buffer status
    if (pThis->_buffer == NULL || pThis->_usedLength == 0) {
        return 0;
    }

    // 3. Calculate copy length
    copyLength = pThis->_usedLength;

    if (bufferSize < copyLength) {
        copyLength = bufferSize;
    }

    // 4. Copy data
    rightLength = pThis->_bufferSize - pThis->_readIndex;

    if (pThis->_writeIndex > pThis->_readIndex || copyLength <= rightLength) {
        memcpy(buffer, pThis->_buffer + pThis->_readIndex, copyLength);
    } else {
        memcpy(buffer, pThis->_buffer + pThis->_readIndex, rightLength);
        memcpy(buffer + rightLength, pThis->_buffer, copyLength - rightLength);
    }

    // 5. Update read index
    pThis->_readIndex = (pThis->_readIndex + copyLength) % pThis->_bufferSize;
    pThis->_usedLength -= copyLength;

    return copyLength;
}

PUBLIC size_t RingBuffer_Write(
    RingBuffer *pThis,
    const uint8_t *buffer,
    size_t bufferLength)
{
    size_t copyLength = 0;
    size_t rightLength = 0;

    // 1. Check parameters
    if (pThis == NULL || buffer == NULL || bufferLength == 0) {
        return 0;
    }

    // 2. Check buffer status
    copyLength = pThis->_bufferSize - pThis->_usedLength;

    if (pThis->_buffer == NULL || copyLength == 0) {
        return 0;
    }

    // 3. Calculate copy length
    if (bufferLength < copyLength) {
        copyLength = bufferLength;
    }

    // 3. Copy data
    rightLength = pThis->_bufferSize - pThis->_writeIndex;

    if (pThis->_readIndex > pThis->_writeIndex || copyLength <= rightLength) {
        memcpy(pThis->_buffer + pThis->_writeIndex, buffer, copyLength);
    } else {
        memcpy(pThis->_buffer + pThis->_writeIndex, buffer, rightLength);
        memcpy(pThis->_buffer, buffer + rightLength, copyLength - rightLength);
    }

    // 4. Update write index
    pThis->_writeIndex = (pThis->_writeIndex + copyLength) % pThis->_bufferSize;
    pThis->_usedLength += copyLength;

    return copyLength;
}

PUBLIC RingBufferPacketResult RingBuffer_FindPacket(
    RingBuffer *pThis,
    RingBufferPacketParameter *parameter)
{
    RingBufferPacketResult result = {
        .invalidLength = 0,
        .packetLength = 0,
    };

    size_t start = pThis->_readIndex;
    size_t end = start + pThis->_usedLength;

    // 1. Check parameters
    if (pThis == NULL || parameter == NULL) {
        return result;
    }

    // 2. Find header
    if (parameter->header != NULL || parameter->headerLength != 0) {
        for (size_t i = start; i < end; i++) {
            if (RingBuffer_FindSequence(
                    pThis,
                    i,
                    parameter->header,
                    parameter->headerLength)) {
                result.invalidLength = i - start;
                break;
            }
        }
    }

    // 3. Find footer
    if (parameter->footer != NULL || parameter->footerLength != 0) {
        for (size_t i = start + result.invalidLength; i < end; i++) {
            if (RingBuffer_FindSequence(
                    pThis,
                    i,
                    parameter->footer,
                    parameter->footerLength)) {
                result.packetLength = i - start - result.invalidLength;
                result.packetLength += parameter->footerLength;
                break;
            }
        }
    }

    return result;
}

PRIVATE bool RingBuffer_FindSequence(
    RingBuffer *pThis,
    size_t offset,
    const uint8_t *sequence,
    size_t sequenceLength)
{
    for (size_t i = 0; i < sequenceLength; i++) {
        if (pThis->_buffer[(offset + i) % pThis->_bufferSize] != sequence[i]) {
            return false;
        }
    }

    return true;
}
