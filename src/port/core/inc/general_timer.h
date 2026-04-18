#ifndef __GENERAL_TIMER_H__
#define __GENERAL_TIMER_H__

#include "core/event/inc/event_handler.h"
#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_timer.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GENERAL_HARDWARE_TIMER "GeneralHardwareTimer"
#define GENERAL_SOFTWARE_TIMER "GeneralSoftwareTimer"

#define GENERAL_TIMER_PARAMETER_BASE {          \
    ._reserved = BASE_TIMER_PARAMETER_RESERVED, \
}

#define BaseTimerParameter2GeneralTimerParameter(pThis) \
    CONTAINER_OF(pThis, GeneralTimerParameter, base)

typedef struct {
    BaseTimerParameter base;
    EventHandler handler;
} GeneralTimerParameter;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GENERAL_TIMER_H__
