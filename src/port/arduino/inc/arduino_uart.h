#ifndef __ARDUINO_UART_H__
#define __ARDUINO_UART_H__

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <Arduino.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/ring_buffer.h"
#include "core/thread/inc/base_thread.h"

#include "port/common/inc/base_serial.h"
#include "utils/at_command/inc/at_command.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define ARDUINO_UART_PARAMETER_BASE \
    {BASE_SERIAL_PARAMETER_RESERVED}

#define BaseThread2ArduinoUARTThread(instance) \
    BASE2SUB(instance, ArduinoUARTThread, base)

#define BaseSerial2ArduinoUART(instance) \
    BASE2SUB(instance, ArduinoUART, base)

#define BaseSerialParameter2ArduinoUARTParameter(instance) \
    BASE2SUB(instance, ArduinoUARTParameter, base)

struct ArduinoUART;

typedef struct {
    BaseThread base;
    struct ArduinoUART *_uart;
} ArduinoUARTThread;

typedef struct ArduinoUART {
    BaseSerial base;
    HardwareSerial *_port;

    uint8_t *_rxBuffer;
    RingBuffer _rxRingBuffer;
    ArduinoUARTThread _thread;
} ArduinoUART;

typedef struct {
    BaseSerialParameter base;
    HardwareSerial *port;
    unsigned long baudrate;
    unsigned int rxBufferSize;
} ArduinoUARTParameter;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructArduinoUART(
    ArduinoUART *instance,
    ArduinoUARTParameter *parameter);

PUBLIC void DestructArduinoUART(ArduinoUART *instance);

PUBLIC void ConstructArduinoUARTThread(
    ArduinoUARTThread *instance,
    ArduinoUART *uart);

PUBLIC void DestructArduinoUARTThread(ArduinoUARTThread *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_UART_H__
