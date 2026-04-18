#ifndef __LINKED_COROUTINE_TEST_H__
#define __LINKED_COROUTINE_TEST_H__

#include <stddef.h>
#include <string.h>

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/coroutine/inc/linked_coroutine.h"
#include "core/device/inc/device_manager.h"
#include "core/utils/inc/keywords.h"
#include "port/arduino/inc/arduino_core.h"

#define LinkedCoroutine2TestLinkedCoroutine(pThis) \
    CONTAINER_OF(pThis, TestLinkedCoroutine, base)

#define LinkedListNode2TestLinkedCoroutine(pThis) \
    LinkedCoroutine2TestLinkedCoroutine(LinkedListNode2LinkedCoroutine(pThis))

typedef struct {
    LinkedCoroutine base;
    unsigned int _counter;
} TestLinkedCoroutine;

class LinkedCoroutineTest : public testing::Test {
public:
    static unsigned long GetSleepTime(void);

protected:
    ArduinoCore mCore;
    TestLinkedCoroutine mCoroutine;

    static const unsigned int REPEAT_TIMES;
    static const unsigned long SLEEP_TIME;

    void SetUp(void);
    void TearDown(void);
};

#endif // __LINKED_COROUTINE_TEST_H__
