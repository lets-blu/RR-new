#include "core/device/inc/device_manager.h"

// Private member(s)
PRIVATE STATIC DeviceManager instance;

// Private method(s)
PRIVATE void ConstructDeviceManager(DeviceManager *instance);
PRIVATE STATIC void RunDeviceManager(void *parameter);

// Method implement(s)
PRIVATE void ConstructDeviceManager(DeviceManager *instance)
{
    if (instance == NULL)
    {
        return;
    }

    instance->_isConstructed = true;

    instance->_core = NULL;
    instance->_sys = NULL;
    ConstructLinkedList(&instance->_factories);

    instance->_task = NULL;

    for (unsigned int i = 0; i < DEVICE_MANAGER_THREAD_NUMBER; i++)
    {
        ConstructLinkedList(&instance->_threads[i]);
    }
}

PUBLIC void DestructDeviceManager(DeviceManager *instance)
{
    if (instance == NULL)
    {
        return;
    }

    DestructLinkedList(&instance->_factories);

    for (unsigned int i = 0; i < DEVICE_MANAGER_THREAD_NUMBER; i++)
    {
        DestructLinkedList(&instance->_threads[i]);
    }

    memset(instance, 0, sizeof(DeviceManager));
}

PUBLIC void SetCoreToDeviceManager(DeviceManager *self, BaseCore *core)
{
    if (self != NULL && core != NULL && self->_core == NULL)
    {
        self->_core = core;
        AddNodeToLinkedList(&self->_factories, &core->base.base);
        printf("[DeviceManager][D] Set core: %s\r\n", GetNameOfBaseCore(core));
    }
}

PUBLIC void SetSystemToDeviceManager(DeviceManager *self, BaseSystem *sys)
{
    GeneralTaskParameter parameter = {
        .base = GENERAL_TASK_PARAMETER_BASE,
        .entry = RunDeviceManager,
        .parameter = self
    };

    if (self == NULL || sys == NULL || self->_sys != NULL)
    {
        return;
    }

    self->_sys = sys;
    AddNodeToLinkedList(&self->_factories, &sys->base.base);
    printf("[DeviceManager][D] Set system: %s\r\n", GetNameOfBaseSystem(sys));

    self->_task = CreateTaskWithBaseFactories(
        &self->_factories,
        GENERAL_TASK,
        &parameter.base);

    printf("[DeviceManager][I] Set system, create task %p\r\n", self->_task);
}

PUBLIC void AddThreadToDeviceManager(
    DeviceManager *self,
    DeviceManagerThreadType type,
    BaseThread *thread)
{
    if (self != NULL && thread != NULL)
    {
        AddNodeToLinkedList(&self->_threads[type], &thread->base);
        printf("[DeviceManager][D] Add thread: %p (type %d)\r\n", thread, type);
    }
}

PUBLIC BaseCore *GetCoreFromDeviceManager(DeviceManager *self)
{
    return (self == NULL) ? NULL : self->_core;
}

PUBLIC BaseSystem *GetSystemFromDeviceManager(DeviceManager *self)
{
    return (self == NULL) ? NULL : self->_sys;
}

PUBLIC LinkedList *GetFactoriesFromDeviceManager(DeviceManager *self)
{
    return (self == NULL) ? NULL : &self->_factories;
}

PUBLIC STATIC DeviceManager *InstanceOfDeviceManager(void)
{
    if (!instance._isConstructed)
    {
        ConstructDeviceManager(&instance);
    }

    return &instance;
}

PRIVATE STATIC void RunDeviceManager(void *parameter)
{
    DeviceManager *self = (DeviceManager *)parameter;

    for (;;)
    {
        for (unsigned int i = 0; i < DEVICE_MANAGER_THREAD_NUMBER; i++)
        {
            RunBaseThreads(&self->_threads[i]);
        }
    }
}
