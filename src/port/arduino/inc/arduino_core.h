#ifndef __ARDUINO_CORE_H__
#define __ARDUINO_CORE_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/thread/inc/base_thread.h"

#include "port/common/inc/base_core.h"
#include "port/common/inc/base_task.h"
#include "port/general/inc/general_port.h"
#include "port/general/inc/general_uart_serial.h"

#include "port/arduino/inc/arduino_digital_port.h"
#include "port/arduino/inc/arduino_uart_serial.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define ARDUINO_CORE_DIGITAL_PORT   "ArduinoDigitalPort"
#define ARDUINO_CORE_UART_SERIAL    "ArduinoUARTSerial"

#define BaseCore2ArduinoCore(instance)          \
    BASE2SUB(instance, ArduinoCore, base)

#define BaseFactory2ArduinoCore(instance)       \
    BaseCore2ArduinoCore(BaseFactory2BaseCore(instance))

#define BaseThread2ArduinoCoreThread(instance)  \
    BASE2SUB(instance, ArduinoCoreThread, base)

struct ArduinoCore;

typedef struct {
    BaseThread base;
    struct ArduinoCore *_core;
} ArduinoCoreThread;

typedef struct ArduinoCore {
    BaseCore base;
    ArduinoCoreThread _thread;
    ArduinoDigitalPort _digitalPort;
    ArduinoUARTSerial _uartSerial;
} ArduinoCore;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructArduinoCore(ArduinoCore *instance);
PUBLIC void DestructArduinoCore(ArduinoCore *instance);

PUBLIC void ConstructArduinoCoreThread(
    ArduinoCoreThread *instance,
    ArduinoCore *core);

PUBLIC void DestructArduinoCoreThread(ArduinoCoreThread *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ARDUINO_CORE_H__
