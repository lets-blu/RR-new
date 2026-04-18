#ifndef __AT_COMMAND_TEST_H__
#define __AT_COMMAND_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/device/inc/device_factory.h"
#include "core/device/inc/device_manager.h"
#include "core/event/inc/event_handler.h"
#include "core/utils/inc/ring_buffer.h"
#include "port/arduino/inc/arduino_core.h"
#include "port/core/inc/base_serial.h"

#include "utils/command/inc/at_command.h"

#define AT_COMMAND_TEST_COMMAND "+TEST"
#define AT_COMMAND_TEST_COMMAND_LENGTH 5U

#define AT_COMMAND_TEST_ARGUMENTS_COUNT 2
#define AT_COMMAND_TEST_ARGUMENT1 "ARGUMENT1"
#define AT_COMMAND_TEST_ARGUMENT1_LENGTH 9U
#define AT_COMMAND_TEST_ARGUMENT2 "ARGUMENT2"
#define AT_COMMAND_TEST_ARGUMENT2_LENGTH 9U

#define AT_COMMAND_TEST_RESPONSE "RESPONSE"
#define AT_COMMAND_TEST_RESPONSE_LENGTH 8U

class ATCommandTest : public testing::Test {
protected:
    ArduinoCore mCore;
    uint8_t mBuffer[ARDUINO_BUFFER_SIZE];

    BaseSerial *mSerial;
    ATCommand mCommand;

    static HardwareSerial *const SERIAL;
    static const unsigned long BAUDRATE;

    static const char *COMMAND;
    static const size_t COMMAND_LENGTH;
    static const char *RESPONSE;
    static const size_t RESPONSE_LENGTH;

    void SetUp(void);
    void TearDown(void);
    void SetSerial(void);

    static void EventHandler(void *sender, EventArgs *args);
};

#endif // __AT_COMMAND_TEST_H__
