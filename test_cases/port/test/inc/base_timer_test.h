#ifndef __BASE_TIMER_TEST_H__
#define __BASE_TIMER_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "core/event/inc/event_handler.h"

#include "port/arduino/inc/arduino_core.h"
#include "port/core/inc/base_timer.h"
#include "port/none/inc/none_timer.h"

class BaseTimerTest : public testing::Test {
protected:
    ArduinoCore mCore;
    NoneTimer mTimer;

    static unsigned int sCounter;
    static const unsigned long DELAY;

    void SetUp(void);
    void TearDown(void);
    void StartTimer(void);

    static void EventHandler(void *sender, EventArgs *args);
};

#endif // __BASE_TIMER_TEST_H__
