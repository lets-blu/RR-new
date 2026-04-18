#include "port/test/inc/base_component_test.h"

// Static member(s)
void *const BaseComponentTest::PORT = NULL;
const unsigned int BaseComponentTest::SER_PIN = 2;
const unsigned int BaseComponentTest::SCK_PIN = 3;
const unsigned int BaseComponentTest::RCK_PIN = 4;

const unsigned int BaseComponentTest::BIT = 0;

// Test case(s)
TEST_F(BaseComponentTest, CreatePort)
{
    EXPECT_EQ(&mGroup._vPort.base, CreatePort());
    EXPECT_TRUE(REGISTER_PORT_IS_CONSTRUCTED(&mGroup._vPort));
}

TEST_F(BaseComponentTest, DestroyPort)
{
    BaseComponent_DestroyPort(&mGroup.base, CreatePort());
    EXPECT_TRUE(REGISTER_PORT_IS_CONSTRUCTED(&mGroup._vPort));
}

TEST_F(BaseComponentTest, CreatePort_General)
{
    EXPECT_EQ(&mGroup._vPort.base, CreatePortGeneral());
    EXPECT_TRUE(REGISTER_PORT_IS_CONSTRUCTED(&mGroup._vPort));
}

TEST_F(BaseComponentTest, DestroyPort_General)
{
    BaseComponent_DestroyPort(&mGroup.base, CreatePortGeneral());
    EXPECT_TRUE(REGISTER_PORT_IS_CONSTRUCTED(&mGroup._vPort));
}

// Method implement(s)
void BaseComponentTest::SetUp(void)
{
    RegisterGroupParameter parameter = {
        .port = PORT,
        .serPin = SER_PIN,
        .sckPin = SCK_PIN,
        .rckPin = RCK_PIN,
    };

    ArduinoCore_Construct(&mCore);
    DeviceManager_SetCore(DeviceManager_GetInstance(), &mCore.base);

    ShiftRegister_Construct(&mRegister);
    RegisterGroup_Construct(&mGroup, &parameter);
    RegisterGroup_AddRegister(&mGroup, &mRegister);
}

void BaseComponentTest::TearDown(void)
{
    RegisterGroup_RemoveRegister(&mGroup, &mRegister);
    RegisterGroup_Destruct(&mGroup);
    ShiftRegister_Destruct(&mRegister);

    DeviceManager_SetCore(DeviceManager_GetInstance(), NULL);
    ArduinoCore_Destruct(&mCore);
}

BasePort *BaseComponentTest::CreatePort(void)
{
    RegisterPortParameter parameter = {
        .base = REGISTER_PORT_PARAMETER_BASE,
        .group = &mGroup,
    };

    return BaseComponent_CreatePort(
        &mGroup.base,
        REGISTER_GROUP_DIGITAL_PORT,
        &parameter.base);
}

BasePort *BaseComponentTest::CreatePortGeneral(void)
{
    GeneralPortParameter parameter = {
        .base = GENERAL_PORT_PARAMETER_BASE,
        .port = &mGroup,
    };

    return BaseComponent_CreatePort(
        &mGroup.base,
        GENERAL_DIGITAL_PORT,
        &parameter.base);
}
