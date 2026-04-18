#include "digital/test/inc/register_port_test.h"

// Static member(s)
void *const RegisterPortTest::PORT = NULL;
const unsigned int RegisterPortTest::SER_PIN = 2;
const unsigned int RegisterPortTest::SCK_PIN = 3;
const unsigned int RegisterPortTest::RCK_PIN = 4;

const unsigned int RegisterPortTest::BIT = 0;

// Test case(s)
TEST_F(RegisterPortTest, SetMode)
{
    BasePort_SetMode(&mPort.base, BIT, BASE_PORT_MODE_OUTPUT);
}

TEST_F(RegisterPortTest, Read)
{
    BasePort_Read(&mPort.base, BIT);
}

TEST_F(RegisterPortTest, Write)
{
    BasePort_Write(&mPort.base, BIT, BASE_PORT_VALUE_HIGH);
    EXPECT_EQ(1, gArduinoPinValues[SER_PIN]);
}

// Method implement(s)
void RegisterPortTest::SetUp(void)
{
    RegisterGroupParameter groupParameter = {
        .port = PORT,
        .serPin = SER_PIN,
        .sckPin = SCK_PIN,
        .rckPin = RCK_PIN,
    };

    RegisterPortParameter portParamtere = {
        .base = REGISTER_PORT_PARAMETER_BASE,
        .group = &mGroup,
    };

    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);

    ShiftRegister_Construct(&mRegister);
    RegisterGroup_Construct(&mGroup, &groupParameter);
    RegisterGroup_AddRegister(&mGroup, &mRegister);
    RegisterPort_Construct(&mPort, &portParamtere);
}

void RegisterPortTest::TearDown(void)
{
    RegisterPort_Destruct(&mPort);
    RegisterGroup_RemoveRegister(&mGroup, &mRegister);
    RegisterGroup_Destruct(&mGroup);
    ShiftRegister_Destruct(&mRegister);

    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}
