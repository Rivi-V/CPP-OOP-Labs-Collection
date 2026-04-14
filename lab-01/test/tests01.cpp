#include <gtest/gtest.h>
#include "../include/height.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(height(100,10,910)==10);
}

TEST(test_02, test_one_day)
{
    ASSERT_TRUE(height(10,1,9)==1);
}

TEST(test_03, slow_test)
{
    ASSERT_TRUE(height(2,1,10)==9);
}

TEST(test_04, fast_test)
{
    ASSERT_TRUE(height(10,2,34)==4);
}

TEST(test_05, test_one_day)
{
    ASSERT_TRUE(height(10,1,10)==1);
}

TEST(test_06, no_night_test)
{
    ASSERT_TRUE(height(5,0,20)==4);
}

TEST(test_07, large_test)
{
    ASSERT_TRUE(height(1000,500,100000)==199);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}