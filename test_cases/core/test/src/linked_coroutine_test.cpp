#include "core/test/inc/linked_coroutine_test.h"

// Static member(s)
const unsigned int LinkedCoroutineTest::REPEAT_TIMES = 3;
const unsigned long LinkedCoroutineTest::SLEEP_TIME = 1000;

// Private method(s)
PRIVATE void TestLinkedCoroutine_Construct(
    TestLinkedCoroutine *pThis,
    const LinkedCoroutineVtbl *vtbl);

PRIVATE void TestLinkedCoroutine_Destruct(TestLinkedCoroutine *pThis);

// Override method(s)
PUBLIC CoroutineState TestLinkedCoroutine_RunYield(LinkedCoroutine *coroutine);
PUBLIC CoroutineState TestLinkedCoroutine_RunSleep(LinkedCoroutine *coroutine);

// Virtual methods table(s)
static const LinkedCoroutineVtbl yieldVtbl = {
    .Run = TestLinkedCoroutine_RunYield,
};

static const LinkedCoroutineVtbl sleepVtbl = {
    .Run = TestLinkedCoroutine_RunSleep,
};

// Test case(s)
TEST_F(LinkedCoroutineTest, INIT)
{
    LINKED_COROUTINE_INIT(&mCoroutine.base);
    EXPECT_EQ(0U, mCoroutine.base._coroutine._line);
}

TEST_F(LinkedCoroutineTest, YIELD)
{
    TestLinkedCoroutine_Construct(&mCoroutine, &yieldVtbl);

    for (unsigned int i = 0; i < REPEAT_TIMES; i++) {
        LinkedCoroutine_Run(&mCoroutine.base);
        EXPECT_EQ(i + 1, mCoroutine._counter);
    }

    TestLinkedCoroutine_Destruct(&mCoroutine);
}

TEST_F(LinkedCoroutineTest, SLEEP)
{
    gArduinoMillis = 0;
    TestLinkedCoroutine_Construct(&mCoroutine, &sleepVtbl);

    for (unsigned int i = 0; i < REPEAT_TIMES; i++) {
        LinkedCoroutine_Run(&mCoroutine.base);
        gArduinoMillis += SLEEP_TIME;
        EXPECT_EQ(i + 1, mCoroutine._counter);
    }

    TestLinkedCoroutine_Destruct(&mCoroutine);
}

// Method implement(s)
unsigned long LinkedCoroutineTest::GetSleepTime(void)
{
    return SLEEP_TIME;
}

void LinkedCoroutineTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
}

void LinkedCoroutineTest::TearDown(void)
{
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

PRIVATE void TestLinkedCoroutine_Construct(
    TestLinkedCoroutine *pThis,
    const LinkedCoroutineVtbl *vtbl)
{
    LinkedCoroutine_Construct(&pThis->base);
    pThis->base.vtbl = vtbl;
    pThis->_counter = 0;
}

PRIVATE void TestLinkedCoroutine_Destruct(TestLinkedCoroutine *pThis)
{
    LinkedCoroutine_Destruct(&pThis->base);
    memset(pThis, 0, sizeof(TestLinkedCoroutine));
}

PUBLIC CoroutineState TestLinkedCoroutine_RunYield(LinkedCoroutine *coroutine)
{
    TestLinkedCoroutine *pThis = LinkedCoroutine2TestLinkedCoroutine(coroutine);

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

PUBLIC CoroutineState TestLinkedCoroutine_RunSleep(LinkedCoroutine *coroutine)
{
    TestLinkedCoroutine *pThis = LinkedCoroutine2TestLinkedCoroutine(coroutine);

    if (coroutine == NULL) {
        return COROUTINE_STATE_ENDED;
    }

    LINKED_COROUTINE_BEGIN(coroutine);

    for (;;) {
        pThis->_counter++;
        LINKED_COROUTINE_SLEEP(coroutine, LinkedCoroutineTest::GetSleepTime());
    }

    LINKED_COROUTINE_END(coroutine);
}
