#ifndef __BASE_TASK_H__
#define __BASE_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <string.h>
#include "core/common/inc/Keywords.h"

#define BASE_TASK_PARAMETER_RESERVED 0

struct BaseTaskVtbl;

typedef struct {
    const struct BaseTaskVtbl *vtbl;
} BaseTask;

typedef struct {
    unsigned int _reserved;
} BaseTaskParameter;

typedef struct BaseTaskVtbl {
    void (*Run)(BaseTask *);
} BaseTaskVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBaseTask(
    BaseTask *instance,
    BaseTaskParameter *parameter);

PROTECTED void DestructBaseTask(BaseTask *instance);

// Public method(s)
PUBLIC void RunBaseTask(BaseTask *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_TASK_H__
