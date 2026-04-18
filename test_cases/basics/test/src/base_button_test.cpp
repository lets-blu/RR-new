#include "basics/test/inc/base_button_test.h"

// Static member(s)
unsigned int BaseButtonTest::sCounter = 0;

void *const BaseButtonTest::PORT = NULL;
const unsigned int BaseButtonTest::PIN = 0x01;
const unsigned int BaseButtonTest::PRESS_VALUE = BASE_PORT_VALUE_LOW;

const ButtonState *BaseButtonTest::STATE = BUTTON_STATE_RELEASED;

// Test case(s)
TEST_F(BaseButtonTest, SetState)
{
    SetState();
    EXPECT_EQ(STATE, mButton._state);
}

TEST_F(BaseButtonTest, GetState)
{
    SetState();
    EXPECT_EQ(STATE, BaseButton_GetState(&mButton.base));
}

TEST_F(BaseButtonTest, OnClick)
{
    DigitalButton_SetEventHandler(&mButton, EventHandler);

    sCounter = 0;
    BaseButton_OnClick(&mButton.base);
    EXPECT_EQ(1U, sCounter);
}

// Method implement(s)
void BaseButtonTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    DigitalButton_Construct(&mButton, PORT, PIN, PRESS_VALUE);
}

void BaseButtonTest::TearDown(void)
{
    DigitalButton_Destruct(&mButton);
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

void BaseButtonTest::SetState(void)
{
    BaseButton_SetState(&mButton.base, STATE);
}

void BaseButtonTest::EventHandler(void *sender, EventArgs *args)
{
    (void)sender;
    (void)args;
    sCounter++;
}
