#ifndef __ARDUINO_UART_SERIAL_H__
#define __ARDUINO_UART_SERIAL_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/ring_buffer.h"
#include "port/common/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define ARDUINO_UART_SERIAL_PARAMETER_BASE              \
    {._reserved = BASE_SERIAL_PARAMETER_RESERVED}

#define IS_ARDUINO_UART_SERIAL_CONSTRUCTED(instance)    \
    ((instance)->base.vtbl != NULL)

#define BaseSerial2ArduinoUARTSerial(instance)          \
    BASE2SUB(instance, ArduinoUARTSerial, base)

#define BaseSerialParameter2ArduinoUARTSerialParameter(instance) \
    BASE2SUB(instance, ArduinoUARTSerialParameter, base)

typedef struct {
    BaseSerial base;
    RingBuffer *_buffer;
    LinkedList _handlers;
} ArduinoUARTSerial;

typedef struct {
    BaseSerialParameter base;
    unsigned long baudrate;
    RingBuffer *buffer;
} ArduinoUARTSerialParameter;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructArduinoUARTSerial(
    ArduinoUARTSerial *instance,
    ArduinoUARTSerialParameter *parameter);

PUBLIC void DestructArduinoUARTSerial(ArduinoUARTSerial *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_UART_SERIAL_H__
