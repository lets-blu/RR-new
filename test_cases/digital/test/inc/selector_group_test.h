#ifndef __SELECTOR_GROUP_TEST_H__
#define __SELECTOR_GROUP_TEST_H__

#include "gtest/gtest.h"

#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"
#include "port/arduino/inc/arduino_port.h"

#include "digital/selector/inc/data_selector.h"
#include "digital/selector/inc/selector_group.h"

#define SELECTOR_GROUP_TEST_SELECTORS_NUMBER 2U

class SelectorGroupTest : public testing::Test {
protected:
    ArduinoCore mCore;
    SelectorGroup mGroup;
    DataSelector mSelectors[SELECTOR_GROUP_TEST_SELECTORS_NUMBER];

    static void *const PORT;
    static const unsigned int ADDRESS_PINS;
    static const unsigned int DATA_PIN;

    static const unsigned int BIT;

    void SetUp(void);
    void TearDown(void);
    void AddSelector(void);
};

#endif // __SELECTOR_GROUP_TEST_H__
