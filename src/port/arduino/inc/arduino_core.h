#ifndef __ARDUINO_CORE_H__
#define __ARDUINO_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_core.h"
#include "port/arduino/inc/arduino_port.h"

#define ARDUINO_CORE_DIGITAL_PORT "ArduinoDPort"

#define BaseCore2ArduinoCore(instance) \
    BASE2SUB(instance, ArduinoCore, base)

typedef struct {
    BaseCore base;
} ArduinoCore;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructArduinoCore(ArduinoCore *instance);
PUBLIC void DestructArduinoCore(ArduinoCore *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_CORE_H__
