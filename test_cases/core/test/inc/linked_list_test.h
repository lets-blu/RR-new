#ifndef __LINKED_LIST_TEST_H__
#define __LINKED_LIST_TEST_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "gtest/gtest.h"

#include "core/utils/inc/keywords.h"
#include "core/utils/inc/linked_list.h"

#define LINKED_LIST_TEST_NODES_NUMBER 3U

#define LinkedListNode2LinkedListTestNode(pThis) \
    CONTAINER_OF(pThis, LinkedListTestNode, base)

typedef struct {
    LinkedListNode base;
} LinkedListTestNode;

class LinkedListTest : public testing::Test {
protected:
    LinkedList mList;
    LinkedListTestNode mNodes[LINKED_LIST_TEST_NODES_NUMBER];

    void SetUp(void);
    void TearDown(void);
    void AddNode(bool toHead);

    static bool FindCallback(LinkedListNode *node, const void *data);
};

#endif // __LINKED_LIST_TEST_H__
