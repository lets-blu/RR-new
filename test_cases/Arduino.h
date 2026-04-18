#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "core/utils/inc/ring_buffer.h"

#define ARDUINO_PIN_NUMBER 14U
#define ARDUINO_BUFFER_SIZE 80U

#define INPUT 0x00U
#define OUTPUT 0x01U
#define INPUT_PULLUP 0x02U

#define LOW 0x00U
#define HIGH 0x01U

#define ARDUINO_PORT_REGISTERS_PIN 0U
#define ARDUINO_PORT_REGISTERS_DDR 1U
#define ARDUINO_PORT_REGISTERS_PORT 2U
#define ARDUINO_PORT_REGISTERS_NUMBER 3U

#define PINB (*(volatile uint8_t *)&gArduinoPortB[ARDUINO_PORT_REGISTERS_PIN])
#define DDRB (*(volatile uint8_t *)&gArduinoPortB[ARDUINO_PORT_REGISTERS_DDR])
#define PORTB (*(volatile uint8_t *)&gArduinoPortB[ARDUINO_PORT_REGISTERS_PORT])

#define PINC (*(volatile uint8_t *)&gArduinoPortC[ARDUINO_PORT_REGISTERS_PIN])
#define DDRC (*(volatile uint8_t *)&gArduinoPortC[ARDUINO_PORT_REGISTERS_DDR])
#define PORTC (*(volatile uint8_t *)&gArduinoPortC[ARDUINO_PORT_REGISTERS_PORT])

#define PIND (*(volatile uint8_t *)&gArduinoPortD[ARDUINO_PORT_REGISTERS_PIN])
#define DDRD (*(volatile uint8_t *)&gArduinoPortD[ARDUINO_PORT_REGISTERS_DDR])
#define PORTD (*(volatile uint8_t *)&gArduinoPortD[ARDUINO_PORT_REGISTERS_PORT])

class HardwareSerial {
private:
    unsigned long mBaudrate;
    uint8_t mBuffer[ARDUINO_BUFFER_SIZE];
    RingBuffer mRingBuffer;

public:
    void begin(unsigned long baudrate);
    int available(void);
    size_t readBytes(uint8_t *buffer, size_t bufferSize);
    size_t write(const uint8_t *buffer, size_t bufferLength);

    RingBuffer *getRingBuffer(void);
};

// Public member(s)
extern HardwareSerial Serial;
extern uint8_t gArduinoPinModes[ARDUINO_PIN_NUMBER];
extern uint8_t gArduinoPinValues[ARDUINO_PIN_NUMBER];
extern unsigned long gArduinoMillis;

extern uint8_t gArduinoPortB[ARDUINO_PORT_REGISTERS_NUMBER];
extern uint8_t gArduinoPortC[ARDUINO_PORT_REGISTERS_NUMBER];
extern uint8_t gArduinoPortD[ARDUINO_PORT_REGISTERS_NUMBER];

// Public method(s)
void pinMode(uint8_t pin, uint8_t mode);
int digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t value);
unsigned long millis(void);

#endif // __ARDUINO_H__
