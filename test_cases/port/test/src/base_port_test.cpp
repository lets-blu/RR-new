#include "port/test/inc/base_port_test.h"

// Static member(s)
void *const BasePortTest::PORT = NULL;
const unsigned int BasePortTest::PIN = 0x01;

// Test case(s)
TEST_F(BasePortTest, SetMode)
{
    BasePort_SetMode(&mPort.base, PIN, BASE_PORT_MODE_INPUT);
    EXPECT_EQ(INPUT, gArduinoPinModes[PIN]);

    BasePort_SetMode(&mPort.base, PIN, BASE_PORT_MODE_OUTPUT);
    EXPECT_EQ(OUTPUT, gArduinoPinModes[PIN]);

    BasePort_SetMode(&mPort.base, PIN, BASE_PORT_MODE_INPUT_PULLUP);
    EXPECT_EQ(INPUT_PULLUP, gArduinoPinModes[PIN]);
}

TEST_F(BasePortTest, Read)
{
    gArduinoPinValues[PIN] = LOW;
    EXPECT_EQ(BASE_PORT_VALUE_LOW, BasePort_Read(&mPort.base, PIN));

    gArduinoPinValues[PIN] = HIGH;
    EXPECT_EQ(BASE_PORT_VALUE_HIGH, BasePort_Read(&mPort.base, PIN));
}

TEST_F(BasePortTest, Write)
{
    BasePort_Write(&mPort.base, PIN, BASE_PORT_VALUE_LOW);
    EXPECT_EQ(LOW, gArduinoPinValues[PIN]);

    BasePort_Write(&mPort.base, PIN, BASE_PORT_VALUE_HIGH);
    EXPECT_EQ(HIGH, gArduinoPinValues[PIN]);
}

// Method implement(s)
void BasePortTest::SetUp(void)
{
    ArduinoPortParameter parameter = {
        .base = ARDUINO_PORT_PARAMETER_BASE,
        .port = NULL,
    };

    ArduinoPort_Construct(&mPort, &parameter);
}

void BasePortTest::TearDown(void)
{
    ArduinoPort_Destruct(&mPort);
}
