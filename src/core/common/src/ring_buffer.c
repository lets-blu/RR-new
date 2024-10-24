#include "core/common/inc/ring_buffer.h"

// Private method(s)
PRIVATE bool FindSequenceInRingBuffer(
    RingBuffer *self,
    unsigned int offset,
    const uint8_t *sequence,
    unsigned int sequenceLength);

// Method implement(s)
PUBLIC void ConstructRingBuffer(
    RingBuffer *instance,
    uint8_t *buffer,
    unsigned int bufferLength)
{
    if (instance == NULL || buffer == NULL || bufferLength == 0)
    {
        return;
    }

    instance->_buffer = buffer;
    instance->_bufferLength = bufferLength;
    instance->_freeLength = bufferLength;

    instance->_readIndex = 0;
    instance->_writeIndex = 0;

    instance->_callback = NULL;
}

PUBLIC void DestructRingBuffer(
    RingBuffer *instance)
{
    if (instance != NULL)
    {
        memset(instance, 0, sizeof(RingBuffer));
    }
}

PUBLIC unsigned int ReadRingBuffer(
    RingBuffer *self,
    uint8_t *buffer,
    unsigned int bufferLength)
{
    unsigned int copyLength = 0;
    unsigned int rightLength = 0;

    // 1. Check parameters
    if (self == NULL || buffer == NULL || bufferLength == 0)
    {
        return 0;
    }

    // 2. Check buffer status
    if (self->_buffer == NULL || self->_freeLength == self->_bufferLength)
    {
        return 0;
    }

    // 3. Calculate copy length
    copyLength = self->_bufferLength - self->_freeLength;

    if (bufferLength < copyLength)
    {
        copyLength = bufferLength;
    }

    // 4. Copy data
    rightLength = self->_bufferLength - self->_readIndex;

    if (self->_writeIndex > self->_readIndex || copyLength <= rightLength)
    {
        memcpy(buffer, self->_buffer + self->_readIndex, copyLength);
    }
    else
    {
        memcpy(buffer, self->_buffer + self->_readIndex, rightLength);
        memcpy(buffer + rightLength, self->_buffer, copyLength - rightLength);
    }

    // 5. Update read index
    self->_readIndex = (self->_readIndex + copyLength) % self->_bufferLength;
    self->_freeLength += copyLength;

    return copyLength;
}

PUBLIC bool WriteRingBuffer(
    RingBuffer *self,
    uint8_t *buffer,
    unsigned int bufferLength)
{
    unsigned int rightLength = 0;

    RingBufferEventParameter parameter = {
        .buffer = self
    };

    // 1. Check parameters
    if (self == NULL || buffer == NULL || bufferLength == 0)
    {
        return false;
    }

    // 2. Check buffer status
    if (self->_buffer == NULL || self->_freeLength < bufferLength)
    {
        return false;
    }

    // 3. Copy data
    rightLength = self->_bufferLength - self->_writeIndex;

    if (self->_readIndex > self->_writeIndex || bufferLength <= rightLength)
    {
        memcpy(self->_buffer + self->_writeIndex, buffer, bufferLength);
    }
    else
    {
        memcpy(self->_buffer + self->_writeIndex, buffer, rightLength);
        memcpy(self->_buffer, buffer + rightLength, bufferLength - rightLength);
    }

    // 4. Update write index
    self->_writeIndex = (self->_writeIndex + bufferLength) % self->_bufferLength;
    self->_freeLength -= bufferLength;

    // 5. Invoke callback
    if (self->_callback != NULL)
    {
        self->_callback(RING_BUFFER_EVENT_READY_TO_READ, &parameter);
    }

    return true;
}

PUBLIC void SetCallbackToRingBuffer(
    RingBuffer *self,
    RingBufferCallback callback)
{
    if (self != NULL)
    {
        self->_callback = callback;
    }
}

PUBLIC RingBufferPacketResult FindPacketInRingBuffer(
    RingBuffer *self,
    RingBufferPacketParameter *parameter)
{
    RingBufferPacketResult result = {
        .invalidLength = 0,
        .packetLength = 0
    };

    unsigned int start = self->_readIndex;
    unsigned int end = start + self->_bufferLength - self->_freeLength;

    // 1. Check parameters
    if (self == NULL || parameter == NULL)
    {
        return result;
    }

    // 2. Find header
    if (parameter->header != NULL || parameter->headerLength != 0)
    {
        for (unsigned int i = start; i < end; i++)
        {
            if (FindSequenceInRingBuffer(
                    self,
                    i,
                    parameter->header,
                    parameter->headerLength))
            {
                result.invalidLength = i - start;
                break;
            }
        }
    }

    // 3. Find footer
    if (parameter->footer != NULL || parameter->footerLength != 0)
    {
        for (unsigned int i = start + result.invalidLength; i < end; i++)
        {
            if (FindSequenceInRingBuffer(
                    self,
                    i,
                    parameter->footer,
                    parameter->footerLength))
            {
                result.packetLength = i - start - result.invalidLength;
                result.packetLength += parameter->footerLength;
                break;
            }
        }
    }

    return result;
}

PRIVATE bool FindSequenceInRingBuffer(
    RingBuffer *self,
    unsigned int offset,
    const uint8_t *sequence,
    unsigned int sequenceLength)
{
    for (unsigned int i = 0; i < sequenceLength; i++)
    {
        if (self->_buffer[(offset + i) % self->_bufferLength] != sequence[i])
        {
            return false;
        }
    }

    return true;
}
