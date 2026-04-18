#ifndef __LOGGER_TEST_H__
#define __LOGGER_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/device/inc/device_factory.h"
#include "core/device/inc/device_manager.h"
#include "port/arduino/inc/arduino_core.h"
#include "port/core/inc/base_serial.h"

#include "utils/logger/inc/logger.h"

#define LOGGER_TEST_NAME "LoggerTest"
#define LOGGER_TEST_FORMAT "Hello, world!"

class LoggerTest : public testing::Test {
protected:
    ArduinoCore mCore;
    BaseSerial *mSerial;
    Logger mLogger;

    static HardwareSerial *const SERIAL;
    static const unsigned long BAUDRATE;
    static const LoggerLevel LEVEL;

    static const char *DEBUG_STRING;
    static const size_t DEBUG_STRING_LENGTH;

    static const char *INFO_STRING;
    static const size_t INFO_STRING_LENGTH;

    static const char *WARN_STRING;
    static const size_t WARN_STRING_LENGTH;

    static const char *ERROR_STRING;
    static const size_t ERROR_STRING_LENGTH;

    void SetUp(void);
    void TearDown(void);

    void SetSerial(void);
    void Register(void);
};

#endif // __LOGGER_TEST_H__
