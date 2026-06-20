# Phase 7 项目 3: CSV Parser
cmake_minimum_required(VERSION 3.20)
project(csv_parser
    VERSION 1.0.0
    DESCRIPTION "模板化 CSV 解析器"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CSV Parser 是 header-only 库，编译测试程序验证
add_executable(test_csv_parser test.cpp)

# 构建 & 运行:
#   cmake -S . -B build && cmake --build build && ./build/test_csv_parser
