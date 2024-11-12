#include "port/common/inc/base_serial.h"

// Method implement(s)
PROTECTED void ConstructBaseSerial(
    BaseSerial *instance,
    BaseSerialParameter *parameter)
{
    (void)parameter;

    if (instance != NULL)
    {
        ConstructLinkedListNode(&instance->base);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBaseSerial(
    BaseSerial *instance)
{
    if (instance != NULL)
    {
        DestructLinkedListNode(&instance->base);
        memset(instance, 0, sizeof(BaseSerial));
    }
}

PUBLIC unsigned int ReadBaseSerial(
    BaseSerial *self,
    uint8_t *buffer,
    unsigned int size)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Read == NULL)
    {
        return 0;
    }

    return self->vtbl->Read(self, buffer, size);
}

PUBLIC unsigned int WriteBaseSerial(
    BaseSerial *self,
    const uint8_t *buffer,
    unsigned int size)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Write == NULL)
    {
        return 0;
    }

    return self->vtbl->Write(self, buffer, size);
}

PUBLIC void SetRxCallbackToBaseSerial(
    BaseSerial *self,
    RingBufferCallback callback)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->SetRxCallback == NULL)
    {
        return;
    }

    self->vtbl->SetRxCallback(self, callback);
}
