#ifndef __REGISTER_GROUP_TEST_H__
#define __REGISTER_GROUP_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"

#include "digital/register/inc/register_group.h"
#include "digital/register/inc/shift_register.h"

#define REGISTER_GROUP_TEST_REGISTERS_NUMBER 2U

class RegisterGroupTest : public testing::Test {
protected:
    ArduinoCore mCore;
    RegisterGroup mGroup;
    ShiftRegister mRegisters[REGISTER_GROUP_TEST_REGISTERS_NUMBER];

    static void *const PORT;
    static const unsigned int SER_PIN;
    static const unsigned int SCK_PIN;
    static const unsigned int RCK_PIN;

    static const unsigned int BIT;

    void SetUp(void);
    void TearDown(void);

    void AddRegister(void);
    void SetBit(void);
};

#endif // __REGISTER_GROUP_TEST_H__
