#ifndef __DEVICE_MANAGER_TEST_H__
#define __DEVICE_MANAGER_TEST_H__

#include <stddef.h>
#include <string.h>

#include "gtest/gtest.h"

#include "core/coroutine/inc/linked_coroutine.h"
#include "core/device/inc/device_manager.h"
#include "core/event/inc/event_handler.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#include "port/arduino/inc/arduino_core.h"
#include "port/component/inc/base_component.h"
#include "port/core/inc/base_timer.h"
#include "port/core/inc/general_timer.h"
#include "port/none/inc/none_system.h"

#include "digital/register/inc/register_group.h"

#define LinkedCoroutine2DeviceManagerTestCoroutine(pThis) \
    CONTAINER_OF(pThis, DeviceManagerTestCoroutine, base)

#define LinkedListNode2DeviceManagerTestCoroutine(pThis) \
    LinkedCoroutine2DeviceManagerTestCoroutine(          \
        LinkedListNode2LinkedCoroutine(pThis))

typedef struct {
    LinkedCoroutine base;
    unsigned int _counter;
} DeviceManagerTestCoroutine;

class DeviceManagerTest : public testing::Test {
protected:
    ArduinoCore mCore;
    NoneSystem mSystem;
    RegisterGroup mGroup;
    DeviceManagerTestCoroutine mCoroutine;

    static unsigned int sCounter;

    static void *const PORT;
    static const unsigned int SER_PIN;
    static const unsigned int SCK_PIN;
    static const unsigned int RCK_PIN;
    static const unsigned int BIT;

    static const unsigned long DELAY;

    void SetUp(void);
    void TearDown(void);

    void SetCore(void);
    void SetSystem(void);
    void AddComponent(void);
    void AddCoroutine(void);

    static bool FindCallback(LinkedListNode *node, const void *data);
    static void EventHandler(void *sender, EventArgs *args);
};

#endif // __DEVICE_MANAGER_TEST_H__
