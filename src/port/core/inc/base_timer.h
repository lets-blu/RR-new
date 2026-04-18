#ifndef __BASE_TIMER_H__
#define __BASE_TIMER_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BASE_TIMER_PARAMETER_RESERVED 0U

struct BaseTimerVtbl;

typedef struct {
    const struct BaseTimerVtbl *vtbl;
} BaseTimer;

typedef struct {
    unsigned int _reserved;
} BaseTimerParameter;

typedef struct BaseTimerVtbl {
    void (*Start)(BaseTimer *, unsigned long);
    void (*Stop)(BaseTimer *);
} BaseTimerVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void BaseTimer_Construct(
    BaseTimer *pThis,
    BaseTimerParameter *parameter);

PROTECTED void BaseTimer_Destruct(BaseTimer *pThis);

// Public method(s)
PUBLIC void BaseTimer_Start(BaseTimer *pThis, unsigned long delay);
PUBLIC void BaseTimer_Stop(BaseTimer *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_TIMER_H__
