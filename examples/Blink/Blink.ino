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
    ConstructArduinoCore(&core);
    SetCoreToDeviceManager(manager, &core.base);

    // 2. Setup logger and AT command
    ArduinoUARTParameter uartParameter = {
        .base = ARDUINO_UART_PARAMETER_BASE,
        .port = &Serial,
        .baudrate = 115200,
        .rxBufferSize = AT_COMMAND_MAX_LENGTH
    };

    serial = CreateSerialWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        ARDUINO_CORE_UART_SERIAL,
        &uartParameter.base);

    fdevopen(serialPutc, NULL);
    SetRxHandlerToBaseSerial(serial, RingBufferHandlerOfATCommand);

    // 3. Setup system
    ConstructNoneSystem(&sys);
    SetSystemToDeviceManager(manager, &sys.base);

    // 4. Create LED
    ConstructLED(&led, NULL, LED_BUILTIN, BASE_PORT_VALUE_HIGH);

    // 5. Create thread and task
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

    // 6. Run system
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
