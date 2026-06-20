# Phase 7 项目 2: Thread Pool
cmake_minimum_required(VERSION 3.20)
project(thread_pool
    VERSION 1.0.0
    DESCRIPTION "简单线程池实现"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ThreadPool 是 header-only 库，编译测试程序验证
add_executable(test_thread_pool test.cpp)
target_link_libraries(test_thread_pool PRIVATE pthread)

# 构建 & 运行:
#   cmake -S . -B build && cmake --build build && ./build/test_thread_pool
