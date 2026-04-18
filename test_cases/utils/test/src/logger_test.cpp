#include "utils/test/inc/logger_test.h"

// Static member(s)
HardwareSerial *const LoggerTest::SERIAL = &Serial;
const unsigned long LoggerTest::BAUDRATE = 115200;
const LoggerLevel LoggerTest::LEVEL = LOGGER_LEVEL_INFO;

const char *LoggerTest::DEBUG_STRING = "";
const size_t LoggerTest::DEBUG_STRING_LENGTH = 0;

const char *LoggerTest::INFO_STRING
    = "[" LOGGER_TEST_NAME "][I] " LOGGER_TEST_FORMAT "\r\n";

const size_t LoggerTest::INFO_STRING_LENGTH = strlen(INFO_STRING);

const char *LoggerTest::WARN_STRING
    = "[" LOGGER_TEST_NAME "][W] " LOGGER_TEST_FORMAT "\r\n";

const size_t LoggerTest::WARN_STRING_LENGTH = strlen(WARN_STRING);

const char *LoggerTest::ERROR_STRING
    = "[" LOGGER_TEST_NAME "][E] " LOGGER_TEST_FORMAT "\r\n";

const size_t LoggerTest::ERROR_STRING_LENGTH = strlen(ERROR_STRING);

// Test case(s)
TEST_F(LoggerTest, SetSerial)
{
    SetSerial();
}

TEST_F(LoggerTest, Register)
{
    Register();
}

TEST_F(LoggerTest, Deregister)
{
    Register();
    Logger_Deregister(&mLogger);
}

TEST_F(LoggerTest, LOGGER_D)
{
    RingBuffer *buffer = SERIAL->getRingBuffer();

    SetSerial();
    LOGGER_D(&mLogger, LOGGER_TEST_FORMAT);

    EXPECT_EQ(DEBUG_STRING_LENGTH, buffer->_usedLength);
    EXPECT_STREQ(DEBUG_STRING, (const char *)buffer->_buffer);
}

TEST_F(LoggerTest, LOGGER_I)
{
    RingBuffer *buffer = SERIAL->getRingBuffer();

    SetSerial();
    LOGGER_I(&mLogger, LOGGER_TEST_FORMAT);

    EXPECT_EQ(INFO_STRING_LENGTH, buffer->_usedLength);
    EXPECT_STREQ(INFO_STRING, (const char *)buffer->_buffer);
}

TEST_F(LoggerTest, LOGGER_W)
{
    RingBuffer *buffer = SERIAL->getRingBuffer();

    SetSerial();
    LOGGER_W(&mLogger, LOGGER_TEST_FORMAT);

    EXPECT_EQ(WARN_STRING_LENGTH, buffer->_usedLength);
    EXPECT_STREQ(WARN_STRING, (const char *)buffer->_buffer);
}

TEST_F(LoggerTest, LOGGER_E)
{
    RingBuffer *buffer = SERIAL->getRingBuffer();

    SetSerial();
    LOGGER_E(&mLogger, LOGGER_TEST_FORMAT);

    EXPECT_EQ(ERROR_STRING_LENGTH, buffer->_usedLength);
    EXPECT_STREQ(ERROR_STRING, (const char *)buffer->_buffer);
}

// Method implement(s)
void LoggerTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    mLogger = LOGGER_STATIC(LOGGER_TEST_NAME, LOGGER_LEVEL_INFO);
}

void LoggerTest::TearDown(void)
{
    Logger_Deregister(&mLogger);
    Logger_SetSerial(NULL);
    DeviceFactory_DestroySerial(DeviceFactory_GetInstance(), mSerial);

    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

void LoggerTest::SetSerial(void)
{
    ArduinoSerialParameter parameter = {
        .base = ARDUINO_SERIAL_PARAMETER_BASE,
        .serial = SERIAL,
        .baudrate = BAUDRATE,
        .rxBuffer = NULL,
        .rxBufferSize = 0,
    };

    mSerial = DeviceFactory_CreateSerial(
        DeviceFactory_GetInstance(),
        ARDUINO_CORE_UART_SERIAL,
        &parameter.base);

    Logger_SetSerial(mSerial);
}

void LoggerTest::Register(void)
{
    Logger_Register(&mLogger);
}
