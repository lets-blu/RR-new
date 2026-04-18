#ifndef __BASE_SYSTEM_H__
#define __BASE_SYSTEM_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "port/core/inc/base_timer.h"
#include "port/system/inc/base_task.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct BaseSystemVtbl;

typedef struct {
    const struct BaseSystemVtbl *vtbl;
} BaseSystem;

typedef struct BaseSystemVtbl {
    BaseTask *(*CreateTask)(BaseSystem *, const char *, BaseTaskParameter *);
    void (*DestroyTask)(BaseSystem *, BaseTask *);
    BaseTimer *(*CreateTimer)(BaseSystem *, const char *, BaseTimerParameter *);
    void (*DestroyTimer)(BaseSystem *, BaseTimer *);
    void (*Run)(BaseSystem *);
} BaseSystemVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void BaseSystem_Construct(BaseSystem *pThis);
PROTECTED void BaseSystem_Destruct(BaseSystem *pThis);

// Public method(s)
PUBLIC BaseTask *BaseSystem_CreateTask(
    BaseSystem *pThis,
    const char *type,
    BaseTaskParameter *parameter);

PUBLIC void BaseSystem_DestroyTask(BaseSystem *pThis, BaseTask *task);

PUBLIC BaseTimer *BaseSystem_CreateTimer(
    BaseSystem *pThis,
    const char *type,
    BaseTimerParameter *parameter);

PUBLIC void BaseSystem_DestroyTimer(BaseSystem *pThis, BaseTimer *timer);

PUBLIC void BaseSystem_Run(BaseSystem *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_SYSTEM_H__
