#include "core/coroutine/inc/coroutine.h"
#include "core/device/inc/device_manager.h"

// Method implement(s)
PUBLIC void Coroutine_Construct(Coroutine *pThis)
{
    if (pThis != NULL) {
        pThis->_line = 0;
    }
}

PUBLIC void Coroutine_Destruct(Coroutine *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(Coroutine));
    }
}

PUBLIC STATIC unsigned long Coroutine_GetTime(void)
{
    return BaseCore_GetTime(
        DeviceManager_GetCore(DeviceManager_GetInstance()));
}

PUBLIC STATIC bool Coroutine_IsTimeout(unsigned long pre, unsigned long delay)
{
    return (Coroutine_GetTime() - pre >= delay);
}
