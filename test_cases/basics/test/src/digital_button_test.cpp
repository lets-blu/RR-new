#include "basics/test/inc/digital_button_test.h"

// Static member(s)
unsigned int DigitalButtonTest::sCounter = 0;

void *const DigitalButtonTest::PORT = NULL;
const unsigned int DigitalButtonTest::PIN = 0x01;
const unsigned int DigitalButtonTest::PRESS_VALUE = BASE_PORT_VALUE_LOW;

// Test case(s)
TEST_F(DigitalButtonTest, SetEventHandler)
{
    SetEventHandler();
    EXPECT_EQ(EventHandler, mButton._handler);
}

TEST_F(DigitalButtonTest, EnableSample)
{
    LinkedListNode *node = NULL;
    DeviceManager *manager = DeviceManager_GetInstance();

    SetEventHandler();
    DigitalButton_EnableSample(&mButton, true);

    node = LinkedList_FindNode(
        &manager->_coroutines,
        FindCallback,
        &mButton._coroutine);

    EXPECT_EQ(&mButton._coroutine.base.base, node);

    sCounter = 0;
    gArduinoPinValues[PIN] = PRESS_VALUE;

    DeviceManager_TaskEntry(manager);
    gArduinoMillis += DIGITAL_BUTTON_SAMPLE_INTERVAL;
    DeviceManager_TaskEntry(manager);
    gArduinoMillis += DIGITAL_BUTTON_SAMPLE_INTERVAL;

    if (PRESS_VALUE == BASE_PORT_VALUE_LOW) {
        gArduinoPinValues[PIN] = BASE_PORT_VALUE_HIGH;
    } else {
        gArduinoPinValues[PIN] = BASE_PORT_VALUE_LOW;
    }

    DeviceManager_TaskEntry(manager);
    gArduinoMillis += DIGITAL_BUTTON_SAMPLE_INTERVAL;
    DeviceManager_TaskEntry(manager);
    EXPECT_EQ(1U, sCounter);
}

// Method implement(s)
void DigitalButtonTest::SetUp(void)
{
    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    DigitalButton_Construct(&mButton, PORT, PIN, PRESS_VALUE);
}

void DigitalButtonTest::TearDown(void)
{
    DigitalButton_Destruct(&mButton);
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

void DigitalButtonTest::SetEventHandler(void)
{
    DigitalButton_SetEventHandler(&mButton, EventHandler);
}

void DigitalButtonTest::EventHandler(void *sender, EventArgs *args)
{
    (void)sender;
    (void)args;
    sCounter++;
}

bool DigitalButtonTest::FindCallback(LinkedListNode *node, const void *data)
{
    if (node == NULL) {
        return false;
    }

    return (LinkedListNode2DigitalButtonCoroutine(node) == data);
}
