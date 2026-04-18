#ifndef __BUTTON_STATE_TEST_H__
#define __BUTTON_STATE_TEST_H__

#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"
#include "port/core/inc/base_port.h"

#include "basics/button/inc/base_button.h"
#include "basics/button/inc/button_state.h"
#include "basics/button/inc/digital_button.h"

class ButtonStateTest : public testing::Test {
protected:
    ArduinoCore mCore;
    DigitalButton mButton;

    static void *const PORT;
    static const unsigned int PIN;
    static const unsigned int PRESS_VALUE;

    void SetUp(void);
    void TearDown(void);
    void SetState(const ButtonState *state);
};

#endif // __BUTTON_STATE_TEST_H__
