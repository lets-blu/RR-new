#include "core/test/inc/device_manager_test.h"

// Static member(s)
unsigned int DeviceManagerTest::sCounter = 0;

void *const DeviceManagerTest::PORT = NULL;
const unsigned int DeviceManagerTest::SER_PIN = 2;
const unsigned int DeviceManagerTest::SCK_PIN = 3;
const unsigned int DeviceManagerTest::RCK_PIN = 4;
const unsigned int DeviceManagerTest::BIT = 0;

const unsigned long DeviceManagerTest::DELAY = 1000;

// Private method(s)
PRIVATE void DeviceManagerTestCoroutine_Construct(
    DeviceManagerTestCoroutine *pThis);

PRIVATE void DeviceManagerTestCoroutine_Destruct(
    DeviceManagerTestCoroutine *pThis);

// Override method(s)
PUBLIC CoroutineState DeviceManagerTestCoroutine_Run(
    LinkedCoroutine *coroutine);

// Virtual methods table(s)
static const LinkedCoroutineVtbl baseVtbl = {
    .Run = DeviceManagerTestCoroutine_Run,
};

// Test case(s)
TEST_F(DeviceManagerTest, GetInstance)
{
    EXPECT_NE((DeviceManager *)NULL, DeviceManager_GetInstance());
}

TEST_F(DeviceManagerTest, SetCore)
{
    SetCore();
    EXPECT_EQ(&mCore.base, DeviceManager_GetInstance()->_core);
}

TEST_F(DeviceManagerTest, GetCore)
{
    SetCore();
    EXPECT_EQ(&mCore.base, DeviceManager_GetCore(DeviceManager_GetInstance()));
}

TEST_F(DeviceManagerTest, SetSystem)
{
    SetSystem();
    EXPECT_EQ(&mSystem.base, DeviceManager_GetInstance()->_system);
}

TEST_F(DeviceManagerTest, GetSystem)
{
    SetSystem();
    EXPECT_EQ(&mSystem.base, DeviceManager_GetSystem(DeviceManager_GetInstance()));
}

TEST_F(DeviceManagerTest, AddComponent)
{
    LinkedListNode *node = NULL;

    AddComponent();

    node = LinkedList_FindNode(
        &DeviceManager_GetInstance()->_components,
        FindCallback,
        &mGroup.base.base);

    EXPECT_EQ(&mGroup.base.base, node);
}

TEST_F(DeviceManagerTest, RemoveComponent)
{
    LinkedListNode *node;
    DeviceManager *manager = DeviceManager_GetInstance();

    AddComponent();
    DeviceManager_RemoveComponent(manager, &mGroup.base);

    node = LinkedList_FindNode(
        &manager->_components,
        FindCallback,
        &mGroup.base.base);

    EXPECT_EQ(NULL, node);
}

TEST_F(DeviceManagerTest, AddCoroutine)
{
    LinkedListNode *node = NULL;

    AddCoroutine();

    node = LinkedList_FindNode(
        &DeviceManager_GetInstance()->_coroutines,
        FindCallback,
        &mCoroutine.base.base);

    EXPECT_EQ(&mCoroutine.base.base, node);
}

TEST_F(DeviceManagerTest, RemoveCoroutine)
{
    LinkedListNode *node = NULL;
    DeviceManager *manager = DeviceManager_GetInstance();

    AddCoroutine();
    DeviceManager_RemoveCoroutine(manager, &mCoroutine.base);

    node = LinkedList_FindNode(
        &manager->_coroutines,
        FindCallback,
        &mCoroutine.base.base);

    EXPECT_EQ(NULL, node);
}

TEST_F(DeviceManagerTest, GetComponents)
{
    DeviceManager *manager = DeviceManager_GetInstance();
    EXPECT_EQ(&manager->_components, DeviceManager_GetComponents(manager));
}

TEST_F(DeviceManagerTest, TaskEntry)
{
    AddCoroutine();
    DeviceManager_TaskEntry(DeviceManager_GetInstance());
    EXPECT_EQ(1U, mCoroutine._counter);
}

// Method implement(s)
void DeviceManagerTest::SetUp(void)
{
    RegisterGroupParameter parameter = {
        .port = PORT,
        .serPin = SER_PIN,
        .sckPin = SCK_PIN,
        .rckPin = RCK_PIN,
    };

    ArduinoCore_Construct(&mCore);
    NoneSystem_Construct(&mSystem);
    RegisterGroup_Construct(&mGroup, &parameter);
    DeviceManagerTestCoroutine_Construct(&mCoroutine);
}

void DeviceManagerTest::TearDown(void)
{
    DeviceManager *manager = DeviceManager_GetInstance();

    DeviceManager_RemoveComponent(manager, &mGroup.base);
    RegisterGroup_Destruct(&mGroup);

    DeviceManager_SetCore(manager, NULL);
    ArduinoCore_Destruct(&mCore);

    DeviceManager_SetSystem(manager, NULL);
    NoneSystem_Destruct(&mSystem);

    DeviceManager_RemoveCoroutine(manager, &mCoroutine.base);
    DeviceManagerTestCoroutine_Destruct(&mCoroutine);
}

void DeviceManagerTest::SetCore(void)
{
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
}

void DeviceManagerTest::SetSystem(void)
{
    DeviceManager_SetSystem(DeviceManager_GetInstance(), &mSystem.base);
}

void DeviceManagerTest::AddComponent(void)
{
    DeviceManager_AddComponent(DeviceManager_GetInstance(), &mGroup.base);
}

void DeviceManagerTest::AddCoroutine(void)
{
    DeviceManager_AddCoroutine(DeviceManager_GetInstance(), &mCoroutine.base);
}

bool DeviceManagerTest::FindCallback(LinkedListNode *node, const void *data)
{
    return (node == NULL) ? false : (node == data);
}

void DeviceManagerTest::EventHandler(void *sender, EventArgs *args)
{
    (void)sender;
    (void)args;
    sCounter++;
}

PRIVATE void DeviceManagerTestCoroutine_Construct(
    DeviceManagerTestCoroutine *pThis)
{
    LinkedCoroutine_Construct(&pThis->base);
    pThis->base.vtbl = &baseVtbl;
    pThis->_counter = 0;
}

PRIVATE void DeviceManagerTestCoroutine_Destruct(
    DeviceManagerTestCoroutine *pThis)
{
    LinkedCoroutine_Destruct(&pThis->base);
    memset(pThis, 0, sizeof(DeviceManagerTestCoroutine));
}

PUBLIC CoroutineState DeviceManagerTestCoroutine_Run(LinkedCoroutine *coroutine)
{
    DeviceManagerTestCoroutine *pThis
        = LinkedCoroutine2DeviceManagerTestCoroutine(coroutine);

    if (coroutine == NULL) {
        return COROUTINE_STATE_ENDED;
    }

    LINKED_COROUTINE_BEGIN(coroutine);

    for (;;) {
        pThis->_counter++;
        LINKED_COROUTINE_YIELD(coroutine);
    }

    LINKED_COROUTINE_END(coroutine);
}
