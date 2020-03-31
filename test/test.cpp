#include "gtest/gtest.h"
#include "sum.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(test, small) {
    EXPECT_EQ(sum(2, 7),9);
}