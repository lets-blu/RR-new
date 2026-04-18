#ifndef __NONE_SYSTEM_H__
#define __NONE_SYSTEM_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"

#include "port/core/inc/base_timer.h"
#include "port/core/inc/general_timer.h"
#include "port/system/inc/base_system.h"
#include "port/system/inc/base_task.h"
#include "port/system/inc/general_task.h"

#include "port/none/inc/none_task.h"
#include "port/none/inc/none_timer.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef NONE_SYSTEM_TIMERS_NUMBER
#define NONE_SYSTEM_TIMERS_NUMBER 2U
#endif // NONE_SYSTEM_TIMERS_NUMBER

#define NONE_SYSTEM_TASK "NoneTask"
#define NONE_SYSTEM_TIMER "NoneTimer"

#define BaseSystem2NoneSystem(pThis) \
    CONTAINER_OF(pThis, NoneSystem, base)

typedef struct {
    BaseSystem base;
    NoneTask _task;
    NoneTimer _timers[NONE_SYSTEM_TIMERS_NUMBER];
} NoneSystem;

// Constructor(s) & Destructor(s)
PUBLIC void NoneSystem_Construct(NoneSystem *pThis);
PUBLIC void NoneSystem_Destruct(NoneSystem *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __NONE_SYSTEM_H__
