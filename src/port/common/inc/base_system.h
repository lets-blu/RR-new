#ifndef __BASE_SYSTEM_H__
#define __BASE_SYSTEM_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "port/common/inc/base_factory.h"

#define BaseFactory2BaseSystem(instance) \
    BASE2SUB(instance, BaseSystem, base)

struct BaseSystemVtbl;

typedef struct {
    BaseFactory base;
    const struct BaseSystemVtbl* vtbl;
} BaseSystem;

typedef struct BaseSystemVtbl {
    void (*Run)(BaseSystem *);
    const char *(*GetName)(BaseSystem *);
} BaseSystemVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void ConstructBaseSystem(BaseSystem *instance);
PROTECTED void DestructBaseSystem(BaseSystem *instance);

// Public Method(s)
PUBLIC void RunBaseSystem(BaseSystem *self);
PUBLIC const char *GetNameOfBaseSystem(BaseSystem *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_SYSTEM_H__
