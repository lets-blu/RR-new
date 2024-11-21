#include "port/common/inc/base_port.h"

// Method implement(s)
PROTECTED void ConstructBasePort(
    BasePort *instance,
    BasePortParameter *parameter)
{
    (void)parameter;

    if (instance != NULL)
    {
        ConstructLinkedListNode(&instance->base);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBasePort(BasePort *instance)
{
    if (instance != NULL)
    {
        DestructLinkedListNode(&instance->base);
        memset(instance, 0, sizeof(BasePort));
    }
}

PUBLIC void SetupBasePort(BasePort *self, unsigned int pin, BasePortMode mode)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Setup == NULL)
    {
        return;
    }

    self->vtbl->Setup(self, pin, mode);
}

PUBLIC void SampleBasePort(BasePort *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Sample == NULL)
    {
        return;
    }

    self->vtbl->Sample(self);
}

PUBLIC unsigned int ReadBasePort(BasePort *self, unsigned int pin)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Read == NULL)
    {
        return 0;
    }

    return self->vtbl->Read(self, pin);
}

PUBLIC void WriteBasePort(BasePort *self, unsigned int pin, unsigned int value)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Write == NULL)
    {
        return;
    }

    self->vtbl->Write(self, pin, value);
}
