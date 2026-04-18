#include "core/test/inc/ring_buffer_test.h"

// Static member(s)
const char *RingBufferTest::COMMAND = "AT+TEST\r";
const char *RingBufferTest::COMMAND_HEADER = "AT";
const char *RingBufferTest::COMMAND_FOOTER = "\r";
const size_t RingBufferTest::COMMAND_LENGTH = strlen(COMMAND);

// Test case(s)
TEST_F(RingBufferTest, Write)
{
    Write();

    EXPECT_EQ(COMMAND_LENGTH, mRingBuffer._usedLength);
    EXPECT_STREQ(COMMAND, (const char *)mRingBuffer._buffer);

    EXPECT_EQ(0U, mRingBuffer._readIndex);
    EXPECT_EQ(COMMAND_LENGTH, mRingBuffer._writeIndex);
}

TEST_F(RingBufferTest, Read)
{
    size_t bufferLength = 0;
    uint8_t buffer[RING_BUFFER_TEST_BUFFER_SIZE] = {0};

    Write();

    bufferLength = RingBuffer_Read(
        &mRingBuffer,
        buffer,
        RING_BUFFER_TEST_BUFFER_SIZE);

    EXPECT_EQ(COMMAND_LENGTH, bufferLength);
    EXPECT_STREQ(COMMAND, (const char *)buffer);
}

TEST_F(RingBufferTest, FindPacket)
{
    RingBufferPacketParameter parameter = {
        .header = (const uint8_t *)COMMAND_HEADER,
        .headerLength = strlen(COMMAND_HEADER),
        .footer = (const uint8_t *)COMMAND_FOOTER,
        .footerLength = strlen(COMMAND_FOOTER),
    };

    RingBufferPacketResult result;
    size_t bufferLength = 0;
    uint8_t buffer[RING_BUFFER_TEST_BUFFER_SIZE] = {0};

    Write();

    result = RingBuffer_FindPacket(&mRingBuffer, &parameter);
    EXPECT_EQ(0U, result.invalidLength);
    EXPECT_EQ(COMMAND_LENGTH, result.packetLength);

    bufferLength = RingBuffer_Read(&mRingBuffer, buffer, result.invalidLength);
    EXPECT_EQ(0U, bufferLength);

    bufferLength = RingBuffer_Read(&mRingBuffer, buffer, result.packetLength);
    EXPECT_EQ(COMMAND_LENGTH, bufferLength);
    EXPECT_STREQ(COMMAND, (const char *)buffer);
}

// Method implement(s)
void RingBufferTest::SetUp(void)
{
    memset(mBuffer, 0, RING_BUFFER_TEST_BUFFER_SIZE);
    RingBuffer_Construct(&mRingBuffer, mBuffer, RING_BUFFER_TEST_BUFFER_SIZE);
}

void RingBufferTest::TearDown(void)
{
    RingBuffer_Destruct(&mRingBuffer);
    memset(mBuffer, 0, RING_BUFFER_TEST_BUFFER_SIZE);
}

void RingBufferTest::Write(void)
{
    RingBuffer_Write(&mRingBuffer, (const uint8_t *)COMMAND, COMMAND_LENGTH);
}
