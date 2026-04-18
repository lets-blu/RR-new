#ifndef __DATA_SELECTOR_TEST_H__
#define __DATA_SELECTOR_TEST_H__

#include "gtest/gtest.h"

#include "digital/selector/inc/data_selector.h"

class DataSelectorTest : public testing::Test {
protected:
    DataSelector mSelector;
    void SetUp(void);
    void TearDown(void);
};

#endif // __DATA_SELECTOR_TEST_H__
