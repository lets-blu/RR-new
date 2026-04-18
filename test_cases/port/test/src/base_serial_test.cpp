#include "port/test/inc/base_serial_test.h"

// Static member(s)
unsigned int BaseSerialTest::sCounter = 0;

HardwareSerial *const BaseSerialTest::SERIAL = &Serial;
const unsigned long BaseSerialTest::BAUDRATE = 115200;
const uint8_t *BaseSerialTest::BUFFER = (const uint8_t *)"Hello, world!";
const size_t BaseSerialTest::BUFFER_SIZE = strlen((const char *)BUFFER);

// Test case(s)
TEST_F(BaseSerialTest, Write)
{
    RingBuffer *buffer = SERIAL->getRingBuffer();

    Write();

    EXPECT_STREQ((const char *)BUFFER, (const char *)buffer->_buffer);
    EXPECT_EQ(BUFFER_SIZE, buffer->_usedLength);

    EXPECT_EQ(0U, buffer->_readIndex);
    EXPECT_EQ(BUFFER_SIZE, buffer->_writeIndex);
}

TEST_F(BaseSerialTest, Read)
{
    size_t length = 0;
    uint8_t buffer[ARDUINO_BUFFER_SIZE] = {0};

    Write();
    ArduinoSerial_Sample(&mSerial);

    length = BaseSerial_Read(&mSerial.base, buffer, ARDUINO_BUFFER_SIZE);
    EXPECT_STREQ((const char *)BUFFER, (const char *)buffer);
    EXPECT_EQ(BUFFER_SIZE, length);
}

TEST_F(BaseSerialTest, SetEventHandler)
{
    Write();
    BaseSerial_SetEventHandler(&mSerial.base, EventHandler);

    sCounter = 0;
    ArduinoSerial_Sample(&mSerial);
    EXPECT_EQ(1U, sCounter);
}

// Method implement(s)
void BaseSerialTest::SetUp(void)
{
    ArduinoSerialParameter parameter = {
        .base = ARDUINO_SERIAL_PARAMETER_BASE,
        .serial = SERIAL,
        .baudrate = BAUDRATE,
        .rxBuffer = mBuffer,
        .rxBufferSize = ARDUINO_BUFFER_SIZE,
    };

    ArduinoSerial_Construct(&mSerial, &parameter);
}

void BaseSerialTest::TearDown(void)
{
    ArduinoSerial_Destruct(&mSerial);
}

void BaseSerialTest::Write(void)
{
    BaseSerial_Write(&mSerial.base, BUFFER, BUFFER_SIZE);
}

void BaseSerialTest::EventHandler(void *sender, EventArgs *args)
{
    (void)sender;
    (void)args;
    sCounter++;
}
