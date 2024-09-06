#include "core/common/inc/linked_list.h"

// Method implement(s)
PUBLIC void ConstructLinkedList(LinkedList *instance)
{
    if (instance != NULL)
    {
        instance->_count = 0;
        instance->_head = NULL;
        instance->_tail = NULL;
    }
}

PUBLIC void DestructLinkedList(LinkedList *instance)
{
    if (instance != NULL)
    {
        memset(instance, 0, sizeof(LinkedList));
    }
}

PROTECTED void ConstructLinkedListNode(LinkedListNode *instance)
{
    if (instance != NULL)
    {
        instance->_next = NULL;
    }
}

PROTECTED void DestructLinkedListNode(LinkedListNode *instance)
{
    if (instance != NULL)
    {
        memset(instance, 0, sizeof(LinkedListNode));
    }
}

PUBLIC void ConstructLinkedListIterator(
    LinkedListIterator *instance,
    LinkedList *list)
{
    if (instance != NULL && list != NULL)
    {
        instance->_next = list->_head;
    }
}

PUBLIC void DestructLinkedListIterator(LinkedListIterator *instance)
{
    if (instance != NULL)
    {
        memset(instance, 0, sizeof(LinkedListIterator));
    }
}

PUBLIC void AddNodeToLinkedList(
    LinkedList *self,
    LinkedListNode *node)
{
    // 1. Check parameters
    if (self == NULL || node == NULL)
    {
        return;
    }

    // 2. Add the node to the list
    if (self->_head == NULL)
    {
        self->_head = node;
    }
    else
    {
        self->_tail->_next = node;
    }

    self->_tail = node;

    // 3. Increase count
    self->_count++;
}

PUBLIC void RemoveNodeFromLinkedList(
    LinkedList *self,
    LinkedListNode *node)
{
    LinkedListNode *previous = NULL;

    // 1. Check parameters
    if (self == NULL || node == NULL)
    {
        return;
    }

    // 2. If the node is head
    if (self->_head == node)
    {
        self->_head = node->_next;
        self->_count--;

        if (self->_head == NULL)
        {
            self->_tail = NULL;
        }

        return;
    }

    // 3. If the node is not head
    previous = self->_head;

    while (previous != NULL && previous->_next != node)
    {
        previous = previous->_next;
    }

    if (previous != NULL)
    {
        previous->_next = node->_next;
        self->_count--;

        if (self->_tail == node)
        {
            self->_tail = previous;
        }
    }
}

PUBLIC LinkedListNode *FindNodeInLinkedList(
    LinkedList *self,
    LinkedListFindCallback callback,
    void *data)
{
    LinkedListNode *node = NULL;

    // 1. Check parameters
    if (self == NULL || callback == NULL)
    {
        return NULL;
    }

    // 2. Find the node
    node = self->_head;

    while (node != NULL && !callback(node, data))
    {
        node = node->_next;
    }

    return node;
}

PUBLIC STATIC bool FindEqualCallbackOfLinkedList(
    LinkedListNode *node,
    void *data)
{
    return (node == data);
}

PUBLIC bool HasNextInLinkedListIterator(LinkedListIterator *self)
{
    return (self != NULL && self->_next != NULL);
}

PUBLIC LinkedListNode *NextOfLinkedListIterator(LinkedListIterator *self)
{
    LinkedListNode *next = NULL;

    if (HasNextInLinkedListIterator(self))
    {
        next = self->_next;
        self->_next = next->_next;
    }

    return next;
}
