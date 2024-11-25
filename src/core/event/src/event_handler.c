#include "core/event/inc/event_handler.h"

// Method implement(s)
PUBLIC void ConstructEventHandler(
    EventHandler *instance,
    EventHandlerHandler handler)
{
    if (instance != NULL && handler != NULL)
    {
        ConstructLinkedListNode(&instance->base);
        instance->_handler = handler;
    }
}

PUBLIC void DestructEventHandler(
    EventHandler *instance)
{
    if (instance != NULL)
    {
        DestructLinkedListNode(&instance->base);
        memset(instance, 0, sizeof(EventHandler));
    }
}

PUBLIC void InvokeEventHandler(
    EventHandler *self,
    void *sender,
    EventParameter *parameter)
{
    if (self != NULL && self->_handler != NULL)
    {
        self->_handler(sender, parameter);
    }
}

PUBLIC STATIC void InvokeEventHandlers(
    LinkedList *handlers,
    void *sender,
    EventParameter *parameter)
{
    LinkedListIterator iterator;

    if (handlers == NULL)
    {
        return;
    }

    ConstructLinkedListIterator(&iterator, handlers);

    while (HasNextInLinkedListIterator(&iterator))
    {
        EventHandler *handler
            = LinkedListNode2EventHandler(NextInLinkedListIterator(&iterator));

        InvokeEventHandler(handler, sender, parameter);
    }

    DestructLinkedListIterator(&iterator);
}
