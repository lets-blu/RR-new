#include <RR.h>
#include <port/arduino/inc/arduino_core.h>
#include <port/none/inc/none_system.h>

ArduinoCore core;
NoneSystem sys;
BaseSerial *serial;

DigitalButton button;
Logger logger = STATIC_LOGGER("Main", LOGGER_LEVEL_INFO);

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
    RegisterLogger(&logger);
    SetRxHandlerToBaseSerial(serial, RingBufferHandlerOfATCommand);

    // 3. Setup system
    ConstructNoneSystem(&sys);
    SetSystemToDeviceManager(manager, &sys.base);

    // 4. Create button
    ArduinoDPortParameter buttonParameter = {
        .base = ARDUINO_D_PORT_PARAMETER_BASE,
        .pin = A0
    };

    ConstructDigitalButton(
        &button,
        ARDUINO_CORE_DIGITAL_PORT,
        &buttonParameter.base,
        BASE_PORT_VALUE_LOW);

    SetEventHandlerToDigitalButton(&button, buttonEventHandler);
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

void buttonEventHandler(
    DigitalButton *sender,
    DigitalButtonEventParameter *parameter)
{
    if (sender == &button && parameter->event == DIGITAL_BUTTON_EVENT_CLICK)
    {
        LOGGER_I(&logger, "Button clicked!");
    }
}
