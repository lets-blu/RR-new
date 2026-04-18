#ifndef __SHIFT_REGISTER_TEST_H__
#define __SHIFT_REGISTER_TEST_H__

#include "gtest/gtest.h"

#include "digital/register/inc/shift_register.h"

class ShiftRegisterTest : public testing::Test {
protected:
    ShiftRegister mRegister;
    static const unsigned int BIT;

    void SetUp(void);
    void TearDown(void);
    void SetBit(void);
};

#endif // __SHIFT_REGISTER_TEST_H__
