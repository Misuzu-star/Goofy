#include <iostream>
#include <gtest/gtest.h>
#include "ncGuid.h"

class ncGuidTest : public testing::Test
{
protected:
    void SetUp(void) override
    {
        std::cout << "=========== ncGuidTest SetUp ===========" << std::endl;
    }

    void TearDown(void) override
    {
        std::cout << "========== ncGuidTest TearDown =========" << std::endl;
    }
};

TEST_F(ncGuidTest, tt1)
{
    ncGuid guid;
    std::cout << guid.ToHexString() << std::endl;
}
