#include "basics/test/inc/led_test.h"

// Static member(s)
void *const LEDTest::PORT = NULL;
const unsigned int LEDTest::PIN = 0x01;
const unsigned int LEDTest::ON_VALUE = BASE_PORT_VALUE_HIGH;

// Test case(s)
TEST_F(LEDTest, TurnOn)
{
    LED_TurnOn(&mLED);
    EXPECT_EQ(ON_VALUE, gArduinoPinValues[PIN]);
}

TEST_F(LEDTest, TurnOff)
{
    LED_TurnOff(&mLED);

    if (ON_VALUE == BASE_PORT_VALUE_LOW) {
        EXPECT_EQ(BASE_PORT_VALUE_HIGH, gArduinoPinValues[PIN]);
    } else {
        EXPECT_EQ(BASE_PORT_VALUE_LOW, gArduinoPinValues[PIN]);
    }
}

// Method implement(s)
void LEDTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    LED_Construct(&mLED, PORT, PIN, ON_VALUE);
}

void LEDTest::TearDown(void)
{
    LED_Destruct(&mLED);
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}
