#include "port/test/inc/base_task_test.h"

// Static member(s)
unsigned int BaseTaskTest::sCounter = 0;

// Test case(s)
TEST_F(BaseTaskTest, Start)
{
    sCounter = 0;
    BaseTask_Start(&mTask.base);
    EXPECT_EQ(1U, sCounter);
}

// Method implement(s)
void BaseTaskTest::SetUp(void)
{
    NoneTaskParameter parameter = {
        .base = NONE_TASK_PARAMETER_BASE,
        .entry = TaskEntry,
        .parameter = NULL,
    };

    NoneTask_Construct(&mTask, &parameter);
}

void BaseTaskTest::TearDown(void)
{
    NoneTask_Destruct(&mTask);
}

void BaseTaskTest::TaskEntry(void *parameter)
{
    (void)parameter;
    sCounter++;
}
