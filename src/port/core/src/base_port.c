#include "port/core/inc/base_port.h"

// Method implement(s)
PROTECTED void BasePort_Construct(
    BasePort *pThis,
    BasePortParameter *parameter)
{
    (void)parameter;

    if (pThis != NULL) {
        pThis->vtbl = NULL;
    }
}

PROTECTED void BasePort_Destruct(BasePort *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(BasePort));
    }
}

PUBLIC void BasePort_SetMode(
    BasePort *pThis,
    unsigned int pin,
    BasePortMode mode)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->SetMode != NULL) {
        pThis->vtbl->SetMode(pThis, pin, mode);
    }
}

PUBLIC unsigned int BasePort_Read(BasePort *pThis, unsigned int pin)
{
    if (pThis == NULL || pThis->vtbl == NULL || pThis->vtbl->Read == NULL) {
        return 0;
    }

    return pThis->vtbl->Read(pThis, pin);
}

PUBLIC void BasePort_Write(BasePort *pThis, unsigned int pin, unsigned int val)
{
    if (pThis != NULL && pThis->vtbl != NULL && pThis->vtbl->Write != NULL) {
        pThis->vtbl->Write(pThis, pin, val);
    }
}

PUBLIC STATIC unsigned int BasePort_GetPinOffset(unsigned int pin)
{
    unsigned int offset = 0;

    while (pin != 0) {
        if ((pin & 1) != 0) {
            break;
        }

        offset++;
        pin >>= 1;
    }

    return offset;
}
