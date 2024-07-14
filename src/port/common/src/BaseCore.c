#include "port/common/inc/BaseCore.h"

// Method implement(s)
PROTECTED void ConstructBaseCore(BaseCore *instance)
{
    if (instance != NULL)
    {
        ConstructorBaseFactory(&instance->base);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBaseCore(BaseCore *instance)
{
    if (instance != NULL)
    {
        DestructorBaseFactory(&instance->base);
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
