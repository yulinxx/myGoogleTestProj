// 一文掌握开源单元测试框架Google Test - 简书
// https://www.jianshu.com/p/83613ea7c1d3

// TEST_F宏
// TEST_F主要是进行多样测试，就是多种不同情况的测试TestCase中都会使用相同一份的测试数据的时候将会才用它。
// 即用相同的数据测试不同的行为，如果采用TEST宏进行测试那么将会为不同的测试case创建一份数据。TEST_F宏将会共用一份避免重复拷贝共具灵活性。

// 语法定义为：
// TEST_F(test_case_name, test_name);
// test_case_name第一个参数是测试用例名,必须取类名。这个和TEST宏不同
// test_name 第二个参数是测试名这个随便取，但最好取有意义的名称
// 使用TEST_F时必须继承::testing::Test类。并且该类提供了两个接口void SetUp(); void TearDown();
// void SetUp()函数,为测试准备对象.
// void TearDown()函数 为测试后销毁对象资源
// https://blog.csdn.net/wteruiycbqqvwt/article/details/125625975

#include <iostream>
#include <gtest/gtest.h>
#include <memory>

////////////////////////////////////////////////////////////
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
    // void SetUp()函数,为测试准备数据对象
    virtual void SetUp()
    {
        std::cout << "1 --> " << __func__ << " <--" << std::endl;
    }
    // void TearDown()函数 为测试后销毁对象资源。
    virtual void TearDown()
    {
        std::cout << "4 --> " << __func__ << " <--" << std::endl;
    }

    calcFunction calcObj; // 定义对象
};

TEST_F(calcFunctionTest, test_add)
{
    std::cout << "  2 --> test_add start <--" << std::endl;
    EXPECT_EQ(calcObj.add(1, 2), 3);
    std::cout << "  3 --> test_add end <--" << std::endl;
}

TEST_F(calcFunctionTest, test_sub)
{
    std::cout << "  2 --> test_sub start <--" << std::endl;
    EXPECT_EQ(calcObj.sub(1, 2), -1);
    std::cout << "  3 --> test_sub end <--" << std::endl;
}

////////////////////////////////////////////////////////////

class Base
{
public:
    Base(std::string name) : m_name{name}
    {
        std::cout << "Create constructor name: " << m_name << std::endl;
    }

    std::string getName()
    {
        return m_name;
    }

    void setName(const std::string &name)
    {
        m_name = std::string(name);
    }

    ~Base()
    {
        std::cout << "Destory base" << std::endl;
    }

private:
    std::string m_name;
};

class BaseTest : public ::testing::Test
{
protected:
    // 为测试准备数据对象
    void SetUp() override
    {
        m_base = std::make_shared<Base>("SvenBaseTest");
    }
    // 清除资源
    void TearDown() override
    {
        m_base.reset();
    }

    std::shared_ptr<Base> m_base;
};

TEST_F(BaseTest, testCreateInstance)
{
    std::unique_ptr<Base> instance = std::make_unique<Base>("SvenBaseUnique");
    EXPECT_NE(instance, nullptr);
    instance.reset();
    EXPECT_EQ(instance, nullptr);
}

TEST_F(BaseTest, testGetName)
{
    auto name = m_base->getName();
    EXPECT_STREQ(name.c_str(), "SvenBaseTest");
}

TEST_F(BaseTest, testSetName)
{
    m_base->setName("NewSvenBase");
    auto name = m_base->getName();
    EXPECT_STREQ(name.c_str(), "NewSvenBase");
}

////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
