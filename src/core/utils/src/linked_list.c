#include "core/utils/inc/linked_list.h"

// Method implement(s)
PUBLIC void LinkedList_Construct(LinkedList *pThis)
{
    if (pThis != NULL) {
        pThis->_head = NULL;
        pThis->_tail = NULL;
    }
}

PUBLIC void LinkedList_Destruct(LinkedList *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(LinkedList));
    }
}

PROTECTED void LinkedListNode_Construct(LinkedListNode *pThis)
{
    if (pThis != NULL) {
        pThis->_next = NULL;
    }
}

PROTECTED void LinkedListNode_Destruct(LinkedListNode *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(LinkedListNode));
    }
}

PUBLIC void LinkedListIterator_Construct(
    LinkedListIterator *pThis,
    LinkedList *list)
{
    if (pThis != NULL && list != NULL) {
        pThis->_next = list->_head;
    }
}

PUBLIC void LinkedListIterator_Destruct(LinkedListIterator *pThis)
{
    if (pThis != NULL) {
        memset(pThis, 0, sizeof(LinkedListIterator));
    }
}

PUBLIC void LinkedList_AddHead(LinkedList *pThis, LinkedListNode *node)
{
    // 1. Check parameters
    if (pThis == NULL || node == NULL) {
        return;
    }

    // 2. Add the node to the list
    node->_next = pThis->_head;
    pThis->_head = node;

    if (pThis->_tail == NULL) {
        pThis->_tail = node;
    }
}

PUBLIC void LinkedList_AddTail(LinkedList *pThis, LinkedListNode *node)
{
    // 1. Check parameters
    if (pThis == NULL || node == NULL) {
        return;
    }

    // 2. Add the node to the list
    if (pThis->_head == NULL) {
        pThis->_head = node;
    } else {
        pThis->_tail->_next = node;
    }

    pThis->_tail = node;
}

PUBLIC void LinkedList_RemoveNode(LinkedList *pThis, LinkedListNode *node)
{
    LinkedListNode *previous = NULL;

    // 1. Check parameters
    if (pThis == NULL || node == NULL) {
        return;
    }

    // 2. If the node is head
    if (pThis->_head == node) {
        pThis->_head = node->_next;

        if (pThis->_head == NULL) {
            pThis->_tail = NULL;
        }

        return;
    }

    // 3. If the node is not head
    previous = pThis->_head;

    while (previous != NULL && previous->_next != node) {
        previous = previous->_next;
    }

    if (previous != NULL) {
        previous->_next = node->_next;

        if (pThis->_tail == node) {
            pThis->_tail = previous;
        }
    }
}

PUBLIC LinkedListNode *LinkedList_FindNode(
    LinkedList *pThis,
    LinkedListFindCallback callback,
    const void *data)
{
    LinkedListNode *node = NULL;

    // 1. Check parameters
    if (pThis == NULL || callback == NULL) {
        return NULL;
    }

    // 2. Find the node
    node = pThis->_head;

    while (node != NULL && !callback(node, data)) {
        node = node->_next;
    }

    return node;
}

PUBLIC LinkedListNode *LinkedList_GetHead(LinkedList *pThis)
{
    return (pThis == NULL) ? NULL : pThis->_head;
}

PUBLIC LinkedListNode *LinkedList_GetTail(LinkedList *pThis)
{
    return (pThis == NULL) ? NULL : pThis->_tail;
}

PUBLIC LinkedListNode *LinkedListNode_GetNext(LinkedListNode *pThis)
{
    return (pThis == NULL) ? NULL : pThis->_next;
}

PUBLIC bool LinkedListIterator_HasNext(LinkedListIterator *pThis)
{
    return (pThis != NULL && pThis->_next != NULL);
}

PUBLIC LinkedListNode *LinkedListIterator_GetNext(LinkedListIterator *pThis)
{
    LinkedListNode *next = NULL;

    if (LinkedListIterator_HasNext(pThis)) {
        next = pThis->_next;
        pThis->_next = next->_next;
    }

    return next;
}
