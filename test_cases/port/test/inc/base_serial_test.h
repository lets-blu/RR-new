#ifndef __BASE_SERIAL_TEST_H__
#define __BASE_SERIAL_TEST_H__

#include "Arduino.h"
#include "gtest/gtest.h"

#include "core/event/inc/event_handler.h"
#include "port/arduino/inc/arduino_serial.h"
#include "port/core/inc/base_serial.h"

class BaseSerialTest : public testing::Test {
protected:
    uint8_t mBuffer[ARDUINO_BUFFER_SIZE];
    ArduinoSerial mSerial;
    static unsigned int sCounter;

    static HardwareSerial *const SERIAL;
    static const unsigned long BAUDRATE;
    static const uint8_t *BUFFER;
    static const size_t BUFFER_SIZE;

    void SetUp(void);
    void TearDown(void);
    void Write(void);

    static void EventHandler(void *sender, EventArgs *args);
};

#endif // __BASE_SERIAL_TEST_H__
