#include "core/device/inc/device_factory.h"

// Method implement(s)
PUBLIC BasePort *DeviceFactory_CreatePort(
    DeviceFactory *pThis,
    const char *type,
    BasePortParameter *parameter)
{
    (void)pThis;
    LinkedListIterator iterator;
    DeviceManager *manager = DeviceManager_GetInstance();

    BasePort *port = BaseCore_CreatePort(
        DeviceManager_GetCore(manager),
        type,
        parameter);

    if (port != NULL) {
        return port;
    }

    LinkedListIterator_Construct(
        &iterator,
        DeviceManager_GetComponents(manager));

    while (LinkedListIterator_HasNext(&iterator)) {
        port = BaseComponent_CreatePort(
            LinkedListNode2BaseComponent(LinkedListIterator_GetNext(&iterator)),
            type,
            parameter);

        if (port != NULL) {
            break;
        }
    }

    LinkedListIterator_Destruct(&iterator);

    return port;
}

PUBLIC void DeviceFactory_DestroyPort(
    DeviceFactory *pThis,
    BasePort *port)
{
    (void)pThis;
    LinkedListIterator iterator;
    DeviceManager *manager = DeviceManager_GetInstance();

    BaseCore_DestroyPort(DeviceManager_GetCore(manager), port);

    LinkedListIterator_Construct(
        &iterator,
        DeviceManager_GetComponents(manager));

    while (LinkedListIterator_HasNext(&iterator)) {
        BaseComponent_DestroyPort(
            LinkedListNode2BaseComponent(LinkedListIterator_GetNext(&iterator)),
            port);
    }

    LinkedListIterator_Destruct(&iterator);
}

PUBLIC BaseSerial *DeviceFactory_CreateSerial(
    DeviceFactory *pThis,
    const char *type,
    BaseSerialParameter *parameter)
{
    (void)pThis;

    return BaseCore_CreateSerial(
        DeviceManager_GetCore(DeviceManager_GetInstance()),
        type,
        parameter);
}

PUBLIC void DeviceFactory_DestroySerial(
    DeviceFactory *pThis,
    BaseSerial *serial)
{
    (void)pThis;

    BaseCore_DestroySerial(
        DeviceManager_GetCore(DeviceManager_GetInstance()),
        serial);
}

PUBLIC BaseTask *DeviceFactory_CreateTask(
    DeviceFactory *pThis,
    const char *type,
    BaseTaskParameter *parameter)
{
    (void)pThis;

    return BaseSystem_CreateTask(
        DeviceManager_GetSystem(DeviceManager_GetInstance()),
        type,
        parameter);
}

PUBLIC void DeviceFactory_DestroyTask(
    DeviceFactory *pThis,
    BaseTask *task)
{
    (void)pThis;

    BaseSystem_DestroyTask(
        DeviceManager_GetSystem(DeviceManager_GetInstance()),
        task);
}

PUBLIC BaseTimer *DeviceFactory_CreateTimer(
    DeviceFactory *pThis,
    const char *type,
    BaseTimerParameter *parameter)
{
    (void)pThis;

    return BaseSystem_CreateTimer(
        DeviceManager_GetSystem(DeviceManager_GetInstance()),
        type,
        parameter);
}

PUBLIC void DeviceFactory_DestroyTimer(
    DeviceFactory *pThis,
    BaseTimer *timer)
{
    (void)pThis;

    BaseSystem_DestroyTimer(
        DeviceManager_GetSystem(DeviceManager_GetInstance()),
        timer);
}

PUBLIC DeviceFactory *DeviceFactory_GetInstance(void)
{
    return NULL;
}
