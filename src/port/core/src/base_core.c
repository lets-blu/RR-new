#include "port/core/inc/base_core.h"

// Method implement(s)
PROTECTED void BaseCore_Construct(BaseCore *pThis)
{
    if (pThis != NULL) {
        pThis->vtbl = NULL;
    }
}

PROTECTED void BaseCore_Destruct(BaseCore *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(BaseCore));
    }
}

PUBLIC BasePort *BaseCore_CreatePort(
    BaseCore *pThis,
    const char *type,
    BasePortParameter *parameter)
{
    if (pThis == NULL
        || pThis->vtbl == NULL
        || pThis->vtbl->CreatePort == NULL) {
        return NULL;
    }

    return pThis->vtbl->CreatePort(pThis, type, parameter);
}

PUBLIC void BaseCore_DestroyPort(BaseCore *pThis, BasePort *port)
{
    if (pThis != NULL
        && pThis->vtbl != NULL
        && pThis->vtbl->DestroyPort != NULL) {
        pThis->vtbl->DestroyPort(pThis, port);
    }
}

PUBLIC BaseSerial *BaseCore_CreateSerial(
    BaseCore *pThis,
    const char *type,
    BaseSerialParameter *parameter)
{
    if (pThis == NULL
        || pThis->vtbl == NULL
        || pThis->vtbl->CreateSerial == NULL) {
        return NULL;
    }

    return pThis->vtbl->CreateSerial(pThis, type, parameter);
}

PUBLIC void BaseCore_DestroySerial(BaseCore *pThis, BaseSerial *serial)
{
    if (pThis != NULL
        && pThis->vtbl != NULL
        && pThis->vtbl->DestroySerial != NULL) {
        pThis->vtbl->DestroySerial(pThis, serial);
    }
}

PUBLIC unsigned long BaseCore_GetTime(BaseCore *pThis)
{
    if (pThis == NULL
        || pThis->vtbl == NULL
        || pThis->vtbl->GetTime == NULL) {
        return 0;
    }

    return pThis->vtbl->GetTime(pThis);
}

PUBLIC void BaseCore_Run(BaseCore *pThis)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->Run != NULL) {
        pThis->vtbl->Run(pThis);
    }
}
