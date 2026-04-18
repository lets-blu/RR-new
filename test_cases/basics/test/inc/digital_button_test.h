#ifndef __DIGITAL_BUTTON_TEST_H__
#define __DIGITAL_BUTTON_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "core/event/inc/event_handler.h"
#include "core/utils/inc/linked_list.h"

#include "port/arduino/inc/arduino_core.h"
#include "port/core/inc/base_port.h"

#include "basics/button/inc/digital_button.h"

class DigitalButtonTest : public testing::Test {
protected:
    ArduinoCore mCore;
    DigitalButton mButton;
    static unsigned int sCounter;

    static void *const PORT;
    static const unsigned int PIN;
    static const unsigned int PRESS_VALUE;

    void SetUp(void);
    void TearDown(void);

    void SetEventHandler(void);
    static void EventHandler(void *sender, EventArgs *args);
    static bool FindCallback(LinkedListNode *node, const void *data);
};

#endif // __DIGITAL_BUTTON_TEST_H__
