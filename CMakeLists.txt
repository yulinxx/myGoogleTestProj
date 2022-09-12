# g++ -std=c++11 testA.cpp -o test -lgtest -lpthread

cmake_minimum_required(VERSION 3.0.0)
project(g_test VERSION 0.1.0)

# 查找 GTest 库
find_package(GTest REQUIRED)

# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

set(CPP_DIR
    ./
)

foreach(SUB_DIR ${CPP_DIR})
    message(STATUS "---Sub Dir: ${SUB_DIR}")

    file(GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/${SUB_DIR}/*.cpp")

    foreach(CPP ${SRC})
        message(STATUS "---Create Exe From: ${CPP}")

        STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${CPP})
        MESSAGE(" --- FILE_NAME"  ${FILE_NAME})

        add_executable(test_${FILE_NAME} ${CPP} )
        
        # 链接测试库
        target_link_libraries(test_${FILE_NAME}
        ${GTEST_BOTH_LIBRARIES}
        pthread )

        # 添加到测试
        gtest_discover_tests(test_${FILE_NAME})

    endforeach(CPP)    

endforeach(SUB_DIR)
