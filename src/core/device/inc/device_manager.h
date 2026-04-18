#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#include <stddef.h>

#include "core/coroutine/inc/linked_coroutine.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#include "port/component/inc/base_component.h"
#include "port/core/inc/base_core.h"
#include "port/system/inc/base_system.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
    BaseCore *_core;
    BaseSystem *_system;
    LinkedList _components;
    LinkedList _coroutines;
} DeviceManager;

// Public method(s)
PUBLIC void DeviceManager_SetCore(DeviceManager *pThis, BaseCore *core);
PUBLIC BaseCore *DeviceManager_GetCore(DeviceManager *pThis);

PUBLIC void DeviceManager_SetSystem(DeviceManager *pThis, BaseSystem *system);
PUBLIC BaseSystem *DeviceManager_GetSystem(DeviceManager *pThis);

PUBLIC void DeviceManager_AddComponent(
    DeviceManager *pThis,
    BaseComponent *component);

PUBLIC void DeviceManager_RemoveComponent(
    DeviceManager *pThis,
    BaseComponent *component);

PUBLIC void DeviceManager_AddCoroutine(
    DeviceManager *pThis,
    LinkedCoroutine *coroutine);

PUBLIC void DeviceManager_RemoveCoroutine(
    DeviceManager *pThis,
    LinkedCoroutine *coroutine);

PUBLIC LinkedList *DeviceManager_GetComponents(DeviceManager *pThis);
PUBLIC STATIC DeviceManager *DeviceManager_GetInstance(void);
PUBLIC STATIC void DeviceManager_TaskEntry(void *parameter);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //__DEVICE_MANAGER_H__
