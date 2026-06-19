# C++ Learning 🚀

我的 C++ 学习之旅，以 **C++17 为核心，C++20 新特性为补充**。

## 环境

- **编译器**: Apple Clang 17 (arm64) / GCC 13+
- **构建系统**: CMake 3.20+
- **标准**: C++20 (`-std=c++20`)
- **IDE**: VS Code + clangd

## 快速开始

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# 运行某个阶段的 demo（以阶段 1 类型推导为例）
./build/bin/phase1_types_demo
```

## 目录结构

```
cpp-learning/
├── phase0_environment/         # 环境搭建文档
├── phase1_basics/              # 基础语法（8 个主题）
│   ├── 01_types_and_auto/      #   ├─ docs/README.md  + demo.cpp + exercise.cpp
│   ├── 02_const_and_constexpr/ #   ├─ docs/README.md  + demo.cpp + exercise.cpp
│   ├── ...                     #   └─ ...
│   └── CMakeLists.txt
├── phase2_classes_raii/        # 类与 RAII（4 个主题）
├── phase3_stl_algorithms/      # STL 算法（4 个主题）
├── phase4_templates/           # 模板与编译期编程（5 个主题）
├── phase5_cpp17_library/       # C++17 核心库（5 个主题）
├── phase6_error_handling/      # 错误处理与调试（2 个主题）
├── phase7_projects/            # 实战项目（4 个）
├── include/                    # 公共头文件
├── LEARNING_PLAN.md            # 完整学习路线图
└── CMakeLists.txt              # 顶层构建文件
```

## 每个主题包含

| 文件 | 内容 |
|------|------|
| `docs/README.md` | 概念解释、关键知识点、常见陷阱 |
| `demo.cpp` | 可运行的示例代码，展示概念用法 |
| `exercise.cpp` | 练习题（骨架代码 + TODO 注释） |

## 学习顺序

按阶段编号 **0 → 1 → 2 → 3 → 4 → 5 → 6 → 7** 依次学习。

每个阶段内部可以从前往后学，也可以按需跳转。

## VS Code 快捷键

| 操作 | 快捷键 |
|------|--------|
| 构建所有 | `Cmd+Shift+B` |
| 调试当前文件 | `F5` |
| 运行 | 终端执行 `./build/bin/<target>` |
