#include "port/none/inc/none_timer.h"
#include "core/device/inc/device_manager.h"

// Private member(s)
PRIVATE STATIC LinkedList timers = LINKED_LIST_STATIC();

// Private method(s)
PRIVATE void NoneTimer_CheckTimeout(NoneTimer *pThis);

PRIVATE STATIC bool NoneTimer_FindCallback(
    LinkedListNode *node,
    const void *data);

// Override method(s)
PUBLIC void NoneTimer_Start(BaseTimer *timer, unsigned long delay);
PUBLIC void NoneTimer_Stop(BaseTimer *timer);

// Virtual methods table(s)
static const BaseTimerVtbl baseTimerVtbl = {
    .Start = NoneTimer_Start,
    .Stop = NoneTimer_Stop,
};

// Methomd implement(s)
PUBLIC void NoneTimer_Construct(
    NoneTimer *pThis,
    NoneTimerParameter *parameter)
{
    if (pThis == NULL || parameter == NULL) {
        return;
    }

    LinkedListNode_Construct(&pThis->baseNode);
    BaseTimer_Construct(&pThis->baseTimer, &parameter->base);
    pThis->baseTimer.vtbl = &baseTimerVtbl;

    pThis->_handler = parameter->handler;
    pThis->_timeout = 0;
}

PUBLIC void NoneTimer_Destruct(NoneTimer *pThis)
{
    if (pThis == NULL) {
        return;
    }

    LinkedList_RemoveNode(&timers, &pThis->baseNode);

    LinkedList_Destruct(&timers);
    BaseTimer_Destruct(&pThis->baseTimer);
    memset(pThis, 0, sizeof(NoneTimer));
}

PRIVATE void NoneTimer_CheckTimeout(NoneTimer *pThis)
{
    unsigned long current = BaseCore_GetTime(
        DeviceManager_GetCore(DeviceManager_GetInstance()));

    if (pThis->_timeout <= current) {
        pThis->_handler(pThis, NULL);
        LinkedList_RemoveNode(&timers, &pThis->baseNode);
    }
}

PUBLIC void NoneTimer_Start(BaseTimer *timer, unsigned long delay)
{
    NoneTimer *pThis = BaseTimer2NoneTimer(timer);

    if (timer == NULL) {
        return;
    }

    if (LinkedList_FindNode(&timers, NoneTimer_FindCallback, pThis) == NULL) {
        pThis->_timeout = delay
            + BaseCore_GetTime(
                DeviceManager_GetCore(DeviceManager_GetInstance()));

        LinkedList_AddTail(&timers, &pThis->baseNode);
    }
}

PUBLIC void NoneTimer_Stop(BaseTimer *timer)
{
    NoneTimer *pThis = BaseTimer2NoneTimer(timer);

    if (timer != NULL) {
        LinkedList_RemoveNode(&timers, &pThis->baseNode);
    }
}

PUBLIC STATIC void NoneTimer_CheckTimers(void)
{
    LinkedListIterator iterator;

    LinkedListIterator_Construct(&iterator, &timers);

    while (LinkedListIterator_HasNext(&iterator)) {
        NoneTimer_CheckTimeout(
            LinkedListNode2NoneTimer(LinkedListIterator_GetNext(&iterator)));
    }

    LinkedListIterator_Destruct(&iterator);
}

PRIVATE STATIC bool NoneTimer_FindCallback(
    LinkedListNode *node,
    const void *data)
{
    return (node == NULL) ? false : (LinkedListNode2NoneTimer(node) == data);
}
