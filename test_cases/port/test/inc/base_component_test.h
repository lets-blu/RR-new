#ifndef __BASE_COMPONENT_TEST_H__
#define __BASE_COMPONENT_TEST_H__

#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"
#include "port/component/inc/base_component.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/general_port.h"

#include "digital/register/inc/register_group.h"
#include "digital/register/inc/register_port.h"
#include "digital/register/inc/shift_register.h"

class BaseComponentTest : public testing::Test {
protected:
    ArduinoCore mCore;
    ShiftRegister mRegister;
    RegisterGroup mGroup;

    static void *const PORT;
    static const unsigned int SER_PIN;
    static const unsigned int SCK_PIN;
    static const unsigned int RCK_PIN;

    static const unsigned int BIT;

    void SetUp(void);
    void TearDown(void);
    BasePort *CreatePort(void);
    BasePort *CreatePortGeneral(void);
};

#endif // __BASE_COMPONENT_TEST_H__
