#include "port/system/inc/base_task.h"

// Method implement(s)
PROTECTED void BaseTask_Construct(
    BaseTask *pThis,
    BaseTaskParameter *parameter)
{
    (void)parameter;

    if (pThis != NULL) {
        pThis->vtbl = NULL;
    }
}

PROTECTED void BaseTask_Destruct(BaseTask *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(BaseTask));
    }
}

PUBLIC void BaseTask_Start(BaseTask *pThis)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->Start != NULL) {
        pThis->vtbl->Start(pThis);
    }
}
