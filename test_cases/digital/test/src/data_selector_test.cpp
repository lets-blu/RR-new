#include "digital/test/inc/data_selector_test.h"

// Test case(s)
TEST_F(DataSelectorTest, GetStartAddress)
{
    EXPECT_EQ(0U, DataSelector_GetStartAddress(&mSelector));
}

TEST_F(DataSelectorTest, GetEndAddress)
{
    EXPECT_EQ(
        DATA_SELECTOR_DATA_BITS - 1,
        DataSelector_GetEndAddress(&mSelector));
}

// Method implement(s)
void DataSelectorTest::SetUp(void)
{
    DataSelector_Construct(&mSelector, 0, DATA_SELECTOR_DATA_BITS - 1);
}

void DataSelectorTest::TearDown(void)
{
    DataSelector_Destruct(&mSelector);
}
