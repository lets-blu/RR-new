#ifndef __BASE_COMPONENT_H__
#define __BASE_COMPONENT_H__

#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"
#include "port/core/inc/base_port.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define LinkedListNode2BaseComponent(pThis) \
    CONTAINER_OF(pThis, BaseComponent, base)

struct BaseComponentVtbl;

typedef struct {
    LinkedListNode base;
    const struct BaseComponentVtbl *vtbl;
} BaseComponent;

typedef struct BaseComponentVtbl {
    BasePort *(*CreatePort)(BaseComponent *, const char *, BasePortParameter *);
    void (*DestroyPort)(BaseComponent *, BasePort *);
} BaseComponentVtbl;

// Constructor(s) & Destructor(s)
PROTECTED void BaseComponent_Construct(BaseComponent *pThis);
PROTECTED void BaseComponent_Destruct(BaseComponent *pThis);

// Public method(s)
PUBLIC BasePort *BaseComponent_CreatePort(
    BaseComponent *pThis,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void BaseComponent_DestroyPort(BaseComponent *pThis, BasePort *port);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __BASE_COMPONENT_H__
