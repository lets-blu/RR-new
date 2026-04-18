#include "port/test/inc/base_system_test.h"

// Test case(s)
TEST_F(BaseSystemTest, CreateTask)
{
    EXPECT_EQ(&mSystem._task.base, CreateTask());
    EXPECT_TRUE(NONE_TASK_IS_CONSTRUCTED(&mSystem._task));
}

TEST_F(BaseSystemTest, DestroyTask)
{
    BaseSystem_DestroyTask(&mSystem.base, CreateTask());
    EXPECT_FALSE(NONE_TASK_IS_CONSTRUCTED(&mSystem._task));
}

TEST_F(BaseSystemTest, CreateTask_General)
{
    EXPECT_EQ(&mSystem._task.base, CreateTaskGeneral());
    EXPECT_TRUE(NONE_TASK_IS_CONSTRUCTED(&mSystem._task));
}

TEST_F(BaseSystemTest, DestroyTask_General)
{
    BaseSystem_DestroyTask(&mSystem.base, CreateTaskGeneral());
    EXPECT_FALSE(NONE_TASK_IS_CONSTRUCTED(&mSystem._task));
}

TEST_F(BaseSystemTest, CreateTimer)
{
    EXPECT_EQ(&mSystem._timers[0].baseTimer, CreateTimer());
    EXPECT_TRUE(NONE_TIMER_IS_CONSTRUCTED(&mSystem._timers[0]));
}

TEST_F(BaseSystemTest, DestroyTimer)
{
    BaseSystem_DestroyTimer(&mSystem.base, CreateTimer());
    EXPECT_FALSE(NONE_TIMER_IS_CONSTRUCTED(&mSystem._timers[0]));
}

TEST_F(BaseSystemTest, CreateTimer_General)
{
    EXPECT_EQ(&mSystem._timers[0].baseTimer, CreateTimerGeneral());
    EXPECT_TRUE(NONE_TIMER_IS_CONSTRUCTED(&mSystem._timers[0]));
}

TEST_F(BaseSystemTest, DestroyTimer_General)
{
    BaseSystem_DestroyTimer(&mSystem.base, CreateTimerGeneral());
    EXPECT_FALSE(NONE_TIMER_IS_CONSTRUCTED(&mSystem._timers[0]));
}

// Method implement(s)
void BaseSystemTest::SetUp(void)
{
    NoneSystem_Construct(&mSystem);
}

void BaseSystemTest::TearDown(void)
{
    NoneSystem_Destruct(&mSystem);
}

BaseTask *BaseSystemTest::CreateTask(void)
{
    NoneTaskParameter parameter = {
        .base = NONE_TASK_PARAMETER_BASE,
        .entry = TaskEntry,
        .parameter = NULL,
    };

    return BaseSystem_CreateTask(
        &mSystem.base,
        NONE_SYSTEM_TASK,
        &parameter.base);
}

BaseTask *BaseSystemTest::CreateTaskGeneral(void)
{
    GeneralTaskParameter parameter = {
        .base = GENERAL_TASK_PARAMETER_BASE,
        .entry = TaskEntry,
        .parameter = NULL,
    };

    return BaseSystem_CreateTask(&mSystem.base, GENERAL_TASK, &parameter.base);
}

BaseTimer *BaseSystemTest::CreateTimer(void)
{
    NoneTimerParameter parameter = {
        .base = NONE_TIMER_PARAMETER_BASE,
        .handler = EventHandler,
    };

    return BaseSystem_CreateTimer(
        &mSystem.base,
        NONE_SYSTEM_TIMER,
        &parameter.base);
}

BaseTimer *BaseSystemTest::CreateTimerGeneral(void)
{
    GeneralTimerParameter parameter = {
        .base = GENERAL_TIMER_PARAMETER_BASE,
        .handler = EventHandler,
    };

    return BaseSystem_CreateTimer(
        &mSystem.base,
        GENERAL_SOFTWARE_TIMER,
        &parameter.base);
}

void BaseSystemTest::TaskEntry(void *parameter)
{
    (void)parameter;
}

void BaseSystemTest::EventHandler(void *sender, EventArgs *args)
{
    (void)sender;
    (void)args;
}
