#include "utils/test/inc/at_command_test.h"

// Static member(s)
HardwareSerial *const ATCommandTest::SERIAL = &Serial;
const unsigned long ATCommandTest::BAUDRATE = 115200;

const char *ATCommandTest::COMMAND
    = AT_COMMAND_HEADER AT_COMMAND_TEST_COMMAND AT_COMMAND_COMMAND_SEPARATOR
        AT_COMMAND_TEST_ARGUMENT1 AT_COMMAND_ARGUMENT_SEPARATOR
            AT_COMMAND_TEST_ARGUMENT2 AT_COMMAND_FOOTER;

const size_t ATCommandTest::COMMAND_LENGTH
    = AT_COMMAND_HEADER_LENGTH + AT_COMMAND_TEST_COMMAND_LENGTH
    + AT_COMMAND_COMMAND_SEPARATOR_LENGTH
    + AT_COMMAND_TEST_ARGUMENT1_LENGTH + AT_COMMAND_ARGUMENT_SEPARATOR_LENGTH
    + AT_COMMAND_TEST_ARGUMENT2_LENGTH + AT_COMMAND_FOOTER_LENGTH;

const char *ATCommandTest::RESPONSE
    = AT_COMMAND_TEST_COMMAND AT_COMMAND_RESPONSE_SEPARATOR
        AT_COMMAND_TEST_RESPONSE AT_COMMAND_FOOTER;

const size_t ATCommandTest::RESPONSE_LENGTH
    = AT_COMMAND_TEST_COMMAND_LENGTH + AT_COMMAND_RESPONSE_SEPARATOR_LENGTH
    + AT_COMMAND_TEST_RESPONSE_LENGTH + AT_COMMAND_FOOTER_LENGTH;

// Test case(s)
TEST_F(ATCommandTest, SetSerial)
{
    SetSerial();
}

TEST_F(ATCommandTest, Response)
{
    size_t length = 0;
    uint8_t buffer[ARDUINO_BUFFER_SIZE] = {0};
    RingBuffer *ringBuffer = SERIAL->getRingBuffer();

    SetSerial();
    RingBuffer_Write(ringBuffer, (const uint8_t *)COMMAND, COMMAND_LENGTH);
    DeviceManager_TaskEntry(DeviceManager_GetInstance());

    length = RingBuffer_Read(ringBuffer, buffer, RESPONSE_LENGTH);
    EXPECT_EQ(RESPONSE_LENGTH, length);
    EXPECT_STREQ(RESPONSE, (const char *)buffer);

    memset(buffer, 0, ARDUINO_BUFFER_SIZE);

    length = RingBuffer_Read(ringBuffer, buffer, ARDUINO_BUFFER_SIZE);
    EXPECT_EQ(AT_COMMAND_OK_RESPONSE_LENGTH, length);
    EXPECT_STREQ(AT_COMMAND_OK_RESPONSE, (const char *)buffer);
}

// Method implement(s)
void ATCommandTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    ATCommand_Construct(&mCommand, AT_COMMAND_TEST_COMMAND, EventHandler);
}

void ATCommandTest::TearDown(void)
{
    ATCommand_SetSerial(NULL);
    ATCommand_Destruct(&mCommand);

    DeviceFactory_DestroySerial(DeviceFactory_GetInstance(), mSerial);
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

void ATCommandTest::SetSerial(void)
{
    ArduinoSerialParameter parameter = {
        .base = ARDUINO_SERIAL_PARAMETER_BASE,
        .serial = SERIAL,
        .baudrate = BAUDRATE,
        .rxBuffer = mBuffer,
        .rxBufferSize = ARDUINO_BUFFER_SIZE,
    };

    mSerial = DeviceFactory_CreateSerial(
        DeviceFactory_GetInstance(),
        ARDUINO_CORE_UART_SERIAL,
        &parameter.base);

    ATCommand_SetSerial(mSerial);
}

void ATCommandTest::EventHandler(void *sender, EventArgs *args)
{
    ATCommandEventArgs *commandArgs = EventArgs2ATCommandEventArgs(args);

    ASSERT_NE((void *)NULL, sender);
    ASSERT_NE((EventArgs *)NULL, args);

    EXPECT_EQ(AT_COMMAND_TEST_ARGUMENTS_COUNT, commandArgs->argc);
    EXPECT_STREQ(AT_COMMAND_TEST_ARGUMENT1, commandArgs->argv[0]);
    EXPECT_STREQ(AT_COMMAND_TEST_ARGUMENT2, commandArgs->argv[1]);

    ATCommand_Response((ATCommand *)sender, AT_COMMAND_TEST_RESPONSE);
}
