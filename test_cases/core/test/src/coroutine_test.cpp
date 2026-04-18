#include "core/test/inc/coroutine_test.h"

// Static member(s)
unsigned int CoroutineTest::sCounter = 0;
const unsigned int CoroutineTest::REPEAT_TIMES = 3;
const unsigned long CoroutineTest::SLEEP_TIME = 1000;

// Test case(s)
TEST_F(CoroutineTest, INIT)
{
    COROUTINE_INIT(&mCoroutine);
    EXPECT_EQ(0U, mCoroutine._line);
}

TEST_F(CoroutineTest, YIELD)
{
    sCounter = 0;

    for (unsigned int i = 0; i < REPEAT_TIMES; i++) {
        RunYield(&mCoroutine);
        EXPECT_EQ(i + 1, sCounter);
    }
}

TEST_F(CoroutineTest, SLEEP)
{
    sCounter = 0;
    gArduinoMillis = 0;

    for (unsigned int i = 0; i < REPEAT_TIMES; i++) {
        RunSleep(&mCoroutine);
        gArduinoMillis += SLEEP_TIME;
        EXPECT_EQ(i + 1, sCounter);
    }
}

// Method implement(s)
void CoroutineTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    Coroutine_Construct(&mCoroutine);
}

void CoroutineTest::TearDown(void)
{
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
    Coroutine_Destruct(&mCoroutine);
}

CoroutineState CoroutineTest::RunYield(Coroutine *coroutine)
{
    COROUTINE_BEGIN(coroutine);

    for (;;) {
        sCounter++;
        COROUTINE_YIELD(coroutine);
    }

    COROUTINE_END(coroutine);
}

CoroutineState CoroutineTest::RunSleep(Coroutine *coroutine)
{
    COROUTINE_BEGIN(coroutine);

    for (;;) {
        sCounter++;
        COROUTINE_SLEEP(coroutine, SLEEP_TIME);
    }

    COROUTINE_END(coroutine);
}
