#include "basics/test/inc/button_state_test.h"

// Static member(s)
void *const ButtonStateTest::PORT = NULL;
const unsigned int ButtonStateTest::PIN = 0x01;
const unsigned int ButtonStateTest::PRESS_VALUE = BASE_PORT_VALUE_LOW;

// Test case(s)
TEST_F(ButtonStateTest, BUTTON_STATE_RELEASED_OnPress)
{
    SetState(BUTTON_STATE_RELEASED);
    ButtonState_OnPress(BUTTON_STATE_RELEASED, &mButton.base);
    EXPECT_EQ(BUTTON_STATE_CONFIRM_PRESS, mButton._state);
}

TEST_F(ButtonStateTest, BUTTON_STATE_RELEASED_OnRelease)
{
    SetState(BUTTON_STATE_RELEASED);
    ButtonState_OnRelease(BUTTON_STATE_RELEASED, &mButton.base);
    EXPECT_EQ(BUTTON_STATE_RELEASED, mButton._state);
}

TEST_F(ButtonStateTest, BUTTON_STATE_RELEASED_GetName)
{
    EXPECT_STREQ("RELEASED", ButtonState_GetName(BUTTON_STATE_RELEASED));
}

TEST_F(ButtonStateTest, BUTTON_STATE_CONFIRM_PRESS_OnPress)
{
    SetState(BUTTON_STATE_CONFIRM_PRESS);
    ButtonState_OnPress(BUTTON_STATE_CONFIRM_PRESS, &mButton.base);
    EXPECT_EQ(BUTTON_STATE_PRESSED, mButton._state);
}

TEST_F(ButtonStateTest, BUTTON_STATE_CONFIRM_PRESS_OnRelease)
{
    SetState(BUTTON_STATE_CONFIRM_PRESS);
    ButtonState_OnRelease(BUTTON_STATE_CONFIRM_PRESS, &mButton.base);
    EXPECT_EQ(BUTTON_STATE_RELEASED, mButton._state);
}

TEST_F(ButtonStateTest, BUTTON_STATE_CONFIRM_PRESS_GetName)
{
    EXPECT_STREQ(
        "CONFIRM_PRESS",
        ButtonState_GetName(BUTTON_STATE_CONFIRM_PRESS));
}

TEST_F(ButtonStateTest, BUTTON_STATE_PRESSED_OnPress)
{
    SetState(BUTTON_STATE_PRESSED);
    ButtonState_OnPress(BUTTON_STATE_PRESSED, &mButton.base);
    EXPECT_EQ(BUTTON_STATE_PRESSED, mButton._state);
}

TEST_F(ButtonStateTest, BUTTON_STATE_PRESSED_OnRelease)
{
    SetState(BUTTON_STATE_PRESSED);
    ButtonState_OnRelease(BUTTON_STATE_PRESSED, &mButton.base);
    EXPECT_EQ(BUTTON_STATE_CONFIRM_RELEASE, mButton._state);
}

TEST_F(ButtonStateTest, BUTTON_STATE_PRESSED_GetName)
{
    EXPECT_STREQ("PRESSED", ButtonState_GetName(BUTTON_STATE_PRESSED));
}

TEST_F(ButtonStateTest, BUTTON_STATE_CONFIRM_RELEASE_OnPress)
{
    SetState(BUTTON_STATE_CONFIRM_RELEASE);
    ButtonState_OnPress(BUTTON_STATE_CONFIRM_RELEASE, &mButton.base);
    EXPECT_EQ(BUTTON_STATE_PRESSED, mButton._state);
}

TEST_F(ButtonStateTest, BUTTON_STATE_CONFIRM_RELEASE_OnRelease)
{
    SetState(BUTTON_STATE_CONFIRM_RELEASE);
    ButtonState_OnRelease(BUTTON_STATE_CONFIRM_RELEASE, &mButton.base);
    EXPECT_EQ(BUTTON_STATE_RELEASED, mButton._state);
}

TEST_F(ButtonStateTest, BUTTON_STATE_CONFIRM_RELEASE_GetName)
{
    EXPECT_STREQ(
        "CONFIRM_RELEASE",
        ButtonState_GetName(BUTTON_STATE_CONFIRM_RELEASE));
}

// Method implement(s)
void ButtonStateTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    DigitalButton_Construct(&mButton, PORT, PIN, PRESS_VALUE);
}

void ButtonStateTest::TearDown(void)
{
    DigitalButton_Destruct(&mButton);
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

void ButtonStateTest::SetState(const ButtonState *state)
{
    BaseButton_SetState(&mButton.base, state);
}
