#include "port/none/inc/none_system.h"

// Override method(s)
PUBLIC void RunNoneSystemBase(
    BaseSystem *sys);

PUBLIC const char *GetNameOfNoneSystemBase(
    BaseSystem *sys);

PUBLIC BasePort *CreatePortWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void DestroyPortWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BasePort *port);

PUBLIC BaseSerial *CreateSerialWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseSerialParameter *parameter);

PUBLIC void DestroySerialWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseSerial *serial);

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
    .CreatePort     = CreatePortWithNoneSystemBase,
    .DestroyPort    = DestroyPortWithNoneSystemBase,
    .CreateSerial   = CreateSerialWithNoneSystemBase,
    .DestroySerial  = DestroySerialWithNoneSystemBase,
    .CreateTask     = CreateTaskWithNoneSystemBase,
    .DestroyTask    = DestroyTaskWithNoneSystemBase
};

// Method implement(s)
PROTECTED void ConstructNoneSystem(NoneSystem *instance)
{
    if (instance != NULL)
    {
        ConstructBaseSystem(&instance->base);
        instance->base.vtbl = &baseSystemVtbl;
        instance->base.base.vtbl = &baseFactoryVtbl;
    }
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

    if (sys != NULL && IS_NONE_TASK_CONSTRUCTED(&self->_task))
    {
        RunBaseTask(&self->_task.base);
    }
}

PUBLIC const char *GetNameOfNoneSystemBase(
    BaseSystem *sys)
{
    (void)sys;
    return "None";
}

PUBLIC BasePort *CreatePortWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BasePortParameter *parameter)
{
    (void)factory;
    (void)type;
    (void)parameter;

    return NULL;
}

PUBLIC void DestroyPortWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BasePort *port)
{
    (void)factory;
    (void)type;
    (void)port;
}

PUBLIC BaseSerial *CreateSerialWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseSerialParameter *parameter)
{
    (void)factory;
    (void)type;
    (void)parameter;

    return NULL;
}

PUBLIC void DestroySerialWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseSerial *serial)
{
    (void)factory;
    (void)type;
    (void)serial;
}

PUBLIC BaseTask *CreateTaskWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseTaskParameter *parameter)
{
    NoneSystem *self = BaseSystem2NoneSystem(factory);

    if (factory == NULL || type == NULL ||IS_NONE_TASK_CONSTRUCTED(&self->_task))
    {
        return NULL;
    }

    if (strcmp(type, NONE_SYSTEM_TASK) == 0)
    {
        ConstructNoneTask(
            &self->_task,
            BaseTaskParameter2NoneTaskParameter(parameter));
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

        ConstructNoneTask(&self->_task, &noneParameter);
    } else {
        return NULL;
    }

    return &self->_task.base;
}

PUBLIC void DestroyTaskWithNoneSystemBase(
    BaseFactory *factory,
    const char *type,
    BaseTask *task)
{
    (void)type;
    NoneSystem *self = BaseSystem2NoneSystem(factory);

    if (factory != NULL && task == &self->_task.base)
    {
        DestructNoneTask(&self->_task);
    }
}
