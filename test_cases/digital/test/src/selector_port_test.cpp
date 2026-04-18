#include "digital/test/inc/selector_port_test.h"

// Static member(s)
void *const SelectorPortTest::PORT = (void *)&PORTB;
const unsigned int SelectorPortTest::ADDRESS_PINS = 0x07;
const unsigned int SelectorPortTest::DATA_PIN = 0x08;

const unsigned int SelectorPortTest::BIT = 0;

// Test case(s)
TEST_F(SelectorPortTest, SetMode)
{
    BasePort_SetMode(&mPort.base, BIT, BASE_PORT_MODE_INPUT);
}

TEST_F(SelectorPortTest, Read)
{
#if defined(ARDUINO_ARCH_AVR)
    unsigned int value = 0;

    *ARDUINO_PORT_GET_AVR_PIN(PORT) = DATA_PIN;
    value = BasePort_Read(&mPort.base, BIT);

    EXPECT_EQ(
        BIT << BasePort_GetPinOffset(ADDRESS_PINS),
        *ARDUINO_PORT_GET_AVR_PORT(PORT) & ADDRESS_PINS);

    EXPECT_EQ(BASE_PORT_VALUE_HIGH, value);
#endif // ARDUINO_ARCH_AVR
}

TEST_F(SelectorPortTest, Write)
{
    BasePort_Write(&mPort.base, BIT, BASE_PORT_VALUE_LOW);
}

// Method implement(s)
void SelectorPortTest::SetUp(void)
{
    SelectorPortParameter parameter = {
        .base = SELECTOR_PORT_PARAMETER_BASE,
        .group = &mGroup,
    };

    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);

    DataSelector_Construct(
        &mSelector,
        0,
        DATA_SELECTOR_DATA_BITS - 1);

    SelectorGroup_Construct(&mGroup, PORT, ADDRESS_PINS, DATA_PIN);
    SelectorGroup_AddSelector(&mGroup, &mSelector);
    SelectorPort_Construct(&mPort, &parameter);
}

void SelectorPortTest::TearDown(void)
{
    SelectorPort_Destruct(&mPort);
    SelectorGroup_RemoveSelector(&mGroup, &mSelector);
    SelectorGroup_Destruct(&mGroup);
    DataSelector_Destruct(&mSelector);

    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}
