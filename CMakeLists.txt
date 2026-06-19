cmake_minimum_required(VERSION 3.20)
project(cpp-learning
    VERSION 1.0.0
    DESCRIPTION "C++ 学习项目：从基础到工业级核心能力"
    LANGUAGES CXX
)

# ── C++ Standard ──────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Output Directories ────────────────────────────────────
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ── Compiler Warnings ─────────────────────────────────────
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ── Sanitizers (Debug mode) ───────────────────────────────
if(CMAKE_BUILD_TYPE MATCHES "Debug" OR NOT CMAKE_BUILD_TYPE)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

# ── Include ───────────────────────────────────────────────
include_directories(${CMAKE_SOURCE_DIR}/include)

# ── Phases ────────────────────────────────────────────────
add_subdirectory(phase1_basics)
add_subdirectory(phase2_classes_raii)
add_subdirectory(phase3_stl_algorithms)
add_subdirectory(phase4_templates)
add_subdirectory(phase5_cpp17_library)
add_subdirectory(phase6_error_handling)
# phase7_projects 的每个项目独立构建，不自动加入
