#ifndef __DEVICE_FACTORY_TEST_H__
#define __DEVICE_FACTORY_TEST_H__

#include "gtest/gtest.h"

#include "core/device/inc/device_factory.h"
#include "core/device/inc/device_manager.h"
#include "core/event/inc/event_handler.h"

#include "port/arduino/inc/arduino_core.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/base_serial.h"
#include "port/core/inc/base_timer.h"
#include "port/core/inc/general_port.h"
#include "port/core/inc/general_serial.h"
#include "port/core/inc/general_timer.h"

#include "port/none/inc/none_system.h"
#include "port/system/inc/base_task.h"
#include "port/system/inc/general_task.h"

class DeviceFactoryTest : public testing::Test {
protected:
    ArduinoCore mCore;
    NoneSystem mSystem;

    static void *const PORT;
    static HardwareSerial *const SERIAL;
    static const unsigned long BAUDRATE;

    void SetUp(void);
    void TearDown(void);

    BasePort *CreatePort(void);
    BaseSerial *CreateSerial(void);
    BaseTask *CreateTask(void);
    BaseTimer *CreateTimer(void);

    static void TaskEntry(void *parameter);
    static void EventHandler(void *sender, EventArgs *args);
};

#endif // __DEVICE_FACTORY_TEST_H__
