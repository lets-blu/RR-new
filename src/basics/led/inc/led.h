#ifndef __LED_H__
#define __LED_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/device/inc/device_manager.h"

#include "port/common/inc/base_factory.h"
#include "port/common/inc/base_port.h"
#include "port/general/inc/general_port.h"

#include "utils/logger/inc/logger.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
    BasePort *_port;
    unsigned int _pin;
    unsigned int _onValue;
} LED;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructLED(
    LED *instance,
    void *port,
    unsigned int pin,
    unsigned int onValue);

PUBLIC void DestructLED(LED *instance);

// Public method(s)
PUBLIC void TurnOnLED(LED *self);
PUBLIC void TurnOffLED(LED *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LED_H__
