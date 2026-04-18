#ifndef __LED_TEST_H__
#define __LED_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"

#include "basics/led/inc/led.h"

class LEDTest : public testing::Test {
protected:
    ArduinoCore mCore;
    LED mLED;

    static void *const PORT;
    static const unsigned int PIN;
    static const unsigned int ON_VALUE;

    void SetUp(void);
    void TearDown(void);
};

#endif // __LED_TEST_H__
