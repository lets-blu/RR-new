#include "core/device/inc/DeviceManager.h"

// Private member(s)
PRIVATE STATIC DeviceManager instance;

// Private method(s)
PRIVATE void ConstructDeviceManager(DeviceManager *instance);

// Method implement(s)
PRIVATE void ConstructDeviceManager(DeviceManager *instance)
{
    if (instance != NULL)
    {
        ConstructLinkedList(&instance->_factories);
        instance->_isConstructed = true;
        instance->_core = NULL;
    }
}

PUBLIC void DestructDeviceManager(DeviceManager *instance)
{
    if (instance != NULL)
    {
        DestructLinkedList(&instance->_factories);
        memset(instance, 0, sizeof(DeviceManager));
    }
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
