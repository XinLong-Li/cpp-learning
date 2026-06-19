cmake_minimum_required(VERSION 3.20)
project(cpp-learning VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 启用测试
enable_testing()

# 添加 src 子目录下的所有源文件
file(GLOB_RECURSE SOURCES src/*.cpp)

# 为每个源文件单独生成可执行文件（便于学习时一个个运行）
foreach(src ${SOURCES})
    get_filename_component(exec_name ${src} NAME_WE)
    add_executable(${exec_name} ${src})
    target_include_directories(${exec_name} PRIVATE include)
    set_target_properties(${exec_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()
