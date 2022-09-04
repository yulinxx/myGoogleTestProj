#include <gtest/gtest.h>

int Addx(int value1, int value2)
{
    return (value1 + value2);
}

/*
gtest中断言的宏可以分为两类：一类是ASSERT宏，另一类就是EXPECT宏了。
1、ASSERT_系列： 如果当前点检测失败 则 退出 当前函数
2、EXPECT_系列： 如果当前点检测失败 则 继续 往下执行
如果你对自动输出的错误信息不满意的话，也是可以通过 operator<< 能够在失败的时候打印日志，将一些自定义的信息输出。
比如：
ASSERT_TRUE(Abs(1) == 1) << "Abs(1)=1";

ASSERT_系列：

bool值检查
1、ASSERT_TRUE(参数)，期待结果是true
2、ASSERT_FALSE(参数)，期待结果是false

数值型数据检查
3、ASSERT_EQ(参数1，参数2)，传入的是需要比较的两个数 equal
4、ASSERT_NE(参数1，参数2)，not equal，不等于才返回true

5、ASSERT_LT(参数1，参数2)，less than，小于才返回true
6、ASSERT_GT(参数1，参数2)，greater than，大于才返回true
7、ASSERT_LE(参数1，参数2)，less equal，小于等于才返回true
8、ASSERT_GE(参数1，参数2)，greater equal，大于等于才返回true

字符串检查
9、ASSERT_STREQ(expected_str, actual_str)，两个C风格的字符串相等才正确返回
10、ASSERT_STRNE(str1, str2)，两个C风格的字符串不相等时才正确返回

11、ASSERT_STRCASEEQ(expected_str, actual_str)
12、ASSERT_STRCASENE(str1, str2)

EXPECT_系列，也是具有类似的宏结构的
————————————————
https://blog.csdn.net/hu_hao/article/details/125029138
*/

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
