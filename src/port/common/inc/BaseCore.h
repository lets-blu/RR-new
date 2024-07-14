#ifndef __BASE_CORE_H__
#define __BASE_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <string.h>

#include "core/common/inc/Keywords.h"
#include "port/common/inc/BaseFactory.h"

#define BaseFactory2BaseCore(instance) \
    BASE2SUB(instance, BaseCore, base)

struct BaseCoreVtbl;

typedef struct {
    BaseFactory base;
    const struct BaseCoreVtbl *vtbl;
} BaseCore;

typedef struct BaseCoreVtbl {
    const char *(*GetName)(BaseCore *);    
} BaseCoreVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBaseCore(BaseCore *instance);
PROTECTED void DestructBaseCore(BaseCore *instance);

// Public method(s)
PUBLIC const char *GetNameOfBaseCore(BaseCore *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_CORE_H__
