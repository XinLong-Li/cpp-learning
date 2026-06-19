# C++ Learning 🚀

我的 C++ 学习之旅，从 C++20 开始。

## 环境

- **编译器**: Apple Clang 17 (arm64)
- **构建系统**: CMake 3.30
- **标准**: C++20
- **IDE**: VS Code

## 快速开始

```bash
# 配置 & 构建
cmake -S . -B build
cmake --build build

# 运行
./build/bin/hello
```

## 目录结构

```
cpp-learning/
├── src/          # 源代码
├── include/      # 头文件
├── build/        # 构建输出
├── .vscode/      # VS Code 配置
└── CMakeLists.txt
```

## VS Code 快捷键

| 操作 | 快捷键 |
|------|--------|
| 构建所有 | `Cmd+Shift+B` |
| 调试当前文件 | `F5` |
| 运行 | 终端执行 `./build/bin/<文件名>` |
