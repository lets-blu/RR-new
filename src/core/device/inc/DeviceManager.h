#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "core/common/inc/Keywords.h"
#include "core/common/inc/LinkedList.h"
#include "core/thread/inc/base_thread.h"

#include "port/common/inc/BaseCore.h"
#include "port/common/inc/base_system.h"
#include "port/general/inc/general_task.h"

typedef enum {
    DEVICE_MANAGER_THREAD_DRIVER_INPUT,
    DEVICE_MANAGER_THREAD_APPLICATION,
    DEVICE_MANAGER_THREAD_DRIVER_OUTPUT,
    DEVICE_MANAGER_THREAD_NUMBER
} DeviceManagerThreadType;

typedef struct {
    bool _isConstructed;

    BaseCore *_core;
    BaseSystem *_sys;
    LinkedList _factories;

    BaseTask *_task;
    LinkedList _threads[DEVICE_MANAGER_THREAD_NUMBER];
} DeviceManager;

// Constructor(s) & Destructor(s)
PUBLIC void DestructDeviceManager(DeviceManager *instance);

// Public method(s)
PUBLIC void SetCoreToDeviceManager(DeviceManager *self, BaseCore *core);
PUBLIC void SetSystemToDeviceManager(DeviceManager *self, BaseSystem *sys);

PUBLIC void AddThreadToDeviceManager(
    DeviceManager *self,
    DeviceManagerThreadType type,
    BaseThread *thread);

PUBLIC BaseCore *GetCoreFromDeviceManager(DeviceManager *self);
PUBLIC BaseSystem *GetSystemFromDeviceManager(DeviceManager *self);
PUBLIC LinkedList *GetFactoriesFromDeviceManager(DeviceManager *self);

PUBLIC STATIC DeviceManager *InstanceOfDeviceManager(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __DEVICE_MANAGER_H__
