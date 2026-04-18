#include "port/core/inc/base_serial.h"

// Method implement(s)
PROTECTED void BaseSerial_Construct(
    BaseSerial *pThis,
    BaseSerialParameter *parameter)
{
    (void)parameter;

    if (pThis != NULL) {
        pThis->vtbl = NULL;
    }
}

PROTECTED void BaseSerial_Destruct(BaseSerial *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(BaseSerial));
    }
}

PUBLIC size_t BaseSerial_Read(
    BaseSerial *pThis,
    uint8_t *buffer,
    size_t bufferSize)
{
    if (pThis == NULL || pThis->vtbl == NULL || pThis->vtbl->Read == NULL) {
        return 0;
    }

    return pThis->vtbl->Read(pThis, buffer, bufferSize);
}

PUBLIC size_t BaseSerial_Write(
    BaseSerial *pThis,
    const uint8_t *buffer,
    size_t bufferLength)
{
    if (pThis == NULL || pThis->vtbl == NULL || pThis->vtbl->Write == NULL) {
        return 0;
    }

    return pThis->vtbl->Write(pThis, buffer, bufferLength);
}

PUBLIC void BaseSerial_SetEventHandler(BaseSerial *pThis, EventHandler handler)
{
    if (pThis != NULL
        && pThis->vtbl != NULL
        && pThis->vtbl->SetEventHandler != NULL) {
        pThis->vtbl->SetEventHandler(pThis, handler);
    }
}
