#include "core/device/inc/device_manager.h"

// Private member(s)
PRIVATE STATIC DeviceManager instance = {
    ._core = NULL,
    ._system = NULL,
    ._components = LINKED_LIST_STATIC(),
    ._coroutines = LINKED_LIST_STATIC(),
};

// Method implement(s)
PUBLIC void DeviceManager_SetCore(DeviceManager *pThis, BaseCore *core)
{
    if (pThis != NULL) {
        pThis->_core = core;
    }
}

PUBLIC BaseCore *DeviceManager_GetCore(DeviceManager *pThis)
{
    return (pThis != NULL) ? pThis->_core : NULL;
}

PUBLIC void DeviceManager_SetSystem(DeviceManager *pThis, BaseSystem *system)
{
    if (pThis != NULL) {
        pThis->_system = system;
    }
}

PUBLIC BaseSystem *DeviceManager_GetSystem(DeviceManager *pThis)
{
    return (pThis != NULL) ? pThis->_system : NULL;
}

PUBLIC void DeviceManager_AddComponent(
    DeviceManager *pThis,
    BaseComponent *component)
{
    if (pThis != NULL && component != NULL) {
        LinkedList_AddTail(&pThis->_components, &component->base);
    }
}

PUBLIC void DeviceManager_RemoveComponent(
    DeviceManager *pThis,
    BaseComponent *component)
{
    if (pThis != NULL && component != NULL) {
        LinkedList_RemoveNode(&pThis->_components, &component->base);
    }
}

PUBLIC void DeviceManager_AddCoroutine(
    DeviceManager *pThis,
    LinkedCoroutine *coroutine)
{
    if (pThis != NULL && coroutine != NULL) {
        LinkedList_AddTail(&pThis->_coroutines, &coroutine->base);
    }
}

PUBLIC void DeviceManager_RemoveCoroutine(
    DeviceManager *pThis,
    LinkedCoroutine *coroutine)
{
    if (pThis != NULL && coroutine != NULL) {
        LinkedList_RemoveNode(&pThis->_coroutines, &coroutine->base);
    }
}

PUBLIC LinkedList *DeviceManager_GetComponents(DeviceManager *pThis)
{
    return (pThis == NULL) ? NULL : &pThis->_components;
}

PUBLIC STATIC DeviceManager *DeviceManager_GetInstance(void)
{
    return &instance;
}

PUBLIC STATIC void DeviceManager_TaskEntry(void *parameter)
{
    DeviceManager *manager = (DeviceManager *)parameter;

    LOOP {
        LinkedListIterator iterator;

        BaseCore_Run(manager->_core);
        BaseSystem_Run(manager->_system);
        LinkedListIterator_Construct(&iterator, &manager->_coroutines);

        while (LinkedListIterator_HasNext(&iterator)) {
            LinkedCoroutine *coroutine = LinkedListNode2LinkedCoroutine(
                LinkedListIterator_GetNext(&iterator));

            if (LinkedCoroutine_Run(coroutine) == COROUTINE_STATE_ENDED) {
                LinkedList_RemoveNode(&manager->_coroutines, &coroutine->base);
            }
        }

        LinkedListIterator_Destruct(&iterator);
    }
}
