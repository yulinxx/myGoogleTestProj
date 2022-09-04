#include <gtest/gtest.h>

int Addx(int value1, int value2)
{
    return (value1 + value2);
}

TEST(Addx, case1)
{
  EXPECT_LT(-2, Addx(1, 2));
  EXPECT_EQ(-1, Addx(1, 2));
  ASSERT_LT(-2, Addx(1, 2));
  ASSERT_EQ(-1, Addx(1, 2));
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc,argv); //初始化

  return RUN_ALL_TESTS();
}
