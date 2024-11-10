#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "gtest/gtest.h"

#include "core/common/inc/keywords.h"
#include "basics/button/inc/base_button.h"
#include "basics/button/inc/button_state.h"

#define BaseButton2TestButton(instance) \
    BASE2SUB(instance, TestButton, base)

typedef struct {
    BaseButton base;
    const ButtonState *_currentState;
} TestButton;

PUBLIC void ConstructTestButton(TestButton *instance);
PUBLIC void DestructTestButton(TestButton *instance);

PUBLIC void OnPressTestButton(TestButton *self);
PUBLIC void OnReleaseTestButton(TestButton *self);

class ButtonStateTest: public testing::Test
{
public:
    static bool s_isClicked;

protected:
    TestButton m_button;

    virtual void SetUp()
    {
        ConstructTestButton(&m_button);
        ButtonStateTest::s_isClicked = false;
    }

    virtual void TearDown()
    {
        DestructTestButton(&m_button);
    }

    void RunTest(const ButtonState *bounceState);
};

TEST_F(ButtonStateTest, PressRelease)
{
    this->RunTest(NULL);
}

TEST_F(ButtonStateTest, PressBounce)
{
    this->RunTest(BUTTON_STATE_CONFIRM_PRESS);
}

TEST_F(ButtonStateTest, ReleaseBounce)
{
    this->RunTest(BUTTON_STATE_CONFIRM_RELEASE);
}

bool ButtonStateTest::s_isClicked = false;

void ButtonStateTest::RunTest(const ButtonState *bounceState)
{
    OnPressTestButton(&m_button);
    EXPECT_EQ(BUTTON_STATE_CONFIRM_PRESS, m_button._currentState);

    if (bounceState != BUTTON_STATE_CONFIRM_PRESS)
    {
        OnPressTestButton(&m_button);
        EXPECT_EQ(BUTTON_STATE_PRESSED, m_button._currentState);
    }
    else
    {
        OnReleaseTestButton(&m_button);
        EXPECT_EQ(BUTTON_STATE_RELEASED, m_button._currentState);
        EXPECT_FALSE(ButtonStateTest::s_isClicked);

        return;
    }

    OnReleaseTestButton(&m_button);
    EXPECT_EQ(BUTTON_STATE_CONFIRM_RELEASE, m_button._currentState);

    if (bounceState != BUTTON_STATE_CONFIRM_RELEASE)
    {
        OnReleaseTestButton(&m_button);
        EXPECT_EQ(BUTTON_STATE_RELEASED, m_button._currentState);
        EXPECT_TRUE(ButtonStateTest::s_isClicked);
    }
    else
    {
        OnPressTestButton(&m_button);
        EXPECT_EQ(BUTTON_STATE_PRESSED, m_button._currentState);
        EXPECT_FALSE(ButtonStateTest::s_isClicked);
    }
}

PUBLIC void SetStateToTestButtonBase(
    BaseButton *button,
    const ButtonState *state);

PUBLIC const ButtonState *GetStateFromTestButtonBase(BaseButton *button);
PUBLIC void OnClickTestButtonBase(BaseButton *button);

static const BaseButtonVtbl baseVtbl = {
    .SetState = SetStateToTestButtonBase,
    .GetState = GetStateFromTestButtonBase,
    .OnClick = OnClickTestButtonBase
};

PUBLIC void ConstructTestButton(TestButton *instance)
{
    if (instance != NULL)
    {
        ConstructBaseButton(&instance->base);
        instance->base.vtbl = &baseVtbl;
        instance->_currentState = BUTTON_STATE_RELEASED;
    }
}

PUBLIC void DestructTestButton(TestButton *instance)
{
    if (instance != NULL)
    {
        DestructBaseButton(&instance->base);
        memset(instance, 0, sizeof(TestButton));
    }
}

PUBLIC void OnPressTestButton(TestButton *self)
{
    if (self != NULL)
    {
        OnPressInButtonState(self->_currentState, &self->base);
    }
}

PUBLIC void OnReleaseTestButton(TestButton *self)
{
    if (self != NULL)
    {
        OnReleaseInButtonState(self->_currentState, &self->base);
    }
}

PUBLIC void SetStateToTestButtonBase(
    BaseButton *button,
    const ButtonState *state)
{
    TestButton *self = BaseButton2TestButton(button);

    if (button != NULL && state != NULL)
    {
        self->_currentState = state;
    }
}

PUBLIC const ButtonState *GetStateFromTestButtonBase(BaseButton *button)
{
    TestButton *self = BaseButton2TestButton(button);
    return (button == NULL) ? NULL : self->_currentState;
}

PUBLIC void OnClickTestButtonBase(BaseButton *button)
{
    (void)button;
    ButtonStateTest::s_isClicked = true;
    printf("[ DEBUG    ] Button clicked!\r\n");
}

