#ifndef __REGISTER_PORT_TEST_H__
#define __REGISTER_PORT_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"
#include "port/core/inc/base_port.h"

#include "digital/register/inc/register_group.h"
#include "digital/register/inc/register_port.h"
#include "digital/register/inc/shift_register.h"

class RegisterPortTest : public testing::Test {
protected:
    ArduinoCore mCore;

    ShiftRegister mRegister;
    RegisterGroup mGroup;
    RegisterPort mPort;

    static void *const PORT;
    static const unsigned int SER_PIN;
    static const unsigned int SCK_PIN;
    static const unsigned int RCK_PIN;

    static const unsigned int BIT;

    void SetUp(void);
    void TearDown(void);
};

#endif // __REGISTER_PORT_TEST_H__
