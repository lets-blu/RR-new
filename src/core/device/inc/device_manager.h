#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"
#include "core/common/inc/linked_list.h"
#include "core/logger/inc/logger.h"
#include "core/thread/inc/base_thread.h"

#include "port/common/inc/base_core.h"
#include "port/common/inc/base_system.h"
#include "port/general/inc/general_task.h"

typedef enum {
    DEVICE_MANAGER_THREAD_DRIVER_INPUT,
    DEVICE_MANAGER_THREAD_APPLICATION,
    DEVICE_MANAGER_THREAD_DRIVER_OUTPUT,
    NUMBER_OF_DEVICE_MANAGER_THREADS
} DeviceManagerThread;

typedef struct {
    bool _isConstructed;

    BaseCore *_core;
    BaseSystem *_sys;
    LinkedList _factories;

    BaseTask *_task;
    LinkedList _threads[NUMBER_OF_DEVICE_MANAGER_THREADS];
} DeviceManager;

// Constructor(s) & Destructor(s)
PUBLIC void DestructDeviceManager(DeviceManager *instance);

// Public method(s)
PUBLIC void SetCoreToDeviceManager(DeviceManager *self, BaseCore *core);
PUBLIC void SetSystemToDeviceManager(DeviceManager *self, BaseSystem *sys);

PUBLIC void AddThreadToDeviceManager(
    DeviceManager *self,
    DeviceManagerThread type,
    BaseThread *thread);

PUBLIC BaseCore *GetCoreFromDeviceManager(DeviceManager *self);
PUBLIC BaseSystem *GetSystemFromDeviceManager(DeviceManager *self);
PUBLIC LinkedList *GetFactoriesFromDeviceManager(DeviceManager *self);

PUBLIC STATIC DeviceManager *InstanceOfDeviceManager(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __DEVICE_MANAGER_H__
