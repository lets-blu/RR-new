#include "port/common/inc/BaseFactory.h"

// Method implement(s)
PROTECTED void ConstructorBaseFactory(
    BaseFactory *instance)
{
    if (instance != NULL)
    {
        ConstructLinkedListNode(&instance->base);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructorBaseFactory(
    BaseFactory *instance)
{
    if (instance != NULL)
    {
        DestructLinkedListNode(&instance->base);
        memset(instance, 0, sizeof(BaseFactory));
    }
}

PUBLIC BasePort *CreatePortWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BasePortParameter *parameter)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->CreatePort == NULL)
    {
        return NULL;
    }

    return self->vtbl->CreatePort(self, type, parameter);
}

PUBLIC void DestroyPortWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BasePort *port)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->DestroyPort == NULL)
    {
        return;
    }

    self->vtbl->DestroyPort(self, type, port);
}

PUBLIC STATIC BasePort *CreatePortWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BasePortParameter *parameter)
{
    BasePort *port = NULL;
    LinkedListIterator iterator;

    ConstructLinkedListIterator(&iterator, factories);

    while (port == NULL && HasNextInLinkedListIterator(&iterator))
    {
        BaseFactory *factory
            = LinkedListNode2BaseFactory(NextOfLinkedListIterator(&iterator));
        
        port = CreatePortWithBaseFactory(factory, type, parameter);
    }

    DestructLinkedListIterator(&iterator);

    return port;
}

PUBLIC STATIC void DestroyPortWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BasePort *port)
{
    LinkedListIterator iterator;

    ConstructLinkedListIterator(&iterator, factories);

    while (HasNextInLinkedListIterator(&iterator))
    {
        BaseFactory *factory
            = LinkedListNode2BaseFactory(NextOfLinkedListIterator(&iterator));
        
        DestroyPortWithBaseFactory(factory, type, port);
    }

    DestructLinkedListIterator(&iterator);
}
