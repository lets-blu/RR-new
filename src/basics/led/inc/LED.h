#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "core/common/inc/Keywords.h"
#include "core/device/inc/DeviceManager.h"

#include "port/common/inc/BaseFactory.h"
#include "port/common/inc/BasePort.h"

typedef struct {
    BasePort *_port;
    unsigned int _onValue;
} LED;

// Constructor(s) & Destructor(s)
PUBLIC void ConstructLED(
    LED *instance,
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
