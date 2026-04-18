#ifndef __NONE_TASK_H__
#define __NONE_TASK_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "port/system/inc/base_task.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define NONE_TASK_PARAMETER_BASE {             \
    ._reserved = BASE_TASK_PARAMETER_RESERVED, \
}

#define NONE_TASK_IS_CONSTRUCTED(pThis) \
    ((pThis)->base.vtbl != NULL)

#define BaseTask2NoneTask(pThis) \
    CONTAINER_OF(pThis, NoneTask, base)

#define BaseTaskParameter2NoneTaskParameter(pThis) \
    CONTAINER_OF(pThis, NoneTaskParameter, base)

typedef struct {
    BaseTask base;
    void (*_entry)(void *);
    void *_parameter;
} NoneTask;

typedef struct {
    BaseTaskParameter base;
    void (*entry)(void *);
    void *parameter;
} NoneTaskParameter;

typedef void (*NoneTaskEntry)(void *);

// Constructor(s) & Destructor(s)
PUBLIC void NoneTask_Construct(NoneTask *pThis, NoneTaskParameter *parameter);
PUBLIC void NoneTask_Destruct(NoneTask *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __NONE_TASK_H__
