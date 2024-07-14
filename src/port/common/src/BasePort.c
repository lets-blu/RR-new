#include "port/common/inc/BasePort.h"

// Method implement(s)
PROTECTED void ConstructBasePort(
    BasePort *instance,
    BasePortParameter *parameter)
{
    (void)parameter;

    if (instance != NULL)
    {
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBasePort(BasePort *instance)
{
    if (instance != NULL)
    {
        memset(instance, 0, sizeof(BasePort));
    }
}

PUBLIC void SetupBasePort(BasePort *self, BasePortMode mode)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Setup == NULL)
    {
        return;
    }

    self->vtbl->Setup(self, mode);
}

PUBLIC unsigned int ReadBasePort(BasePort *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Read == NULL)
    {
        return 0;
    }

    return self->vtbl->Read(self);
}

PUBLIC void WriteBasePort(BasePort *self, unsigned int value)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Write == NULL)
    {
        return;
    }

    self->vtbl->Write(self, value);
}
