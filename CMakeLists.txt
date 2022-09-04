# g++ -std=c++11 testA.cpp -o test -lgtest -lpthread

cmake_minimum_required(VERSION 3.0.0)
project(g_test VERSION 0.1.0)

# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(g_test testA.cpp)

# 链接测试库
target_link_libraries( g_test
        ${GTEST_BOTH_LIBRARIES}
        pthread )

# 添加到测试
gtest_discover_tests(g_test)