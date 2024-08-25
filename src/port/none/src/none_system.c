#include "port/none/inc/none_system.h"

// Override method(s)
PUBLIC void RunNoneSystemBase(
    BaseSystem *sys);

PUBLIC const char *GetNameOfNoneSystemBase(
    BaseSystem *sys);

PUBLIC BaseTask *CreateTaskWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseTaskParameter *parameter);

PUBLIC void DestroyTaskWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseTask *task);

// Virtual methods table
static const BaseSystemVtbl baseSystemVtbl = {
    .Run = RunNoneSystemBase,
    .GetName = GetNameOfNoneSystemBase
};

static const BaseFactoryVtbl baseFactoryVtbl = {
    .CreateTask = CreateTaskWithNoneSystemBase,
    .DestroyTask = DestroyTaskWithNoneSystemBase
};

// Method implement(s)
PROTECTED void ConstructNoneSystem(NoneSystem *instance)
{
    if (instance == NULL)
    {
        return;
    }

    ConstructBaseSystem(&instance->base);
    instance->base.vtbl = &baseSystemVtbl;
    instance->base.base.vtbl = &baseFactoryVtbl;

    instance->_task = NULL;
}

PROTECTED void DestructNoneSystem(NoneSystem *instance)
{
    if (instance != NULL)
    {
        DestructBaseSystem(&instance->base);
        memset(instance, 0, sizeof(NoneSystem));
    }
}

PUBLIC void RunNoneSystemBase(
    BaseSystem *sys)
{
    NoneSystem *self = BaseSystem2NoneSystem(sys);

    if (sys != NULL && self->_task != NULL)
    {
        RunBaseTask(&self->_task->base);
    }
}

PUBLIC const char *GetNameOfNoneSystemBase(
    BaseSystem *sys)
{
    (void)sys;
    return "None";
}

PUBLIC BaseTask *CreateTaskWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseTaskParameter *parameter)
{
    NoneSystem *self = BaseSystem2NoneSystem(factory);

    if (factory == NULL || self->_task != NULL)
    {
        return NULL;
    }

    if (strcmp(type, NONE_SYSTEM_TASK) == 0)
    {
        self->_task = (NoneTask *)malloc(sizeof(NoneTask));

        if (self->_task != NULL)
        {
            ConstructNoneTask(
                self->_task,
                BaseTaskParameter2NoneTaskParameter(parameter));
        }
    }
    else if (strcmp(type, GENERAL_TASK) == 0)
    {
        GeneralTaskParameter *generalParameter
            = BaseTaskParameter2GeneralTaskParameter(parameter);

        NoneTaskParameter noneParameter = {
            .base = NONE_TASK_PARAMETER_BASE,
            .entry = generalParameter->entry,
            .parameter = generalParameter->parameter
        };

        self->_task = (NoneTask *)malloc(sizeof(NoneTask));

        if (self->_task != NULL)
        {
            ConstructNoneTask(self->_task, &noneParameter);
        }
    }

    return &self->_task->base;
}

PUBLIC void DestroyTaskWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseTask *task)
{
    NoneSystem *self = BaseSystem2NoneSystem(factory);

    if (factory != NULL && BaseTask2NoneTask(task) == self->_task)
    {
        DestructNoneTask(self->_task);
        free(self->_task);
        self->_task = NULL;
    }
}
