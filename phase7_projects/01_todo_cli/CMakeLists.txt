# Phase 7 项目 1: TODO CLI
cmake_minimum_required(VERSION 3.20)
project(todo_cli
    VERSION 1.0.0
    DESCRIPTION "命令行 TODO 管理工具"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(todo_cli main.cpp)

# 构建 & 运行:
#   cmake -S . -B build && cmake --build build && ./build/todo_cli
