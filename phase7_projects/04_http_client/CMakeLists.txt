# Phase 7 项目 4: HTTP Client
cmake_minimum_required(VERSION 3.20)
project(http_client
    VERSION 1.0.0
    DESCRIPTION "简单的 HTTP 客户端"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# TODO: 待实现后取消注释
# add_executable(http_client main.cpp)
# target_link_libraries(http_client PRIVATE curl)

# 构建 & 运行:
#   cmake -S . -B build && cmake --build build && ./build/http_client
