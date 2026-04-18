#include "digital/test/inc/shift_register_test.h"

// Static member(s)
const unsigned int ShiftRegisterTest::BIT = 0;

// Test case(s)
TEST_F(ShiftRegisterTest, SetBit)
{
    SetBit();
    EXPECT_EQ(1 << BIT, mRegister._data);
}

TEST_F(ShiftRegisterTest, ResetBit)
{
    SetBit();
    ShiftRegister_ResetBit(&mRegister, BIT);
    EXPECT_EQ(0U, mRegister._data);
}

TEST_F(ShiftRegisterTest, GetData)
{
    SetBit();
    EXPECT_EQ(1 << BIT, ShiftRegister_GetData(&mRegister));
}

// Method implement(s)
void ShiftRegisterTest::SetUp(void)
{
    ShiftRegister_Construct(&mRegister);
}

void ShiftRegisterTest::TearDown(void)
{
    ShiftRegister_Destruct(&mRegister);
}

void ShiftRegisterTest::SetBit(void)
{
    ShiftRegister_SetBit(&mRegister, BIT);
}
