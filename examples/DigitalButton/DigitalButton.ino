#include <RR.h>
#include <port/arduino/inc/arduino_core.h>
#include <port/none/inc/none_system.h>

ArduinoCore core;
NoneSystem sys;

DigitalButton button;
EventHandler handler;

BaseSerial *serial;
RingBuffer ringBuffer;
uint8_t buffer[AT_COMMAND_MAX_LENGTH];
Logger logger = STATIC_LOGGER("Main", LOGGER_LEVEL_INFO);

void setup()
{
    DeviceManager *manager = InstanceOfDeviceManager();

    // 1. Setup core
    ConstructArduinoCore(&core);
    SetCoreToDeviceManager(manager, &core.base);

    // 2. Setup logger and AT command
    ConstructRingBuffer(&ringBuffer, buffer, AT_COMMAND_MAX_LENGTH);

    ArduinoUARTSerialParameter uartParameter = {
        .base = ARDUINO_UART_SERIAL_PARAMETER_BASE,
        .baudrate = 115200,
        .buffer = &ringBuffer
    };

    serial = CreateSerialWithBaseFactories(
        GetFactoriesFromDeviceManager(manager),
        ARDUINO_CORE_UART_SERIAL,
        &uartParameter.base);

    fdevopen(serialPutc, NULL);
    RegisterLogger(&logger);
    AddEventHandlerToBaseSerial(serial, EventHandlerOfATCommand());

    // 3. Setup system
    ConstructNoneSystem(&sys);
    SetSystemToDeviceManager(manager, &sys.base);

    // 4. Create button
    ConstructDigitalButton(&button, NULL, 14, BASE_PORT_VALUE_LOW);
    ConstructEventHandler(&handler, eventHandler);
    AddEventHandlerToDigitalButton(&button, &handler);
    EnableAutoScanToDigitalButton(&button, true);

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

void eventHandler(void *sender, EventParameter *parameter)
{
    DigitalButtonEventParameter *buttonParameter
        = EventParameter2DigitalButtonEventParameter(parameter);

    if (sender == &button
        && parameter != NULL
        && buttonParameter->event == DIGITAL_BUTTON_EVENT_CLICKED)
    {
        LOGGER_I(&logger, "Button clicked!");
    }
}
