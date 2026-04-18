#include "digital/test/inc/register_group_test.h"

// Static member(s)
void *const RegisterGroupTest::PORT = NULL;
const unsigned int RegisterGroupTest::SER_PIN = 0;
const unsigned int RegisterGroupTest::SCK_PIN = 1;
const unsigned int RegisterGroupTest::RCK_PIN = 2;

const unsigned int RegisterGroupTest::BIT = 0;

// Test case(s)
TEST_F(RegisterGroupTest, AddRegister)
{
    AddRegister();

    EXPECT_EQ(
        &mRegisters[REGISTER_GROUP_TEST_REGISTERS_NUMBER - 1].base,
        LinkedList_GetHead(&mGroup._registers));

    EXPECT_EQ(&mRegisters[0].base, LinkedList_GetTail(&mGroup._registers));

    for (unsigned int i = 0; i < REGISTER_GROUP_TEST_REGISTERS_NUMBER; i++) {
        if (i == 0) {
            EXPECT_EQ(NULL, LinkedListNode_GetNext(&mRegisters[i].base));
        } else {
            EXPECT_EQ(
                &mRegisters[i - 1].base,
                LinkedListNode_GetNext(&mRegisters[i].base));
        }
    }
}

TEST_F(RegisterGroupTest, RemoveRegister)
{
    AddRegister();

    for (unsigned int i = 0; i < REGISTER_GROUP_TEST_REGISTERS_NUMBER; i++) {
        RegisterGroup_RemoveRegister(&mGroup, &mRegisters[i]);

        if (i == REGISTER_GROUP_TEST_REGISTERS_NUMBER - 1) {
            EXPECT_EQ(NULL, LinkedList_GetHead(&mGroup._registers));
            EXPECT_EQ(NULL, LinkedList_GetTail(&mGroup._registers));
        } else {
            EXPECT_EQ(
                &mRegisters[REGISTER_GROUP_TEST_REGISTERS_NUMBER - 1].base,
                LinkedList_GetHead(&mGroup._registers));

            EXPECT_EQ(
                &mRegisters[i + 1].base,
                LinkedList_GetTail(&mGroup._registers));
        }
    }
}

TEST_F(RegisterGroupTest, SetBit)
{
    AddRegister();
    SetBit();

    EXPECT_EQ(1 << BIT, ShiftRegister_GetData(&mRegisters[0]));
    EXPECT_EQ(1, gArduinoPinValues[SER_PIN]);
}

TEST_F(RegisterGroupTest, ResetBit)
{
    AddRegister();
    SetBit();

    RegisterGroup_ResetBit(&mGroup, BIT);
    EXPECT_EQ(0U, ShiftRegister_GetData(&mRegisters[0]));
    EXPECT_EQ(0U, gArduinoPinValues[SER_PIN]);
}

// Method implement(s)
void RegisterGroupTest::SetUp(void)
{
    RegisterGroupParameter parameter = {
        .port = PORT,
        .serPin = SER_PIN,
        .sckPin = SCK_PIN,
        .rckPin = RCK_PIN,
    };

    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);
    RegisterGroup_Construct(&mGroup, &parameter);

    for (unsigned int i = 0; i < REGISTER_GROUP_TEST_REGISTERS_NUMBER; i++) {
        ShiftRegister_Construct(&mRegisters[i]);
    }
}

void RegisterGroupTest::TearDown(void)
{
    for (unsigned int i = 0; i < REGISTER_GROUP_TEST_REGISTERS_NUMBER; i++) {
        RegisterGroup_RemoveRegister(&mGroup, &mRegisters[i]);
        ShiftRegister_Destruct(&mRegisters[i]);
    }

    RegisterGroup_Destruct(&mGroup);
    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

void RegisterGroupTest::AddRegister(void)
{
    for (unsigned int i = 0; i < REGISTER_GROUP_TEST_REGISTERS_NUMBER; i++) {
        RegisterGroup_AddRegister(&mGroup, &mRegisters[i]);
    }
}

void RegisterGroupTest::SetBit(void)
{
    RegisterGroup_SetBit(&mGroup, BIT);
}
