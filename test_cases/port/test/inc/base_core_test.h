#ifndef __BASE_CORE_TEST_H__
#define __BASE_CORE_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "port/core/inc/base_core.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/base_serial.h"
#include "port/core/inc/general_port.h"
#include "port/core/inc/general_serial.h"

#include "port/arduino/inc/arduino_core.h"
#include "port/arduino/inc/arduino_port.h"
#include "port/arduino/inc/arduino_serial.h"

class BaseCoreTest : public testing::Test {
protected:
    ArduinoCore mCore;

    static void *const DIGITAL_PORT;
    static void *const ADDRESS_PORT;
    static HardwareSerial *const SERIAL;
    static const unsigned long BAUDRATE;
    static const unsigned long MILLIS;

    void SetUp(void);
    void TearDown(void);

    BasePort *CreatePortDigital(void);
    BasePort *CreatePortGeneralDigital(void);
    BasePort *CreatePortAddress(void);
    BasePort *CreatePortGeneralAddress(void);
    BaseSerial *CreateSerial(void);
    BaseSerial *CreateSerialGeneral(void);
};

#endif // __BASE_CORE_TEST_H__
