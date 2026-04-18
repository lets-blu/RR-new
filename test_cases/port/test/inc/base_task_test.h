#ifndef __BASE_TASK_TEST_H__
#define __BASE_TASK_TEST_H__

#include "gtest/gtest.h"

#include "port/none/inc/none_task.h"
#include "port/system/inc/base_task.h"

class BaseTaskTest : public testing::Test {
protected:
    NoneTask mTask;
    static unsigned int sCounter;

    void SetUp(void);
    void TearDown(void);
    static void TaskEntry(void *parameter);
};

#endif // __BASE_TASK_TEST_H__
