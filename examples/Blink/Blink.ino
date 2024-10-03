#include <RR.h>
#include <port/arduino/inc/arduino_core.h>
#include <port/none/inc/none_system.h>

#include "blink_thread.h"

ArduinoCore core;
NoneSystem sys;
BaseSerial *serial;

LED led;
BaseTask *task;
BlinkThread thread;

void setup()
{
    DeviceManager *manager = InstanceOfDeviceManager();

    // 1. Setup core
    ArduinoUARTParameter uartParameter = {
        .base = ARDUINO_UART_PARAMETER_BASE,
        .port = &Serial,
        .baudrate = 115200
    };

    ConstructArduinoCore(&core);
    SetCoreToDeviceManager(manager, &core.base);

    serial = CreateSerialWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        ARDUINO_CORE_UART_SERIAL,
        &uartParameter.base);

    fdevopen(serialPutc, NULL);

    // 2. Setup system
    ConstructNoneSystem(&sys);
    SetSystemToDeviceManager(manager, &sys.base);

    // 3. Create LED
    ArduinoDPortParameter ledParameter = {
        .base = ARDUINO_D_PORT_PARAMETER_BASE,
        .pin = LED_BUILTIN
    };

    ConstructLED(
        &led,
        ARDUINO_CORE_DIGITAL_PORT,
        &ledParameter.base,
        BASE_PORT_VALUE_HIGH);

    // 4. Create thread & task
    NoneTaskParameter taskParameter = {
        .base = NONE_TASK_PARAMETER_BASE,
        .entry = RunBlinkThreadTask,
        .parameter = &thread
    };

    ConstructBlinkThread(&thread, &led, 1000);

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

    // 5. Run system
    RunBaseSystem(&sys.base);
}

void loop()
{
    // Never reached
}

int serialPutc(char c, FILE *file)
{
    (void)file;
    WriteBaseSerial(serial, (const uint8_t *)&c, sizeof(char));
    return c;
}
