#ifndef __ARDUINO_PORT_H__
#define __ARDUINO_PORT_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <Arduino.h>

#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define ARDUINO_PORT_PARAMETER_BASE {          \
    ._reserved = BASE_PORT_PARAMETER_RESERVED, \
}

#define ARDUINO_PORT_IS_CONSTRUCTED(pThis) \
    ((pThis)->base.vtbl != NULL)

#define BasePort2ArduinoPort(pThis) \
    CONTAINER_OF(pThis, ArduinoPort, base)

#define BasePortParameter2ArduinoPortParameter(pThis) \
    CONTAINER_OF(pThis, ArduinoPortParameter, base)

#if defined(ARDUINO_ARCH_AVR)
#define ARDUINO_PORT_GET_AVR_PIN(port) ((volatile uint8_t *)(port) - 2)
#define ARDUINO_PORT_GET_AVR_DDR(port) ((volatile uint8_t *)(port) - 1)
#define ARDUINO_PORT_GET_AVR_PORT(port) ((volatile uint8_t *)(port))
#define ARDUINO_PORT_AVR_PORTS_NUMBER sizeof(avrPorts) / sizeof(avrPorts[0])
#endif // ARDUINO_ARCH_AVR

typedef struct {
    BasePort base;
    void *_port;
} ArduinoPort;

typedef struct {
    BasePortParameter base;
    void *port;
} ArduinoPortParameter;

// Constructor(s) & Destructor(s)
PUBLIC void ArduinoPort_Construct(
    ArduinoPort *pThis,
    ArduinoPortParameter *parameter);

PUBLIC void ArduinoPort_Destruct(ArduinoPort *pThis);

// Public method(s)
PUBLIC void *ArduinoPort_GetPort(ArduinoPort *pThis);
PUBLIC STATIC bool ArduinoPort_IsValidPort(void *port);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_PORT_H__
