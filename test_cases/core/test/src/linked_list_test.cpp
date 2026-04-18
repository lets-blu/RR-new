#include "core/test/inc/linked_list_test.h"

// Private method(s)
PRIVATE void LinkedListTestNode_Construct(LinkedListTestNode *pThis);
PRIVATE void LinkedListTestNode_Destruct(LinkedListTestNode *pThis);

// Test case(s)
TEST_F(LinkedListTest, AddHead)
{
    AddNode(true);
    EXPECT_EQ(&mNodes[LINKED_LIST_TEST_NODES_NUMBER - 1].base, mList._head);
    EXPECT_EQ(&mNodes[0].base, mList._tail);

    for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
        if (i == 0) {
            EXPECT_EQ(NULL, mNodes[i].base._next);
        } else {
            EXPECT_EQ(&mNodes[i - 1].base, mNodes[i].base._next);
        }
    }
}

TEST_F(LinkedListTest, AddTail)
{
    AddNode(false);
    EXPECT_EQ(&mNodes[0].base, mList._head);
    EXPECT_EQ(&mNodes[LINKED_LIST_TEST_NODES_NUMBER - 1].base, mList._tail);

    for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
        if (i != LINKED_LIST_TEST_NODES_NUMBER - 1) {
            EXPECT_EQ(&mNodes[i + 1].base, mNodes[i].base._next);
        } else {
            EXPECT_EQ(NULL, mNodes[i].base._next);
        }
    }
}

TEST_F(LinkedListTest, RemoveNode)
{
    AddNode(false);

    for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
        LinkedList_RemoveNode(&mList, &mNodes[i].base);

        if (i != LINKED_LIST_TEST_NODES_NUMBER - 1) {
            EXPECT_EQ(&mNodes[i + 1].base, mList._head);

            EXPECT_EQ(
                &mNodes[LINKED_LIST_TEST_NODES_NUMBER - 1].base,
                mList._tail);
        } else {
            EXPECT_EQ(NULL, mList._head);
            EXPECT_EQ(NULL, mList._tail);
        }
    }
}

TEST_F(LinkedListTest, FindNode)
{
    AddNode(false);

    for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
        EXPECT_EQ(
            &mNodes[i].base,
            LinkedList_FindNode(&mList, FindCallback, &mNodes[i]));
    }
}

TEST_F(LinkedListTest, GetHead)
{
    AddNode(false);
    EXPECT_EQ(&mNodes[0].base, LinkedList_GetHead(&mList));
}

TEST_F(LinkedListTest, GetTail)
{
    AddNode(false);

    EXPECT_EQ(
        &mNodes[LINKED_LIST_TEST_NODES_NUMBER - 1].base,
        LinkedList_GetTail(&mList));
}

TEST_F(LinkedListTest, Node_GetNext)
{
    AddNode(false);

    for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
        if (i != LINKED_LIST_TEST_NODES_NUMBER - 1) {
            EXPECT_EQ(
                &mNodes[i + 1].base,
                LinkedListNode_GetNext(&mNodes[i].base));
        } else {
            EXPECT_EQ(NULL, LinkedListNode_GetNext(&mNodes[i].base));
        }
    }
}

TEST_F(LinkedListTest, Iterator_HasNext)
{
    LinkedListIterator iterator;

    AddNode(false);
    LinkedListIterator_Construct(&iterator, &mList);
    EXPECT_TRUE(LinkedListIterator_HasNext(&iterator));

    LinkedListIterator_Destruct(&iterator);
}

TEST_F(LinkedListTest, Iterator_GetNext)
{
    LinkedListIterator iterator;

    AddNode(false);
    LinkedListIterator_Construct(&iterator, &mList);

    for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
        EXPECT_EQ(&mNodes[i].base, LinkedListIterator_GetNext(&iterator));
    }

    LinkedListIterator_Destruct(&iterator);
}

// Method implement(s)
void LinkedListTest::SetUp(void)
{
    LinkedList_Construct(&mList);

    for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
        LinkedListTestNode_Construct(&mNodes[i]);
    }
}

void LinkedListTest::TearDown(void)
{
    for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
        LinkedListTestNode_Destruct(&mNodes[i]);
    }

    LinkedList_Destruct(&mList);
}

void LinkedListTest::AddNode(bool toHead)
{
    if (toHead) {
        for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
            LinkedList_AddHead(&mList, &mNodes[i].base);
        }
    } else {
        for (unsigned int i = 0; i < LINKED_LIST_TEST_NODES_NUMBER; i++) {
            LinkedList_AddTail(&mList, &mNodes[i].base);
        }
    }
}

bool LinkedListTest::FindCallback(LinkedListNode *node, const void *data)
{
    if (node == NULL) {
        return false;
    }

    return LinkedListNode2LinkedListTestNode(node) == data;
}

PRIVATE void LinkedListTestNode_Construct(LinkedListTestNode *pThis)
{
    LinkedListNode_Construct(&pThis->base);
}

PRIVATE void LinkedListTestNode_Destruct(LinkedListTestNode *pThis)
{
    LinkedListNode_Destruct(&pThis->base);
    memset(pThis, 0, sizeof(LinkedListTestNode));
}
