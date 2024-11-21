#ifndef __ARDUINO_DIGITAL_PORT_H__
#define __ARDUINO_DIGITAL_PORT_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define ARDUINO_DIGITAL_PORTS_NUMBER 1

#define ARDUINO_DIGITAL_PORT_PARAMETER_BASE \
    {._reserved = BASE_PORT_PARAMETER_RESERVED}

#define BasePort2ArduinoDigitalPort(instance) \
    BASE2SUB(instance, ArduinoDigitalPort, base)

#define LinkedListNode2ArduinoDigitalPort(instance) \
    BasePort2ArduinoDigitalPort(LinkedListNode2BasePort(instance))

#define BasePortParameter2ArduinoDigitalPortParameter(instance) \
    BASE2SUB(instance, ArduinoDigitalPortParameter, base)

typedef struct {
    BasePort base;
    uint8_t *_port;
    uint8_t _mode;
    uint8_t _value;
} ArduinoDigitalPort;

typedef struct {
    BasePortParameter base;
    uint8_t *port;
} ArduinoDigitalPortParameter;

// Constructor(s) & Destructor(s)
PUBLIC void DestructArduinoDigitalPort(ArduinoDigitalPort *instance);

// Public method(s)
PUBLIC STATIC bool FindCallbackOfArduinoDigitalPort(
    LinkedListNode *node,
    const void *data);

PUBLIC STATIC ArduinoDigitalPort *InstanceOfArduinoDigitalPort(uint8_t *port);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_DIGITAL_PORT_H__
