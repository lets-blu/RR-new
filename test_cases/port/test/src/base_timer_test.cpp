#include "port/test/inc/base_timer_test.h"

// Static member(s)
unsigned int BaseTimerTest::sCounter = 0;
const unsigned long BaseTimerTest::DELAY = 1000;

// Test case(s)
TEST_F(BaseTimerTest, Start)
{
    gArduinoMillis = 0;
    StartTimer();
    EXPECT_EQ(gArduinoMillis + DELAY, mTimer._timeout);

    sCounter = 0;
    gArduinoMillis += DELAY;
    NoneTimer_CheckTimers();
    EXPECT_EQ(1U, sCounter);
}

TEST_F(BaseTimerTest, Stop)
{
    gArduinoMillis = 0;
    StartTimer();
    BaseTimer_Stop(&mTimer.baseTimer);

    sCounter = 0;
    gArduinoMillis += DELAY;
    NoneTimer_CheckTimers();
    EXPECT_EQ(0U, sCounter);
}

// Method implement(s)
void BaseTimerTest::SetUp(void)
{
    NoneTimerParameter parameter = {
        .base = NONE_TIMER_PARAMETER_BASE,
        .handler = EventHandler,
    };

    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    NoneTimer_Construct(&mTimer, &parameter);
}

void BaseTimerTest::TearDown(void)
{
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    ArduinoCore_Destruct(&mCore);
    NoneTimer_Destruct(&mTimer);
}

void BaseTimerTest::StartTimer(void)
{
    BaseTimer_Start(&mTimer.baseTimer, DELAY);
}

void BaseTimerTest::EventHandler(void *sender, EventArgs *args)
{
    (void)sender;
    (void)args;
    sCounter++;
}
