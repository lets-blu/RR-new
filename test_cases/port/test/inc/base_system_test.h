#ifndef __BASE_SYSTEM_TEST_H__
#define __BASE_SYSTEM_TEST_H__

#include "gtest/gtest.h"

#include "port/core/inc/base_timer.h"
#include "port/core/inc/general_timer.h"
#include "port/system/inc/base_system.h"
#include "port/system/inc/base_task.h"
#include "port/system/inc/general_task.h"

#include "port/none/inc/none_system.h"
#include "port/none/inc/none_task.h"
#include "port/none/inc/none_timer.h"

class BaseSystemTest : public testing::Test {
protected:
    NoneSystem mSystem;

    void SetUp(void);
    void TearDown(void);

    BaseTask *CreateTask(void);
    BaseTask *CreateTaskGeneral(void);
    BaseTimer *CreateTimer(void);
    BaseTimer *CreateTimerGeneral(void);

    static void TaskEntry(void *parameter);
    static void EventHandler(void *sender, EventArgs *args);
};

#endif // __BASE_SYSTEM_TEST_H__
