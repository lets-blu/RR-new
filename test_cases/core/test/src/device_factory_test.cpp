#include "core/test/inc/device_factory_test.h"

// Static member(s)
void *const DeviceFactoryTest::PORT = NULL;
HardwareSerial *const DeviceFactoryTest::SERIAL = &Serial;
const unsigned long DeviceFactoryTest::BAUDRATE = 115200;

// Test case(s)
TEST_F(DeviceFactoryTest, GetInstance)
{
    EXPECT_EQ(NULL, DeviceFactory_GetInstance());
}

TEST_F(DeviceFactoryTest, CreatePort)
{
    EXPECT_EQ(&mCore._ports[0].base, CreatePort());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(DeviceFactoryTest, DestroyPort)
{
    DeviceFactory_DestroyPort(DeviceFactory_GetInstance(), CreatePort());
    EXPECT_TRUE(ARDUINO_PORT_IS_CONSTRUCTED(&mCore._ports[0]));
}

TEST_F(DeviceFactoryTest, CreateSerial)
{
    EXPECT_EQ(&mCore._serials[0].base, CreateSerial());
    EXPECT_TRUE(ARDUINO_SERIAL_IS_CONSTRUCTED(&mCore._serials[0]));
}

TEST_F(DeviceFactoryTest, DestroySerial)
{
    DeviceFactory_DestroySerial(DeviceFactory_GetInstance(), CreateSerial());
    EXPECT_FALSE(ARDUINO_SERIAL_IS_CONSTRUCTED(&mCore._serials[0]));
}

TEST_F(DeviceFactoryTest, CreateTask)
{
    EXPECT_EQ(&mSystem._task.base, CreateTask());
    EXPECT_TRUE(NONE_TASK_IS_CONSTRUCTED(&mSystem._task));
}

TEST_F(DeviceFactoryTest, DestroyTask)
{
    DeviceFactory_DestroyTask(DeviceFactory_GetInstance(), CreateTask());
    EXPECT_FALSE(NONE_TASK_IS_CONSTRUCTED(&mSystem._task));
}

TEST_F(DeviceFactoryTest, CreateTimer)
{
    EXPECT_EQ(&mSystem._timers[0].baseTimer, CreateTimer());
    EXPECT_TRUE(NONE_TIMER_IS_CONSTRUCTED(&mSystem._timers[0]));
}

TEST_F(DeviceFactoryTest, DestroyTimer)
{
    DeviceFactory_DestroyTimer(DeviceFactory_GetInstance(), CreateTimer());
    EXPECT_FALSE(NONE_TIMER_IS_CONSTRUCTED(&mSystem._timers[0]));
}

// Method implement(s)
void DeviceFactoryTest::SetUp(void)
{
    DeviceManager *manager = DeviceManager_GetInstance();

    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(manager, &mCore.base);

    NoneSystem_Construct(&mSystem);
    DeviceManager_SetSystem(manager, &mSystem.base);
}

void DeviceFactoryTest::TearDown(void)
{
    DeviceManager *manager = DeviceManager_GetInstance();

    DeviceManager_SetCore(manager, NULL);
    ArduinoCore_Destruct(&mCore);

    DeviceManager_SetSystem(manager, NULL);
    NoneSystem_Destruct(&mSystem);
}

BasePort *DeviceFactoryTest::CreatePort(void)
{
    GeneralPortParameter parameter = {
        .base = GENERAL_PORT_PARAMETER_BASE,
        .port = PORT,
    };

    return DeviceFactory_CreatePort(
        DeviceFactory_GetInstance(),
        GENERAL_DIGITAL_PORT,
        &parameter.base);
}

BaseSerial *DeviceFactoryTest::CreateSerial(void)
{
    GeneralSerialParameter parameter = {
        .base = GENERAL_SERIAL_PARAMETER_BASE,
        .serial = SERIAL,
        .baudrate = BAUDRATE,
    };

    return DeviceFactory_CreateSerial(
        DeviceFactory_GetInstance(),
        GENERAL_UART_SERIAL,
        &parameter.base);
}

BaseTask *DeviceFactoryTest::CreateTask(void)
{
    GeneralTaskParameter parameter = {
        .base = GENERAL_TASK_PARAMETER_BASE,
        .entry = TaskEntry,
        .parameter = NULL,
    };

    return DeviceFactory_CreateTask(
        DeviceFactory_GetInstance(),
        GENERAL_TASK,
        &parameter.base);
}

BaseTimer *DeviceFactoryTest::CreateTimer(void)
{
    GeneralTimerParameter parameter = {
        .base = GENERAL_TIMER_PARAMETER_BASE,
        .handler = EventHandler,
    };

    return DeviceFactory_CreateTimer(
        DeviceFactory_GetInstance(),
        GENERAL_SOFTWARE_TIMER,
        &parameter.base);
}

void DeviceFactoryTest::TaskEntry(void *parameter)
{
    (void)parameter;
}

void DeviceFactoryTest::EventHandler(void *sender, EventArgs *args)
{
    (void)sender;
    (void)args;
}
