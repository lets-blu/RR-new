#include "port/test/inc/base_core_test.h"

// Static member(s)
void *const BaseCoreTest::DIGITAL_PORT = NULL;
void *const BaseCoreTest::ADDRESS_PORT = (void *)&PORTB;
HardwareSerial *const BaseCoreTest::SERIAL = &Serial;
const unsigned long BaseCoreTest::BAUDRATE = 115200;
const unsigned long BaseCoreTest::MILLIS = 1000;

// Test case(s)
TEST_F(BaseCoreTest, CreatePort_Digital)
{
    EXPECT_EQ(&mCore._ports[0].base, CreatePortDigital());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(BaseCoreTest, DestroyPort_Digital)
{
    BaseCore_DestroyPort(&mCore.base, CreatePortDigital());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(BaseCoreTest, CreatePort_GeneralDigital)
{
    EXPECT_EQ(&mCore._ports[0].base, CreatePortGeneralDigital());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(BaseCoreTest, DestroyPort_GeneralDigital)
{
    BaseCore_DestroyPort(&mCore.base, CreatePortGeneralDigital());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(BaseCoreTest, CreatePort_Address)
{
    EXPECT_EQ(&mCore._ports[0].base, CreatePortAddress());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(BaseCoreTest, DestroyPort_Address)
{
    BaseCore_DestroyPort(&mCore.base, CreatePortAddress());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(BaseCoreTest, CreatePort_GeneralAddress)
{
    EXPECT_EQ(&mCore._ports[0].base, CreatePortGeneralAddress());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(BaseCoreTest, DestroyPort_GeneralAddress)
{
    BaseCore_DestroyPort(&mCore.base, CreatePortGeneralAddress());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(BaseCoreTest, CreateSerial)
{
    EXPECT_EQ(&mCore._serials[0].base, CreateSerial());
    EXPECT_TRUE(ARDUINO_SERIAL_IS_CONSTRUCTED(&mCore._serials[0]));
}

TEST_F(BaseCoreTest, DestroySerial)
{
    BaseCore_DestroySerial(&mCore.base, CreateSerial());
    EXPECT_FALSE(ARDUINO_SERIAL_IS_CONSTRUCTED(&mCore._serials[0]));
}

TEST_F(BaseCoreTest, CreateSerial_General)
{
    EXPECT_EQ(&mCore._serials[0].base, CreateSerialGeneral());
    EXPECT_TRUE(ARDUINO_SERIAL_IS_CONSTRUCTED(&mCore._serials[0]));
}

TEST_F(BaseCoreTest, DestroySerial_General)
{
    BaseCore_DestroySerial(&mCore.base, CreateSerialGeneral());
    EXPECT_FALSE(ARDUINO_SERIAL_IS_CONSTRUCTED(&mCore._serials[0]));
}

TEST_F(BaseCoreTest, GetTime)
{
    gArduinoMillis = MILLIS;
    EXPECT_EQ(MILLIS, BaseCore_GetTime(&mCore.base));
}

// Method implement(s)
void BaseCoreTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
}

void BaseCoreTest::TearDown(void)
{
    ArduinoCore_Destruct(&mCore);
}

BasePort *BaseCoreTest::CreatePortDigital(void)
{
    ArduinoPortParameter parameter = {
        .base = ARDUINO_PORT_PARAMETER_BASE,
        .port = DIGITAL_PORT,
    };

    return BaseCore_CreatePort(
        &mCore.base,
        ARDUINO_CORE_DIGITAL_PORT,
        &parameter.base);
}

BasePort *BaseCoreTest::CreatePortGeneralDigital(void)
{
    GeneralPortParameter parameter = {
        .base = GENERAL_PORT_PARAMETER_BASE,
        .port = DIGITAL_PORT,
    };

    return BaseCore_CreatePort(
        &mCore.base,
        GENERAL_DIGITAL_PORT,
        &parameter.base);
}

BasePort *BaseCoreTest::CreatePortAddress(void)
{
    ArduinoPortParameter parameter = {
        .base = ARDUINO_PORT_PARAMETER_BASE,
        .port = ADDRESS_PORT,
    };

    return BaseCore_CreatePort(
        &mCore.base,
        ARDUINO_CORE_ADDRESS_PORT,
        &parameter.base);
}

BasePort *BaseCoreTest::CreatePortGeneralAddress(void)
{
    GeneralPortParameter parameter = {
        .base = GENERAL_PORT_PARAMETER_BASE,
        .port = ADDRESS_PORT,
    };

    return BaseCore_CreatePort(
        &mCore.base,
        GENERAL_ADDRESS_PORT,
        &parameter.base);
}

BaseSerial *BaseCoreTest::CreateSerial(void)
{
    ArduinoSerialParameter parameter = {
        .base = ARDUINO_SERIAL_PARAMETER_BASE,
        .serial = SERIAL,
        .baudrate = BAUDRATE,
        .rxBuffer = NULL,
        .rxBufferSize = 0,
    };

    return BaseCore_CreateSerial(
        &mCore.base,
        ARDUINO_CORE_UART_SERIAL,
        &parameter.base);
}

BaseSerial *BaseCoreTest::CreateSerialGeneral(void)
{
    GeneralSerialParameter parameter = {
        .base = GENERAL_SERIAL_PARAMETER_BASE,
        .serial = SERIAL,
        .baudrate = BAUDRATE,
    };

    return BaseCore_CreateSerial(
        &mCore.base,
        GENERAL_UART_SERIAL,
        &parameter.base);
}
