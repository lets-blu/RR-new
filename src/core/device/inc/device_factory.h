#ifndef __DEVICE_FACTORY_H__
#define __DEVICE_FACTORY_H__

#include <stddef.h>

#include "core/device/inc/device_manager.h"
#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#include "port/component/inc/base_component.h"

#include "port/core/inc/base_core.h"
#include "port/core/inc/base_port.h"
#include "port/core/inc/base_serial.h"
#include "port/core/inc/base_timer.h"

#include "port/system/inc/base_system.h"
#include "port/system/inc/base_task.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef void DeviceFactory;

// Public method(s)
PUBLIC BasePort *DeviceFactory_CreatePort(
    DeviceFactory *pThis,
    const char *type,
    BasePortParameter *parameter);

PUBLIC void DeviceFactory_DestroyPort(
    DeviceFactory *pThis,
    BasePort *port);

PUBLIC BaseSerial *DeviceFactory_CreateSerial(
    DeviceFactory *pThis,
    const char *type,
    BaseSerialParameter *parameter);

PUBLIC void DeviceFactory_DestroySerial(
    DeviceFactory *pThis,
    BaseSerial *serial);

PUBLIC BaseTask *DeviceFactory_CreateTask(
    DeviceFactory *pThis,
    const char *type,
    BaseTaskParameter *parameter);

PUBLIC void DeviceFactory_DestroyTask(
    DeviceFactory *pThis,
    BaseTask *task);

PUBLIC BaseTimer *DeviceFactory_CreateTimer(
    DeviceFactory *pThis,
    const char *type,
    BaseTimerParameter *parameter);

PUBLIC void DeviceFactory_DestroyTimer(
    DeviceFactory *pThis,
    BaseTimer *timer);

PUBLIC DeviceFactory *DeviceFactory_GetInstance(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __DEVICE_FACTORY_H__
