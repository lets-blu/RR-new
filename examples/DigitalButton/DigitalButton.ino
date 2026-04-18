#include <RR.h>
#include <port/arduino/inc/arduino_core.h>

ArduinoCore core;
DigitalButton button;
Logger logger = LOGGER_STATIC("Main", LOGGER_LEVEL_INFO);

void initLogger(void);
void eventHandler(void *sender, EventArgs *args);

void setup(void)
{
    ArduinoCore_Construct(&core);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &core.base);

    initLogger();
    Logger_Register(&logger);

    DigitalButton_Construct(&button, NULL, 2, BASE_PORT_VALUE_LOW);
    DigitalButton_SetEventHandler(&button, eventHandler);
    DigitalButton_EnableSample(&button, true);
}

void loop(void)
{
    DeviceManager_TaskEntry(DeviceManager_GetInstance());
}

void initLogger(void)
{
    ArduinoSerialParameter parameter = {
        .base = ARDUINO_SERIAL_PARAMETER_BASE,
        .serial = &Serial,
        .baudrate = 115200,
        .rxBuffer = NULL,
        .rxBufferSize = 0,
    };

    BaseSerial *serial = DeviceFactory_CreateSerial(
        DeviceFactory_GetInstance(),
        ARDUINO_CORE_UART_SERIAL,
        &parameter.base);

    Logger_SetSerial(serial);
}

void eventHandler(void *sender, EventArgs *args)
{
    (void)sender;
    (void)args;
    LOGGER_I(&logger, "Button clicked!");
}
