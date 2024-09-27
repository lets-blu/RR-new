#ifndef __ARDUINO_UART_H__
#define __ARDUINO_UART_H__

#include <stddef.h>
#include <string.h>
#include <Arduino.h>

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define ARDUINO_UART_PARAMETER_BASE \
    {BASE_SERIAL_PARAMETER_RESERVED}

#define BaseSerial2ArduinoUART(instance) \
    BASE2SUB(instance, ArduinoUART, base)

#define BaseSerialParameter2ArduinoUARTParameter(instance) \
    BASE2SUB(instance, ArduinoUARTParameter, base)

typedef struct {
    BaseSerial base;
    HardwareSerial *_port;
} ArduinoUART;

typedef struct {
    BaseSerialParameter base;
    HardwareSerial *port;
    unsigned long baudrate;
} ArduinoUARTParameter;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructArduinoUART(
    ArduinoUART *instance,
    ArduinoUARTParameter *parameter);

PUBLIC void DestructArduinoUART(ArduinoUART *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_UART_H__
