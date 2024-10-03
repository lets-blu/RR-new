#ifndef __NONE_SYSTEM_H__
#define __NONE_SYSTEM_H__

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"

#include "port/common/inc/base_system.h"
#include "port/common/inc/base_task.h"
#include "port/general/inc/general_task.h"
#include "port/none/inc/none_task.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define NONE_SYSTEM_TASK "NoneTask"

#define BaseSystem2NoneSystem(instance) \
    BASE2SUB(instance, NoneSystem, base)

#define BaseFactory2NoneSystem(instance) \
    BaseSystem2NoneSystem(BaseFactory2BaseSystem(instance))

typedef struct {
    BaseSystem base;
    NoneTask _task;
} NoneSystem;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructNoneSystem(NoneSystem *instance);
PROTECTED void DestructNoneSystem(NoneSystem *instance);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __NONE_SYSTEM_H__
