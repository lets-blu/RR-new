#include "digital/test/inc/selector_group_test.h"

// Static member(s)
void *const SelectorGroupTest::PORT = (void *)&PORTB;
const unsigned int SelectorGroupTest::ADDRESS_PINS = 0x07;
const unsigned int SelectorGroupTest::DATA_PIN = 0x08;

const unsigned int SelectorGroupTest::BIT = 0;

// Test case(s)
TEST_F(SelectorGroupTest, AddSelector)
{
    AddSelector();
    EXPECT_EQ(&mSelectors[0].base, LinkedList_GetHead(&mGroup._selectors));

    EXPECT_EQ(
        &mSelectors[SELECTOR_GROUP_TEST_SELECTORS_NUMBER - 1].base,
        LinkedList_GetTail(&mGroup._selectors));

    for (unsigned int i = 0; i < SELECTOR_GROUP_TEST_SELECTORS_NUMBER; i++) {
        if (i == SELECTOR_GROUP_TEST_SELECTORS_NUMBER - 1) {
            EXPECT_EQ(NULL, LinkedListNode_GetNext(&mSelectors[i].base));
        } else {
            EXPECT_EQ(
                &mSelectors[i + 1].base,
                LinkedListNode_GetNext(&mSelectors[i].base));
        }
    }
}

TEST_F(SelectorGroupTest, RemoveSelector)
{
    AddSelector();

    for (unsigned int i = 0; i < SELECTOR_GROUP_TEST_SELECTORS_NUMBER; i++) {
        SelectorGroup_RemoveSelector(&mGroup, &mSelectors[i]);

        if (i == SELECTOR_GROUP_TEST_SELECTORS_NUMBER - 1) {
            EXPECT_EQ(NULL, LinkedList_GetHead(&mGroup._selectors));
            EXPECT_EQ(NULL, LinkedList_GetTail(&mGroup._selectors));
        } else {
            EXPECT_EQ(
                &mSelectors[i + 1].base,
                LinkedList_GetHead(&mGroup._selectors));

            EXPECT_EQ(
                &mSelectors[SELECTOR_GROUP_TEST_SELECTORS_NUMBER - 1].base,
                LinkedList_GetTail(&mGroup._selectors));
        }
    }
}

TEST_F(SelectorGroupTest, GetBit)
{
    AddSelector();

#if defined(ARDUINO_ARCH_AVR)
    unsigned int value = 0;

    *ARDUINO_PORT_GET_AVR_PIN(PORT) = DATA_PIN;
    value = SelectorGroup_GetBit(&mGroup, BIT);

    EXPECT_EQ(
        BIT << BasePort_GetPinOffset(ADDRESS_PINS),
        *ARDUINO_PORT_GET_AVR_PORT(PORT) & ADDRESS_PINS);

    EXPECT_EQ(BASE_PORT_VALUE_HIGH, value);
#endif // ARDUINO_ARCH_AVR
}

// Method implement(s)
void SelectorGroupTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    SelectorGroup_Construct(&mGroup, PORT, ADDRESS_PINS, DATA_PIN);

    for (unsigned int i = 0; i < SELECTOR_GROUP_TEST_SELECTORS_NUMBER; i++) {
        DataSelector_Construct(
            &mSelectors[i],
            i * DATA_SELECTOR_DATA_BITS,
            (i + 1) * DATA_SELECTOR_DATA_BITS - 1);
    }
}

void SelectorGroupTest::TearDown(void)
{
    for (unsigned int i = 0; i < SELECTOR_GROUP_TEST_SELECTORS_NUMBER; i++) {
        SelectorGroup_RemoveSelector(&mGroup, &mSelectors[i]);
        DataSelector_Destruct(&mSelectors[i]);
    }

    SelectorGroup_Destruct(&mGroup);
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

void SelectorGroupTest::AddSelector(void)
{
    for (unsigned int i = 0; i < SELECTOR_GROUP_TEST_SELECTORS_NUMBER; i++) {
        SelectorGroup_AddSelector(&mGroup, &mSelectors[i]);
    }
}
