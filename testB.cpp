// 一文掌握开源单元测试框架Google Test - 简书
// https://www.jianshu.com/p/83613ea7c1d3

#include <iostream>
#include <gtest/gtest.h>

class calcFunction
{
public:
    int add(int a, int b)
    {
        return a + b;
    }

    int sub(int a, int b)
    {
        return a - b;
    }
};

class calcFunctionTest : public testing::Test
{
protected:
    virtual void SetUp()
    {
        std::cout << "--> " << __func__ << " <--" <<std::endl;
    }
    virtual void TearDown()
    {
        std::cout << "--> " << __func__ << " <--" <<std::endl;
    }

    calcFunction calc;

};

TEST_F(calcFunctionTest, test_add)
{
    std::cout << "--> test_add start <--" << std::endl;
    EXPECT_EQ(calc.add(1,2), 3);
    std::cout << "--> test_add end <--" << std::endl;
}

TEST_F(calcFunctionTest, test_sub)
{
    std::cout << "--> test_sub start <--" << std::endl;
    EXPECT_EQ(calc.sub(1,2), -1);
    std::cout << "--> test_sub end <--" << std::endl;
}

int main(int argc, char **argv)
{  
    testing::InitGoogleTest(&argc, argv);  
    return RUN_ALL_TESTS(); 
} 
