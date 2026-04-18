#include "core/coroutine/inc/linked_coroutine.h"

// Method implement(s)
PROTECTED void LinkedCoroutine_Construct(LinkedCoroutine *pThis)
{
    if (pThis != NULL) {
        LinkedListNode_Construct(&pThis->base);
        Coroutine_Construct(&pThis->_coroutine);
        pThis->vtbl = NULL;
    }
}

PROTECTED void LinkedCoroutine_Destruct(LinkedCoroutine *pThis)
{
    if (pThis != NULL) {
        LinkedListNode_Destruct(&pThis->base);
        Coroutine_Destruct(&pThis->_coroutine);
        memset(pThis, 0, sizeof(LinkedCoroutine));
    }
}

PUBLIC CoroutineState LinkedCoroutine_Run(LinkedCoroutine *pThis)
{
    if (pThis == NULL || pThis->vtbl == NULL || pThis->vtbl->Run == NULL) {
        return COROUTINE_STATE_ENDED;
    }

    return pThis->vtbl->Run(pThis);
}
