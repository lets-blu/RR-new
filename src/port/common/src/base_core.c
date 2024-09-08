#include "port/common/inc/base_core.h"

// Method implement(s)
PROTECTED void ConstructBaseCore(BaseCore *instance)
{
    if (instance != NULL)
    {
        ConstructBaseFactory(&instance->base);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBaseCore(BaseCore *instance)
{
    if (instance != NULL)
    {
        DestructBaseFactory(&instance->base);
        memset(instance, 0, sizeof(BaseCore));
    }
}

PUBLIC const char *GetNameOfBaseCore(BaseCore *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->GetName == NULL)
    {
        return NULL;
    }

    return self->vtbl->GetName(self);
}

PUBLIC unsigned long GetTickOfBaseCore(BaseCore *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->GetTick == NULL)
    {
        return 0;
    }

    return self->vtbl->GetTick(self);
}
