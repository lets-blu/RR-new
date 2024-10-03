#ifndef __GENERAL_TASK_H__
#define __GENERAL_TASK_H__

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_task.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define GENERAL_TASK "GeneralTask"

#define GENERAL_TASK_PARAMETER_BASE \
    {BASE_TASK_PARAMETER_RESERVED}

#define BaseTaskParameter2GeneralTaskParameter(instance) \
    BASE2SUB(instance, GeneralTaskParameter, base)

typedef struct {
    BaseTaskParameter base;
    void *entry;
    void *parameter;
} GeneralTaskParameter;

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GENERAL_TASK_H__
