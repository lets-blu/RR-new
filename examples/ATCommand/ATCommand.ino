#include <RR.h>
#include <port/arduino/inc/arduino_core.h>

#define BUFFER_SIZE 80U

ArduinoCore core;
uint8_t buffer[BUFFER_SIZE];

ATCommand command;
Logger logger = LOGGER_STATIC("Main", LOGGER_LEVEL_INFO);

void commandHandler(void *sender, EventArgs *args);

void setup(void)
{
    ArduinoSerialParameter parameter = {
        .base = ARDUINO_SERIAL_PARAMETER_BASE,
        .serial = &Serial,
        .baudrate = 115200,
        .rxBuffer = buffer,
        .rxBufferSize = BUFFER_SIZE,
    };

    BaseSerial *serial = NULL;

    ArduinoCore_Construct(&core);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &core.base);

    serial = DeviceFactory_CreateSerial(
        DeviceManager_GetInstance(),
        ARDUINO_CORE_UART_SERIAL,
        &parameter.base);

    Logger_SetSerial(serial);
    Logger_Register(&logger);

    ATCommand_SetSerial(serial);
    ATCommand_Construct(&command, "+TEST", commandHandler);
}

void loop(void)
{
    DeviceManager_TaskEntry(DeviceManager_GetInstance());
}

void commandHandler(void *sender, EventArgs *args)
{
    (void)sender;
    ATCommandEventArgs *commandArgs = EventArgs2ATCommandEventArgs(args);

    if (args == NULL) {
        return;
    }

    for (int i = 0; i < commandArgs->argc; i++) {
        LOGGER_I(&logger, "commandHandler, argv[%d]: %s",
            i, commandArgs->argv[i]);
    }
}
