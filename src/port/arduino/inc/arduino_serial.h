#ifndef __ARDUINO_SERIAL_H__
#define __ARDUINO_SERIAL_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <Arduino.h>

#include "core/event/inc/event_handler.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/ring_buffer.h"

#include "port/core/inc/base_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define ARDUINO_SERIAL_BUFFER_SIZE 80

#define ARDUINO_SERIAL_PARAMETER_BASE {          \
    ._reserved = BASE_SERIAL_PARAMETER_RESERVED, \
}

#define ARDUINO_SERIAL_IS_CONSTRUCTED(pThis) \
    ((pThis)->base.vtbl != NULL)

#define BaseSerial2ArduinoSerial(pThis) \
    CONTAINER_OF(pThis, ArduinoSerial, base)

#define BaseSerialParameter2ArduinoSerialParameter(pThis) \
    CONTAINER_OF(pThis, ArduinoSerialParameter, base)

typedef struct {
    BaseSerial base;
    HardwareSerial *_serial;
    RingBuffer _rxBuffer;
    EventHandler _handler;
} ArduinoSerial;

typedef struct {
    BaseSerialParameter base;
    HardwareSerial *serial;
    unsigned long baudrate;
    uint8_t *rxBuffer;
    size_t rxBufferSize;
} ArduinoSerialParameter;

// Constructor(s) & Destructor(s)
PUBLIC void ArduinoSerial_Construct(
    ArduinoSerial *pThis,
    ArduinoSerialParameter *parameter);

PUBLIC void ArduinoSerial_Destruct(ArduinoSerial *pThis);

// Public method(s)
PUBLIC void ArduinoSerial_Sample(ArduinoSerial *pThis);
PUBLIC HardwareSerial *ArduinoSerial_GetSerial(ArduinoSerial *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_SERIAL_H__
