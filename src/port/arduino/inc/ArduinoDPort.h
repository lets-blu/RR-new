#ifndef __ARDUINO_D_PORT_H__
#define __ARDUINO_D_PORT_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/common/inc/Keywords.h"
#include "port/common/inc/BasePort.h"

#define ARDUINO_D_PORT_PARAMETER_BASE {BASE_PORT_PARAMETER_RESERVED}

#define BasePort2ArduinoDPort(instance) \
    BASE2SUB(instance, ArduinoDPort, base)

#define BasePortParameter2ArduinoDPortParameter(instance) \
    BASE2SUB(instance, ArduinoDPortParameter, base)

typedef struct {
    BasePort base;
    uint8_t _pin;
} ArduinoDPort;

typedef struct {
    BasePortParameter base;
    uint8_t pin;
} ArduinoDPortParameter;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructArduinoDPort(
    ArduinoDPort *instance,
    ArduinoDPortParameter *parameter);

PUBLIC void DestructArduinoDPort(ArduinoDPort *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_D_PORT_H__
