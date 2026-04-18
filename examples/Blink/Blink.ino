#include <RR.h>
#include <port/arduino/inc/arduino_core.h>

ArduinoCore core;
LED led;

void initLogger(void);

void setup(void)
{
    ArduinoCore_Construct(&core);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &core.base);

    initLogger();
    LED_Construct(&led, NULL, LED_BUILTIN, BASE_PORT_VALUE_HIGH);
}

void loop(void)
{
    LED_TurnOn(&led);
    delay(1000);

    LED_TurnOff(&led);
    delay(1000);
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
