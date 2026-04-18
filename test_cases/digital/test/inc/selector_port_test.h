#ifndef __SELECTOR_PORT_TEST_H__
#define __SELECTOR_PORT_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"
#include "port/arduino/inc/arduino_port.h"
#include "port/core/inc/base_port.h"

#include "digital/selector/inc/data_selector.h"
#include "digital/selector/inc/selector_group.h"
#include "digital/selector/inc/selector_port.h"

class SelectorPortTest : public testing::Test {
protected:
    ArduinoCore mCore;

    DataSelector mSelector;
    SelectorGroup mGroup;
    SelectorPort mPort;

    static void *const PORT;
    static const unsigned int ADDRESS_PINS;
    static const unsigned int DATA_PIN;

    static const unsigned int BIT;

    void SetUp(void);
    void TearDown(void);
};

#endif // __SELECTOR_PORT_TEST_H__
