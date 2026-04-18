#ifndef __BASE_PORT_TEST_H__
#define __BASE_PORT_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "port/arduino/inc/arduino_port.h"
#include "port/core/inc/base_port.h"

class BasePortTest : public testing::Test {
protected:
    ArduinoPort mPort;
    static void *const PORT;
    static const unsigned int PIN;

    void SetUp(void);
    void TearDown(void);
};

#endif // __BASE_PORT_TEST_H__
