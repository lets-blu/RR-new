#include <Arduino.h>

// Public member(s)
HardwareSerial Serial;
uint8_t gArduinoPinModes[ARDUINO_PIN_NUMBER];
uint8_t gArduinoPinValues[ARDUINO_PIN_NUMBER];
unsigned long gArduinoMillis;

uint8_t gArduinoPortB[ARDUINO_PORT_REGISTERS_NUMBER];
uint8_t gArduinoPortC[ARDUINO_PORT_REGISTERS_NUMBER];
uint8_t gArduinoPortD[ARDUINO_PORT_REGISTERS_NUMBER];

// Method implement(s)
void HardwareSerial::begin(unsigned long baudrate)
{
    mBaudrate = baudrate;
    memset(mBuffer, 0, ARDUINO_BUFFER_SIZE);
    RingBuffer_Construct(&mRingBuffer, mBuffer, ARDUINO_BUFFER_SIZE);
}

int HardwareSerial::available(void)
{
    return mRingBuffer._usedLength;
}

size_t HardwareSerial::readBytes(uint8_t *buffer, size_t bufferLength)
{
    return RingBuffer_Read(&mRingBuffer, buffer, bufferLength);
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t bufferSize)
{
    return RingBuffer_Write(&mRingBuffer, buffer, bufferSize);
}

RingBuffer *HardwareSerial::getRingBuffer(void)
{
    return &mRingBuffer;
}

void pinMode(uint8_t pin, uint8_t mode)
{
    if (pin < ARDUINO_PIN_NUMBER) {
        gArduinoPinModes[pin] = mode;
    }
}

int digitalRead(uint8_t pin)
{
    return (pin >= ARDUINO_PIN_NUMBER) ? 0 : gArduinoPinValues[pin];
}

void digitalWrite(uint8_t pin, uint8_t value)
{
    if (pin < ARDUINO_PIN_NUMBER) {
        gArduinoPinValues[pin] = value;
    }
}

unsigned long millis(void)
{
    return gArduinoMillis;
}
