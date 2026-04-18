#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/utils/inc/keywords.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define LINKED_LIST_STATIC() { \
    ._head = NULL,             \
    ._tail = NULL,             \
}

#define LINKED_LIST_NODE_STATIC() { \
    ._next = NULL,                  \
}

struct LinkedListNode;

typedef struct {
    struct LinkedListNode *_head;
    struct LinkedListNode *_tail;
} LinkedList;

typedef struct LinkedListNode {
    struct LinkedListNode *_next;
} LinkedListNode;

typedef struct {
    struct LinkedListNode *_next;
} LinkedListIterator;

typedef bool (*LinkedListFindCallback)(LinkedListNode *, const void *);

// Constructor(s) & Destructor(s)
PUBLIC void LinkedList_Construct(LinkedList *pThis);
PUBLIC void LinkedList_Destruct(LinkedList *pThis);

PROTECTED void LinkedListNode_Construct(LinkedListNode *pThis);
PROTECTED void LinkedListNode_Destruct(LinkedListNode *pThis);

PUBLIC void LinkedListIterator_Construct(
    LinkedListIterator *pThis,
    LinkedList *list);

PUBLIC void LinkedListIterator_Destruct(LinkedListIterator *pThis);

// Public method(s)
PUBLIC void LinkedList_AddHead(LinkedList *pThis, LinkedListNode *node);
PUBLIC void LinkedList_AddTail(LinkedList *pThis, LinkedListNode *node);
PUBLIC void LinkedList_RemoveNode(LinkedList *pThis, LinkedListNode *node);

PUBLIC LinkedListNode *LinkedList_FindNode(
    LinkedList *pThis,
    LinkedListFindCallback callback,
    const void *data);

PUBLIC LinkedListNode *LinkedList_GetHead(LinkedList *pThis);
PUBLIC LinkedListNode *LinkedList_GetTail(LinkedList *pThis);

PUBLIC LinkedListNode *LinkedListNode_GetNext(LinkedListNode *pThis);
PUBLIC bool LinkedListIterator_HasNext(LinkedListIterator *pThis);
PUBLIC LinkedListNode *LinkedListIterator_GetNext(LinkedListIterator *pThis);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LINKED_LIST_H__
