#include "port/system/inc/base_system.h"

// Method implement(s)
PROTECTED void BaseSystem_Construct(BaseSystem *pThis)
{
    if (pThis != NULL) {
        pThis->vtbl = NULL;
    }
}

PROTECTED void BaseSystem_Destruct(BaseSystem *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(BaseSystem));
    }
}

PUBLIC BaseTask *BaseSystem_CreateTask(
    BaseSystem *pThis,
    const char *type,
    BaseTaskParameter *parameter)
{
    if (pThis == NULL
        || pThis->vtbl == NULL
        || pThis->vtbl->CreateTask == NULL) {
        return NULL;
    }

    return pThis->vtbl->CreateTask(pThis, type, parameter);
}

PUBLIC void BaseSystem_DestroyTask(BaseSystem *pThis, BaseTask *task)
{
    if (pThis != NULL
        && pThis->vtbl != NULL
        && pThis->vtbl->DestroyTask != NULL) {
        pThis->vtbl->DestroyTask(pThis, task);
    }
}

PUBLIC BaseTimer *BaseSystem_CreateTimer(
    BaseSystem *pThis,
    const char *type,
    BaseTimerParameter *parameter)
{
    if (pThis == NULL
        || pThis->vtbl == NULL
        || pThis->vtbl->CreateTimer == NULL) {
        return NULL;
    }

    return pThis->vtbl->CreateTimer(pThis, type, parameter);
}

PUBLIC void BaseSystem_DestroyTimer(BaseSystem *pThis, BaseTimer *timer)
{
    if (pThis != NULL
        && pThis->vtbl != NULL
        && pThis->vtbl->DestroyTimer != NULL) {
        pThis->vtbl->DestroyTimer(pThis, timer);
    }
}

PUBLIC void BaseSystem_Run(BaseSystem *pThis)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->Run != NULL) {
        pThis->vtbl->Run(pThis);
    }
}
