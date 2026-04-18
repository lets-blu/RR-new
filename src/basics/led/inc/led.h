#ifndef __LED_H__
#define __LED_H__

#include <stddef.h>
#include <string.h>

#include "core/device/inc/device_factory.h"
#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/general_port.h"

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
PUBLIC void LED_Construct(
    LED *pThis,
    void *port,
    unsigned int pin,
    unsigned int onValue);

PUBLIC void LED_Destruct(LED *pThis);

// Public method(s)
PUBLIC void LED_TurnOn(LED *pThis);
PUBLIC void LED_TurnOff(LED *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LED_H__
