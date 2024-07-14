#include <RR.h>
#include <port/arduino/inc/ArduinoCore.h>

ArduinoCore core;
LED led;

void setup() {
    DeviceManager *manager = InstanceOfDeviceManager();

    Serial.begin(9600);
    fdevopen(serialPutc, NULL);

    ConstructArduinoCore(&core);
    SetCoreToDeviceManager(manager, &core.base);

    ArduinoDPortParameter parameter = {
        .base = ARDUINO_D_PORT_PARAMETER_BASE,
        .pin = LED_BUILTIN
    };

    ConstructLED(&led, &parameter.base, BASE_PORT_VALUE_HIGH);
}

void loop() {
    TurnOnLED(&led);
    delay(1000);

    TurnOffLED(&led);
    delay(1000);
}

int serialPutc(char c, FILE *file)
{
    (void)file;
    Serial.write(c);
    return c;
}
