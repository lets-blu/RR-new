#include "port/component/inc/base_component.h"

// Method implement(s)
PROTECTED void BaseComponent_Construct(BaseComponent *pThis)
{
    if (pThis != NULL) {
        LinkedListNode_Construct(&pThis->base);
        pThis->vtbl = NULL;
    }
}

PROTECTED void BaseComponent_Destruct(BaseComponent *pThis)
{
    if (pThis != NULL) {
        LinkedListNode_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(BaseComponent));
    }
}

PUBLIC BasePort *BaseComponent_CreatePort(
    BaseComponent *pThis,
    const char *type,
    BasePortParameter *parameter)
{
    if (pThis == NULL
        || pThis->vtbl == NULL
        || pThis->vtbl->CreatePort == NULL) {
        return NULL;
    }

    return pThis->vtbl->CreatePort(pThis, type, parameter);
}

PUBLIC void BaseComponent_DestroyPort(BaseComponent *pThis, BasePort *port)
{
    if (pThis != NULL
        && pThis->vtbl != NULL
        && pThis->vtbl->DestroyPort != NULL) {
        pThis->vtbl->DestroyPort(pThis, port);
    }
}
