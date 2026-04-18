#ifndef __GENERAL_TASK_H__
#define __GENERAL_TASK_H__

#include "core/utils/inc/keywords.h"
#include "port/system/inc/base_task.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GENERAL_TASK "GeneralTask"

#define GENERAL_TASK_PARAMETER_BASE {           \
    ._reserved = BASE_TIMER_PARAMETER_RESERVED, \
}

#define BaseTaskParameter2GeneralTaskParameter(pThis) \
    CONTAINER_OF(pThis, GeneralTaskParameter, base)

typedef struct {
    BaseTaskParameter base;
    void (*entry)(void *);
    void *parameter;
} GeneralTaskParameter;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GENERAL_TASK_H__
