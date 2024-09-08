#include <stdio.h>

#include <RR.h>
#include <port/arduino/inc/arduino_core.h>
#include <port/none/inc/none_system.h>

#include "blink_thread.h"

ArduinoCore core;
NoneSystem sys;

LED led;
BaseTask *task;
BlinkThread thread;

void setup()
{
    DeviceManager *manager = InstanceOfDeviceManager();

    Serial.begin(9600);
    fdevopen(serialPutc, NULL);

    // 1. Setup core & system
    ConstructArduinoCore(&core);
    SetCoreToDeviceManager(manager, &core.base);

    ConstructNoneSystem(&sys);
    SetSystemToDeviceManager(manager, &sys.base);

    // 2. Create LED
    ArduinoDPortParameter ledParameter = {
        .base = ARDUINO_D_PORT_PARAMETER_BASE,
        .pin = LED_BUILTIN
    };

    ConstructLED(
        &led,
        ARDUINO_CORE_DIGITAL_PORT,
        &ledParameter.base,
        BASE_PORT_VALUE_HIGH);

    // 3. Create thread & task
    ConstructBlinkThread(&thread, &led, 1000);

    NoneTaskParameter taskParameter = {
        .base = NONE_TASK_PARAMETER_BASE,
        .entry = RunBlinkThreadTask,
        .parameter = &thread
    };

    task = CreateTaskWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        NONE_SYSTEM_TASK,
        &taskParameter.base);

    if (task == NULL)
    {
        AddThreadToDeviceManager(
            manager,
            DEVICE_MANAGER_THREAD_APPLICATION,
            &thread.base);
    }

    // 4. Run system
    RunBaseSystem(&sys.base);
}

void loop()
{
    // Never reached
}

int serialPutc(char c, FILE *file)
{
    (void)file;
    Serial.write(c);
    return c;
}
