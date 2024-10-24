#include <stdint.h>
#include <string.h>

#include "gtest/gtest.h"
#include "core/common/inc/ring_buffer.h"

#define MAX_BUFFER_LENGTH      (25U)

#define TEST_STRING            ("AT+TEST\r")
#define TEST_STRING_LENGTH     (8U)

#define STRING_HEADER          ("AT")
#define STRING_HEADER_LENGTH   (2U)
#define STRING_FOOTER          ("\r")
#define STRING_FOOTER_LENGTH   (1U)

class RingBufferTest: public testing::Test
{
protected:
    RingBuffer m_ringBuffer;
    uint8_t m_buffer[MAX_BUFFER_LENGTH + 1];

    virtual void SetUp()
    {
        memset(m_buffer, '_', MAX_BUFFER_LENGTH);
        ConstructRingBuffer(&m_ringBuffer, m_buffer, MAX_BUFFER_LENGTH);
    }

    virtual void TearDown()
    {
        DestructRingBuffer(&m_ringBuffer);
        memset(m_buffer, 0, MAX_BUFFER_LENGTH);
    }

    void RunTest(
        uint8_t *invalid,
        unsigned int writeLength,
        unsigned int readLength);
};

TEST_F(RingBufferTest, FindPacket)
{
    uint8_t invalid[MAX_BUFFER_LENGTH + 1] = {0};
    memset(invalid, 'a', MAX_BUFFER_LENGTH);

    // Buffer: aaaAT+TEST$______________
    // Read  : ^
    // Write :            ^
    this->RunTest(invalid, 3, 0);
}

TEST_F(RingBufferTest, FindFragmentedPacket)
{
    uint8_t invalid[MAX_BUFFER_LENGTH + 1] = {0};
    memset(invalid, 'b', MAX_BUFFER_LENGTH);

    // Buffer: ST$_______bbbbbbbbbbAT+TE
    // Read  :           ^
    // Write :    ^
    this->RunTest(invalid, 20, 10);
}

TEST_F(RingBufferTest, FindHeaderFragmentedPacket)
{
    uint8_t invalid[MAX_BUFFER_LENGTH + 1] = {0};
    memset(invalid, 'c', MAX_BUFFER_LENGTH);

    // Buffer: T+TEST$___ccccccccccccccA
    // Read  :           ^
    // Write :        ^
    this->RunTest(invalid, 24, 10);
}

void RingBufferTest::RunTest(
    uint8_t *invalid,
    unsigned int writeLength,
    unsigned int readLength)
{
    uint8_t buffer[MAX_BUFFER_LENGTH + 1] = {0};
    unsigned int difference = writeLength - readLength;

    RingBufferPacketParameter parameter = {
        .header = (const uint8_t *)STRING_HEADER,
        .headerLength = STRING_HEADER_LENGTH,
        .footer = (const uint8_t *)STRING_FOOTER,
        .footerLength = STRING_FOOTER_LENGTH
    };

    RingBufferPacketResult result = {
        .packetLength = 0,
        .invalidLength = 0
    };

    // 1. Write
    // 1.1. Write invalid
    memset(buffer, 0, MAX_BUFFER_LENGTH);

    ASSERT_TRUE(WriteRingBuffer(
            &m_ringBuffer,
            invalid,
            writeLength));

    ASSERT_EQ(readLength, ReadRingBuffer(
            &m_ringBuffer,
            buffer,
            readLength));

    // 1.2. Write packet
    ASSERT_TRUE(WriteRingBuffer(
            &m_ringBuffer,
            (uint8_t *)TEST_STRING,
            TEST_STRING_LENGTH));

    // 2. Find
    result = FindPacketInRingBuffer(&m_ringBuffer, &parameter);

    // 2.1. Read invalid
    memset(buffer, 0, MAX_BUFFER_LENGTH);
    EXPECT_EQ(difference, result.invalidLength);

    EXPECT_EQ(difference, ReadRingBuffer(
            &m_ringBuffer,
            buffer,
            result.invalidLength));

    EXPECT_EQ(0, memcmp(invalid, buffer, difference));

    // 2.2. Read packet
    memset(buffer, 0, MAX_BUFFER_LENGTH);
    EXPECT_EQ(TEST_STRING_LENGTH, result.packetLength);

    EXPECT_EQ(TEST_STRING_LENGTH, ReadRingBuffer(
            &m_ringBuffer,
            buffer,
            result.packetLength));

    EXPECT_STREQ(TEST_STRING, (char *)buffer);
}

