#ifndef __ARDUINO_DIGITAL_PORT_H__
#define __ARDUINO_DIGITAL_PORT_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define ARDUINO_DIGITAL_PORT_PARAMETER_BASE \
    {._reserved = BASE_PORT_PARAMETER_RESERVED}

#define IS_ARDUINO_DIGITAL_PORT_CONSTRUCTED(instance) \
    ((instance)->base.vtbl != NULL)

#define BasePort2ArduinoDigitalPort(instance) \
    BASE2SUB(instance, ArduinoDigitalPort, base)

#define BasePortParameter2ArduinoDigitalPortParameter(instance) \
    BASE2SUB(instance, ArduinoDigitalPortParameter, base)

typedef struct {
    BasePort base;
} ArduinoDigitalPort;

typedef struct {
    BasePortParameter base;
} ArduinoDigitalPortParameter;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructArduinoDigitalPort(
    ArduinoDigitalPort *instance,
    ArduinoDigitalPortParameter *parameter);

PUBLIC void DestructArduinoDigitalPort(ArduinoDigitalPort *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_DIGITAL_PORT_H__
