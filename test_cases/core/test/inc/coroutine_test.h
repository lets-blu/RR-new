#ifndef __COROUTINE_TEST_H__
#define __COROUTINE_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/coroutine/inc/coroutine.h"
#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"

class CoroutineTest : public testing::Test {
protected:
    ArduinoCore mCore;
    Coroutine mCoroutine;

    static unsigned int sCounter;
    static const unsigned int REPEAT_TIMES;
    static const unsigned long SLEEP_TIME;

    void SetUp(void);
    void TearDown(void);

    static CoroutineState RunYield(Coroutine *coroutine);
    static CoroutineState RunSleep(Coroutine *coroutine);
};

#endif // __COROUTINE_TEST_H__
