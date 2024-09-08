#include "port/common/inc/base_system.h"

// Method implement(s)
PROTECTED void ConstructBaseSystem(BaseSystem *instance)
{
    if (instance != NULL)
    {
        ConstructBaseFactory(&instance->base);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBaseSystem(BaseSystem *instance)
{
    if (instance != NULL)
    {
        DestructBaseFactory(&instance->base);
        memset(instance, 0, sizeof(BaseSystem));
    }
}

PUBLIC void RunBaseSystem(BaseSystem *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Run == NULL)
    {
        return;
    }

    self->vtbl->Run(self);
}

PUBLIC const char *GetNameOfBaseSystem(BaseSystem *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->GetName == NULL)
    {
        return NULL;
    }

    return self->vtbl->GetName(self);
}
