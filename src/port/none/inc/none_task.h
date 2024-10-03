#ifndef __NONE_TASK_H__
#define __NONE_TASK_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_task.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define NONE_TASK_PARAMETER_BASE \
    {BASE_TASK_PARAMETER_RESERVED}

#define IS_NONE_TASK_CONSTRUCTED(instance) \
    ((instance)->_entry != NULL)

#define BaseTask2NoneTask(instance) \
    BASE2SUB(instance, NoneTask, base)

#define BaseTaskParameter2NoneTaskParameter(instance) \
    BASE2SUB(instance, NoneTaskParameter, base)

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
PUBLIC void ConstructNoneTask(NoneTask *instance, NoneTaskParameter *parameter);
PUBLIC void DestructNoneTask(NoneTask *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __NONE_TASK_H__
