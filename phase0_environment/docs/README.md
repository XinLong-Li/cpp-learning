# 阶段 0：环境搭建

## 目标

能编译、运行、调试一个 C++ 程序。

---

## 1. 编译器选择

| 编译器 | macOS 安装 | Linux 安装 | 说明 |
|--------|-----------|-----------|------|
| **GCC 13+** | `brew install gcc@13` | `sudo apt install g++-13` | C++20 支持完善 |
| **Clang 16+** | Xcode CLT 自带 | `sudo apt install clang-16` | 错误信息更友好 |

验证安装：
```bash
g++-13 --version   # 或 g++ --version
clang++ --version
```

---

## 2. CMake 构建系统

CMake 是 C++ 工业界的标准构建工具。**从第一个程序开始就用它。**

### 最小 CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(hello-world)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(hello main.cpp)
```

### 编译流程

```bash
# 在项目根目录下
mkdir build && cd build
cmake ..
make          # 或 cmake --build .
./hello       # 运行
```

### 为什么用 CMake？

- **跨平台**：同一份 CMakeLists.txt 在 macOS/Linux/Windows 都能用
- **工业标准**：几乎所有 C++ 开源项目都用 CMake
- **IDE 支持**：VS Code、CLion、Qt Creator 都能直接打开 CMake 项目

---

## 3. VS Code 配置

### 必装插件
1. **clangd**（C/C++ 语言服务器）—— 代码补全、跳转、诊断
2. **CMake Tools** —— 一键配置/编译

### clangd vs Microsoft C/C++ 插件

**推荐 clangd**：
- 更快、更准确
- 自动读取 `compile_commands.json`（CMake 生成）
- 禁用 Microsoft C/C++ 插件的 IntelliSense 避免冲突

在 `.vscode/settings.json` 中：
```json
{
    "clangd.arguments": [
        "--compile-commands-dir=${workspaceFolder}/build",
        "--header-insertion=never"
    ],
    "C_Cpp.intelliSenseEngine": "disabled"
}
```

生成 `compile_commands.json`：
```bash
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
# 或在 VS Code 中：CMake: Configure
```

---

## 4. 编译器警告与消毒器

### 编译选项解释

| 标志 | 含义 |
|------|------|
| `-Wall` | 启用大多数常见警告 |
| `-Wextra` | 额外警告（比 `-Wall` 更多） |
| `-Wpedantic` | 严格遵循 C++ 标准 |
| `-Werror` | 警告视为错误（学习时推荐开启） |
| `-fsanitize=address` | 内存错误检测（越界、泄漏、use-after-free） |
| `-fsanitize=undefined` | 未定义行为检测（整数溢出、空指针解引用等） |

### 为什么学习阶段就要用？

- **Sanitizer** 能在运行时精确告诉你哪一行出了内存问题
- 越早养成习惯，越少写 bug
- 性能损失约 2x，学习代码完全可接受

---

## 5. 代码格式化

### clang-format

在项目根目录创建 `.clang-format`：
```bash
clang-format -style=Google -dump-config > .clang-format
```

VS Code 中设置保存时自动格式化：
```json
{
    "editor.formatOnSave": true,
    "[cpp]": {
        "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd"
    }
}
```

---

## 6. 验证一切正常

创建 `main.cpp`：
```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> messages = {"Hello", "C++", "World!"};

    for (const auto& msg : messages) {
        std::cout << msg << " ";
    }
    std::cout << "\nC++ Standard: " << __cplusplus << '\n';
    return 0;
}
```

编译运行：
```bash
mkdir build && cd build
cmake .. && cmake --build .
./hello
```

如果看到输出和 `__cplusplus` 的值（C++20 应输出 `202002L`），环境就准备好了。

---

## 参考链接

- [CMake 官方教程](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- [clangd 安装指南](https://clangd.llvm.org/installation.html)
- [Compiler Explorer (在线看编译结果)](https://godbolt.org/)
