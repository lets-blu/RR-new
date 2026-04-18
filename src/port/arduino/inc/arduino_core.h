#ifndef __ARDUINO_CORE_H__
#define __ARDUINO_CORE_H__

#include <stddef.h>
#include <string.h>

#include <Arduino.h>

#include "core/utils/inc/keywords.h"

#include "port/core/inc/base_core.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/base_serial.h"
#include "port/core/inc/general_port.h"
#include "port/core/inc/general_serial.h"

#include "port/arduino/inc/arduino_port.h"
#include "port/arduino/inc/arduino_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef ARDUINO_CORE_PORTS_NUMBER
#define ARDUINO_CORE_PORTS_NUMBER 4U
#endif // ARDUINO_CORE_PORTS_NUMBER

#ifndef ARDUINO_CORE_SERIALS_NUMBER
#define ARDUINO_CORE_SERIALS_NUMBER 1U
#endif // ARDUINO_CORE_SERIALS_NUMBER

#define ARDUINO_CORE_DIGITAL_PORT "ArduinoPort"
#define ARDUINO_CORE_ADDRESS_PORT "ArduinoPort"
#define ARDUINO_CORE_UART_SERIAL "ArduinoSerial"

#define BaseCore2ArduinoCore(pThis) \
    CONTAINER_OF(pThis, ArduinoCore, base)

typedef struct {
    BaseCore base;
    ArduinoPort _ports[ARDUINO_CORE_PORTS_NUMBER];
    ArduinoSerial _serials[ARDUINO_CORE_SERIALS_NUMBER];
} ArduinoCore;

// Constructor(s) & Destructor(s)
PUBLIC void ArduinoCore_Construct(ArduinoCore *pThis);
PUBLIC void ArduinoCore_Destruct(ArduinoCore *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_CORE_H__
