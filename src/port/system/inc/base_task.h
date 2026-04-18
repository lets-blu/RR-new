#ifndef __BASE_TASK_H__
#define __BASE_TASK_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define BASE_TASK_PARAMETER_RESERVED 0U

struct BaseTaskVtbl;

typedef struct {
    const struct BaseTaskVtbl *vtbl;
} BaseTask;

typedef struct {
    unsigned int _reserved;
} BaseTaskParameter;

typedef struct BaseTaskVtbl {
    void (*Start)(BaseTask *);
} BaseTaskVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void BaseTask_Construct(
    BaseTask *pThis,
    BaseTaskParameter *parameter);

PROTECTED void BaseTask_Destruct(BaseTask *pThis);

// Public method(s)
PUBLIC void BaseTask_Start(BaseTask *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_TASK_H__
