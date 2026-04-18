#include "port/none/inc/none_task.h"

// Override method(s)
PUBLIC void NoneTask_Start(BaseTask *task);

// Virtual methods table(s)
static const BaseTaskVtbl baseVtbl = {
    .Start = NoneTask_Start,
};

// Method implement(s)
PUBLIC void NoneTask_Construct(NoneTask *pThis, NoneTaskParameter *parameter)
{
    if (pThis == NULL || parameter == NULL) {
        return;
    }

    BaseTask_Construct(&pThis->base, &parameter->base);
    pThis->base.vtbl = &baseVtbl;

    pThis->_entry = parameter->entry;
    pThis->_parameter = parameter->parameter;
}

PUBLIC void NoneTask_Destruct(NoneTask *pThis)
{
    if (pThis != NULL) {
        BaseTask_Destruct(&pThis->base);
        memset(pThis, 0, sizeof(NoneTask));
    }
}

PUBLIC void NoneTask_Start(BaseTask *task)
{
    NoneTask *pThis = BaseTask2NoneTask(task);

    if (task != NULL && pThis->_entry != NULL) {
        pThis->_entry(pThis->_parameter);
    }
}
