#include "port/none/inc/none_system.h"

// Private method(s)
PRIVATE NoneTimer *NoneSystem_AllocTimer(NoneSystem *pThis);

// Override method(s)
PUBLIC BaseTask *NoneSystem_CreateTask(
    BaseSystem *system,
    const char *type,
    BaseTaskParameter *parameter);

PUBLIC void NoneSystem_DestroyTask(BaseSystem *system, BaseTask *task);

PUBLIC BaseTimer *NoneSystem_CreateTimer(
    BaseSystem *system,
    const char *type,
    BaseTimerParameter *parameter);

PUBLIC void NoneSystem_DestroyTimer(BaseSystem *system, BaseTimer *timer);

PUBLIC void NoneSystem_Run(BaseSystem *system);

// Virtual methods table(s)
static const BaseSystemVtbl baseVtbl = {
    .CreateTask = NoneSystem_CreateTask,
    .DestroyTask = NoneSystem_DestroyTask,
    .CreateTimer = NoneSystem_CreateTimer,
    .DestroyTimer = NoneSystem_DestroyTimer,
    .Run = NoneSystem_Run,
};

// Method implement(s)
PUBLIC void NoneSystem_Construct(NoneSystem *pThis)
{
    if (pThis == NULL) {
        return;
    }

    BaseSystem_Construct(&pThis->base);
    pThis->base.vtbl = &baseVtbl;

    memset(&pThis->_task, 0, sizeof(NoneTask));
    memset(&pThis->_timers, 0, NONE_SYSTEM_TIMERS_NUMBER * sizeof(NoneTimer));
}

PUBLIC void NoneSystem_Destruct(NoneSystem *pThis)
{
    if (pThis != NULL) {
        BaseSystem_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(NoneSystem));
    }
}

PRIVATE NoneTimer *NoneSystem_AllocTimer(NoneSystem *pThis)
{
    for (unsigned int i = 0; i < NONE_SYSTEM_TIMERS_NUMBER; i++) {
        if (!NONE_TIMER_IS_CONSTRUCTED(&pThis->_timers[i])) {
            return &pThis->_timers[i];
        }
    }

    return NULL;
}

PUBLIC BaseTask *NoneSystem_CreateTask(
    BaseSystem *system,
    const char *type,
    BaseTaskParameter *parameter)
{
    NoneSystem *pThis = BaseSystem2NoneSystem(system);

    if (system == NULL || type == NULL || parameter == NULL) {
        return NULL;
    }

    if (strcmp(type, NONE_SYSTEM_TASK) == 0) {
        if (!NONE_TASK_IS_CONSTRUCTED(&pThis->_task)) {
            NoneTask_Construct(
                &pThis->_task,
                BaseTaskParameter2NoneTaskParameter(parameter));

            return &pThis->_task.base;
        }
    } else if (strcmp(type, GENERAL_TASK) == 0) {
        GeneralTaskParameter *generalPatameter
            = BaseTaskParameter2GeneralTaskParameter(parameter);

        NoneTaskParameter noneParameter = {
            .base = NONE_TASK_PARAMETER_BASE,
            .entry = generalPatameter->entry,
            .parameter = generalPatameter->parameter,
        };

        if (!NONE_TASK_IS_CONSTRUCTED(&pThis->_task)) {
            NoneTask_Construct(&pThis->_task, &noneParameter);
            return &pThis->_task.base;
        }
    }

    return NULL;
}

PUBLIC void NoneSystem_DestroyTask(BaseSystem *system, BaseTask *task)
{
    NoneSystem *pThis = BaseSystem2NoneSystem(system);

    if (system == NULL || task == NULL) {
        return;
    }

    if (task == &pThis->_task.base) {
        NoneTask_Destruct(&pThis->_task);
    }
}

PUBLIC BaseTimer *NoneSystem_CreateTimer(
    BaseSystem *system,
    const char *type,
    BaseTimerParameter *parameter)
{
    NoneTimer *timer = NULL;
    NoneSystem *pThis = BaseSystem2NoneSystem(system);

    if (system == NULL || type == NULL || parameter == NULL) {
        return NULL;
    }

    if (strcmp(type, NONE_SYSTEM_TIMER) == 0) {
        timer = NoneSystem_AllocTimer(pThis);

        if (timer != NULL) {
            NoneTimer_Construct(
                timer,
                BaseTimerParameter2NoneTimerParameter(parameter));
        }
    } else if (strcmp(type, GENERAL_SOFTWARE_TIMER) == 0) {
        GeneralTimerParameter *generalPatameter
            = BaseTimerParameter2GeneralTimerParameter(parameter);

        NoneTimerParameter noneParameter = {
            .base = NONE_TIMER_PARAMETER_BASE,
            .handler = generalPatameter->handler,
        };

        timer = NoneSystem_AllocTimer(pThis);

        if (timer != NULL) {
            NoneTimer_Construct(timer, &noneParameter);
        }
    }

    return (timer == NULL) ? NULL : &timer->baseTimer;
}

PUBLIC void NoneSystem_DestroyTimer(BaseSystem *system, BaseTimer *timer)
{
    NoneSystem *pThis = BaseSystem2NoneSystem(system);

    if (system == NULL || timer == NULL) {
        return;
    }

    for (unsigned int i = 0; i < NONE_SYSTEM_TIMERS_NUMBER; i++) {
        if (timer == &pThis->_timers[i].baseTimer) {
            NoneTimer_Destruct(&pThis->_timers[i]);
            break;
        }
    }
}

PUBLIC void NoneSystem_Run(BaseSystem *system)
{
    (void)system;
    NoneTimer_CheckTimers();
}
