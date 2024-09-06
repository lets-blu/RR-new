#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/device/inc/device_manager.h"

#include "port/common/inc/base_factory.h"
#include "port/common/inc/base_port.h"

typedef struct {
    BasePort *_port;
    unsigned int _onValue;
} LED;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructLED(
    LED *instance,
    const char *type,
    BasePortParameter *parameter,
    unsigned int onValue);

PUBLIC void DestructLED(LED *instance);

// Public method(s)
PUBLIC void TurnOnLED(LED *self);
PUBLIC void TurnOffLED(LED *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LED_H__
