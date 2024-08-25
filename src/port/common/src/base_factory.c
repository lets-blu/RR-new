#include "port/common/inc/base_factory.h"

// Method implement(s)
PROTECTED void ConstructBaseFactory(
    BaseFactory *instance)
{
    if (instance != NULL)
    {
        ConstructLinkedListNode(&instance->base);
        instance->vtbl = NULL;
    }
}

PROTECTED void DestructBaseFactory(
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

PUBLIC BaseTask *CreateTaskWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BaseTaskParameter *parameter)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->CreateTask == NULL)
    {
        return NULL;
    }

    return self->vtbl->CreateTask(self, type, parameter);
}

PUBLIC void DestroyTaskWithBaseFactory(
    BaseFactory *self,
    const char *type,
    BaseTask *task)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->DestroyTask == NULL)
    {
        return;
    }

    self->vtbl->DestroyTask(self, type, task);
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

PUBLIC STATIC BaseTask *CreateTaskWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BaseTaskParameter *parameter)
{
    BaseTask *task = NULL;
    LinkedListIterator iterator;

    ConstructLinkedListIterator(&iterator, factories);

    while (task == NULL && HasNextInLinkedListIterator(&iterator))
    {
        BaseFactory *factory
            = LinkedListNode2BaseFactory(NextOfLinkedListIterator(&iterator));

        task = CreateTaskWithBaseFactory(factory, type, parameter);
    }

    DestructLinkedListIterator(&iterator);

    return task;
}

PUBLIC STATIC void DestroyTaskWithBaseFactories(
    LinkedList *factories,
    const char *type,
    BaseTask *task)
{
    LinkedListIterator iterator;

    ConstructLinkedListIterator(&iterator, factories);

    while (HasNextInLinkedListIterator(&iterator))
    {
        BaseFactory *factory
            = LinkedListNode2BaseFactory(NextOfLinkedListIterator(&iterator));

        DestroyTaskWithBaseFactory(factory, type, task);
    }

    DestructLinkedListIterator(&iterator);
}
