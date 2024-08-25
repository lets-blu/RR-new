#include "core/thread/inc/base_thread.h"
#include "core/device/inc/device_manager.h"

// Method implement(s)
PROTECTED void ConstructBaseThread(BaseThread *instance)
{
    if (instance == NULL)
    {
        return;
    }

    ConstructLinkedListNode(&instance->base);

    instance->_line = 0;
    instance->_tick = 0;
    instance->vtbl = NULL;
}

PROTECTED void DestructBaseThread(BaseThread *instance)
{
    if (instance != NULL)
    {
        DestructLinkedListNode(&instance->base);
        memset(instance, 0, sizeof(BaseThread));
    }
}

PUBLIC void UpdateTickInBaseThread(BaseThread *self)
{
    DeviceManager *manager = InstanceOfDeviceManager();

    if (self != NULL)
    {
        self->_tick = GetTickOfBaseCore(GetCoreFromDeviceManager(manager));
    }
}

PUBLIC bool IsTimeoutForBaseThread(BaseThread *self, unsigned long delay)
{
    DeviceManager *manager = InstanceOfDeviceManager();
    unsigned long current = GetTickOfBaseCore(GetCoreFromDeviceManager(manager));

    return (self == NULL) ? false : (current - self->_tick > delay);
}

PUBLIC BaseThreadState RunBaseThread(BaseThread *self)
{
    if (self == NULL || self->vtbl == NULL || self->vtbl->Run == NULL)
    {
        return BASE_THREAD_STATE_ENDED;
    }

    return self->vtbl->Run(self);
}

PUBLIC STATIC void RunBaseThreads(LinkedList *threads)
{
    LinkedListIterator iterator;

    if (threads == NULL)
    {
        return;
    }

    ConstructLinkedListIterator(&iterator, threads);

    while (HasNextInLinkedListIterator(&iterator))
    {
        BaseThread *thread
            = LinkedListNode2BaseThread(NextOfLinkedListIterator(&iterator));

        if (RunBaseThread(thread) == BASE_THREAD_STATE_ENDED)
        {
            RemoveNodeFromLinkedList(threads, &thread->base);
        }
    }

    DestructLinkedListIterator(&iterator);
}
