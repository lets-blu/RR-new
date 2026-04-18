#ifndef __BASE_BUTTON_TEST_H__
#define __BASE_BUTTON_TEST_H__

#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "core/event/inc/event_handler.h"
#include "port/arduino/inc/arduino_core.h"
#include "port/core/inc/base_port.h"

#include "basics/button/inc/base_button.h"
#include "basics/button/inc/digital_button.h"

class BaseButtonTest : public testing::Test {
protected:
    ArduinoCore mCore;
    DigitalButton mButton;
    static unsigned int sCounter;

    static void *const PORT;
    static const unsigned int PIN;
    static const unsigned int PRESS_VALUE;

    static const ButtonState *STATE;

    void SetUp(void);
    void TearDown(void);

    void SetState(void);
    static void EventHandler(void *sender, EventArgs *args);
};

#endif // __BASE_BUTTON_TEST_H__
