#include "port/common/inc/base_serial.h"

// Method implement(s)
PROTECTED void ConstructBaseSerial(
    BaseSerial *instance,
    BaseSerialParameter *parameter)
{
    (void)parameter;

    if (instance != NULL)
    {
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBaseSerial(
    BaseSerial *instance)
{
    if (instance != NULL)
    {
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

PUBLIC void AddEventHandlerToBaseSerial(
    BaseSerial *self,
    EventHandler *handler)
{
    if (self == NULL
        || self->vtbl == NULL
        || self->vtbl->AddEventHandler == NULL)
    {
        return;
    }

    self->vtbl->AddEventHandler(self, handler);
}

PUBLIC void SampleBaseSerial(BaseSerial *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Sample == NULL)
    {
        return;
    }

    self->vtbl->Sample(self);
}
