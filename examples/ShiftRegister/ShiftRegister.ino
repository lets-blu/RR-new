#include <RR.h>
#include <port/arduino/inc/arduino_core.h>

#define REGISTERS_NUMBER 2U
#define LEDS_NUMBER (REGISTERS_NUMBER * SHIFT_REGISTER_DATA_BITS)

ArduinoCore core;
RegisterGroup group;
ShiftRegister registers[REGISTERS_NUMBER];
LED leds[LEDS_NUMBER];

void setup(void)
{
    RegisterGroupParameter parameter = {
        .port = NULL,
        .serPin = 2,
        .sckPin = 3,
        .rckPin = 4,
    };

    DeviceManager *manager = DeviceManager_GetInstance();

    ArduinoCore_Construct(&core);
    DeviceManager_SetCore(manager, &core.base);

    RegisterGroup_Construct(&group, &parameter);
    DeviceManager_AddComponent(manager, &group.base);

    for (unsigned int i = 0; i < REGISTERS_NUMBER; i++) {
        ShiftRegister_Construct(&registers[i]);
        RegisterGroup_AddRegister(&group, &registers[i]);
    }

    for (unsigned int i = 0; i < LEDS_NUMBER; i++) {
        LED_Construct(&leds[i], &group, i, BASE_PORT_VALUE_HIGH);
    }
}

void loop(void)
{
    for (unsigned int i = 0; i < LEDS_NUMBER; i++) {
        if (i == 0) {
            LED_TurnOff(&leds[LEDS_NUMBER - 1]);
        } else {
            LED_TurnOff(&leds[i - 1]);
        }

        LED_TurnOn(&leds[i]);
        delay(100);
    }
}
