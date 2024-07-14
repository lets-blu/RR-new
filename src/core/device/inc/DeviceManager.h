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
#include "port/common/inc/BaseCore.h"

typedef struct {
    bool _isConstructed;
    BaseCore *_core;
    LinkedList _factories;
} DeviceManager;

// Constructor(s) & Destructor(s)
PUBLIC void DestructDeviceManager(DeviceManager *instance);

// Public method(s)
PUBLIC void SetCoreToDeviceManager(DeviceManager *self, BaseCore *core);
PUBLIC LinkedList *GetFactoriesFromDeviceManager(DeviceManager *self);
PUBLIC STATIC DeviceManager *InstanceOfDeviceManager(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __DEVICE_MANAGER_H__
