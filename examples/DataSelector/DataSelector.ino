#include <RR.h>
#include <port/arduino/inc/arduino_core.h>

#define SELECTORS_NUMBER 2U

ArduinoCore core;
Logger logger = LOGGER_STATIC("Main", LOGGER_LEVEL_INFO);

SelectorGroup group;
DataSelector selectors[SELECTORS_NUMBER];
DigitalButton button;

void initLogger(void);
void eventHandler(void *sender, EventArgs *args);

void setup(void)
{
    DeviceManager *manager = DeviceManager_GetInstance();

    ArduinoCore_Construct(&core);
    DeviceManager_SetCore(manager, &core.base);

    initLogger();
    Logger_Register(&logger);

    SelectorGroup_Construct(&group, (void *)&PORTD, 0xf0, 0x04);
    DeviceManager_AddComponent(manager, &group.base);

    for (unsigned int i = 0; i < SELECTORS_NUMBER; i++) {
        DataSelector_Construct(
            &selectors[i],
            i * DATA_SELECTOR_DATA_BITS,
            (i + 1) * DATA_SELECTOR_DATA_BITS - 1);

        SelectorGroup_AddSelector(&group, &selectors[i]);
    }

    DigitalButton_Construct(&button, &group, 2, BASE_PORT_VALUE_LOW);
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
