#include "port/none/inc/none_task.h"

// Override method(s)
PUBLIC void RunNoneTaskBase(BaseTask *task);

// Virtual methods table
static const BaseTaskVtbl baseVtbl = {
    .Run = RunNoneTaskBase
};

// Method implement(s)
PUBLIC void ConstructNoneTask(NoneTask *instance, NoneTaskParameter *parameter)
{
    if (instance == NULL || parameter == NULL)
    {
        return;
    }

    ConstructBaseTask(&instance->base, &parameter->base);
    instance->base.vtbl = &baseVtbl;

    instance->_entry = parameter->entry;
    instance->_parameter = parameter->parameter;
}

PUBLIC void DestructNoneTask(NoneTask *instance)
{
    if (instance != NULL)
    {
        DestructBaseTask(&instance->base);
        memset(instance, 0, sizeof(NoneTask));
    }
}

PUBLIC void RunNoneTaskBase(BaseTask *task)
{
    NoneTask *self = BaseTask2NoneTask(task);

    if (task != NULL && self->_entry != NULL)
    {
        self->_entry(self->_parameter);
    }
}
