#include "port/core/inc/base_timer.h"

// Method implement(s)
PROTECTED void BaseTimer_Construct(
    BaseTimer *pThis,
    BaseTimerParameter *parameter)
{
    (void)parameter;

    if (pThis != NULL) {
        pThis->vtbl = NULL;
    }
}

PROTECTED void BaseTimer_Destruct(BaseTimer *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(BaseTimer));
    }
}

PUBLIC void BaseTimer_Start(BaseTimer *pThis, unsigned long delay)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->Start != NULL) {
        pThis->vtbl->Start(pThis, delay);
    }
}

PUBLIC void BaseTimer_Stop(BaseTimer *pThis)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->Stop != NULL) {
        pThis->vtbl->Stop(pThis);
    }
}
