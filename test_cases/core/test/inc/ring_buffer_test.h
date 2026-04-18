#ifndef __RING_BUFFER_TEST_H__
#define __RING_BUFFER_TEST_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "gtest/gtest.h"

#include "core/utils/inc/ring_buffer.h"

#define RING_BUFFER_TEST_BUFFER_SIZE 80U

class RingBufferTest : public testing::Test {
protected:
    uint8_t mBuffer[RING_BUFFER_TEST_BUFFER_SIZE];
    RingBuffer mRingBuffer;

    static const char *COMMAND;
    static const char *COMMAND_HEADER;
    static const char *COMMAND_FOOTER;
    static const size_t COMMAND_LENGTH;

    void SetUp(void);
    void TearDown(void);
    void Write(void);
};

#endif // __RING_BUFFER_TEST_H__
