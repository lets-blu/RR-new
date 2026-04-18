#ifndef __NONE_TIMER_H__
#define __NONE_TIMER_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/event/inc/event_handler.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#include "port/core/inc/base_core.h"
#include "port/core/inc/base_timer.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define NONE_TIMER_PARAMETER_BASE {             \
    ._reserved = BASE_TIMER_PARAMETER_RESERVED, \
}

#define NONE_TIMER_IS_CONSTRUCTED(pThis) \
    ((pThis)->_handler != NULL)

#define LinkedListNode2NoneTimer(pThis) \
    CONTAINER_OF(pThis, NoneTimer, baseNode)

#define BaseTimer2NoneTimer(pThis) \
    CONTAINER_OF(pThis, NoneTimer, baseTimer)

#define BaseTimerParameter2NoneTimerParameter(pThis) \
    CONTAINER_OF(pThis, NoneTimerParameter, base)

typedef struct {
    LinkedListNode baseNode;
    BaseTimer baseTimer;
    EventHandler _handler;
    unsigned long _timeout;
} NoneTimer;

typedef struct {
    BaseTimerParameter base;
    EventHandler handler;
} NoneTimerParameter;

// Constructor(s) & Destructor(s)
PUBLIC void NoneTimer_Construct(
    NoneTimer *pThis,
    NoneTimerParameter *parameter);

PUBLIC void NoneTimer_Destruct(NoneTimer *pThis);

// Public method(s)
PUBLIC STATIC void NoneTimer_CheckTimers(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __NONE_TIMER_H__
