#include "port/common/inc/base_task.h"

// Method implement(s)
PROTECTED void ConstructBaseTask(
    BaseTask *instance,
    BaseTaskParameter *parameter)
{
    (void)parameter;

    if (instance != NULL)
    {
        ConstructLinkedListNode(&instance->base);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBaseTask(BaseTask *instance)
{
    if (instance != NULL)
    {
        DestructLinkedListNode(&instance->base);
        memset(instance, 0, sizeof(BaseTask));
    }
}

PUBLIC void RunBaseTask(BaseTask *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Run == NULL)
    {
        return;
    }

    self->vtbl->Run(self);
}
