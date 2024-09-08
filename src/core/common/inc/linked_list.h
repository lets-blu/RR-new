#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/common/inc/keywords.h"

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

typedef bool (*LinkedListFindCallback)(LinkedListNode *, void *);

// Constructor(s) & Destructor(s)
PUBLIC void ConstructLinkedList(LinkedList *instance);
PUBLIC void DestructLinkedList(LinkedList *instance);

PROTECTED void ConstructLinkedListNode(LinkedListNode *instance);
PROTECTED void DestructLinkedListNode(LinkedListNode *instance);

PUBLIC void ConstructLinkedListIterator(
    LinkedListIterator *instance,
    LinkedList *list);

PUBLIC void DestructLinkedListIterator(LinkedListIterator *instance);

// Public method(s)
PUBLIC void AddNodeToLinkedList(
    LinkedList *self,
    LinkedListNode *node);

PUBLIC void RemoveNodeFromLinkedList(
    LinkedList *self,
    LinkedListNode *node);

PUBLIC LinkedListNode *FindNodeInLinkedList(
    LinkedList *self,
    LinkedListFindCallback callback,
    void *data);

PUBLIC STATIC bool FindEqualCallbackOfLinkedList(
    LinkedListNode *node,
    void *data);

PUBLIC bool HasNextInLinkedListIterator(LinkedListIterator *self);
PUBLIC LinkedListNode *NextInLinkedListIterator(LinkedListIterator *self);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __LINKED_LIST_H__
