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

PUBLIC size_t ReadBaseSerial(
    BaseSerial *self,
    uint8_t *buffer,
    size_t size)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Read == NULL)
    {
        return 0;
    }

    return self->vtbl->Read(self, buffer, size);
}

PUBLIC size_t WriteBaseSerial(
    BaseSerial *self,
    const uint8_t *buffer,
    size_t size)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Write == NULL)
    {
        return 0;
    }

    return self->vtbl->Write(self, buffer, size);
}
