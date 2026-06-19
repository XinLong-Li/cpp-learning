# C++ 学习路线图：从零到工业级核心能力

> **编译器标准：`-std=c++20` | 编译器：GCC 12+ / Clang 16+**
> 以 C++17 为核心，C++20 关键特性为补充。学完一个阶段再做阶段内的练习，不要跳。

---

## 阶段 0：环境搭建（第一天搞定）

**目标：** 能编译、运行、调试一个 C++ 程序。

### 工具链
| 平台 | 编译器 | IDE / 编辑器 |
|------|--------|-------------|
| macOS | `brew install gcc@13` 或 Xcode CLT (Clang) | VS Code + clangd 插件 |
| Linux | `sudo apt install g++-13` | VS Code + clangd 或 CLion |
| Windows | WSL2 (Ubuntu) + g++-13 | VS Code (Remote-WSL) |

### 构建工具
- **CMake** —— 工业标准，第一天就学。
  ```cmake
  # CMakeLists.txt 最小模板
  cmake_minimum_required(VERSION 3.16)
  project(learning-cpp)
  set(CMAKE_CXX_STANDARD 20)
  add_executable(main main.cpp)
  ```

### 验证
```cpp
// main.cpp
#include <iostream>
int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}
```
```bash
mkdir build && cd build && cmake .. && make && ./main
```

---

## 阶段 1：基础语法（1-2 周）

**核心原则：** 这一阶段不要碰指针、不要手动 new/delete。用栈上对象和 STL 容器。

### 1.1 类型系统
- **基本类型**：`int`, `double`, `char`, `bool`, `size_t`
- **`auto`** —— 类型推导，现代 C++ 第一习惯
- **`const`** 和 `constexpr` —— 编译期 vs 运行期常量
- **引用 `&`** —— C++ 的"别名"，不是指针
- **`std::string`** 和 **`std::string_view`**（C++17）—— 告别 C 风格字符串
- **`std::optional<T>`**（C++17）—— 表达"可能没有值"

### 1.2 控制流
- `if constexpr`（C++17）—— 编译期分支
- range-based `for` —— `for (const auto& x : vec)`
- `switch` 带初始化语句（C++17）

### 1.3 函数
- 值传递 vs 引用传递 vs `const` 引用
- 返回值优化（RVO/NRVO）—— 放心 return 大对象
- 函数重载
- 默认参数

### 1.4 第一个 STL 容器
- `std::vector<T>` —— 默认容器，90% 的场景用它
- `std::array<T, N>` —— 定长数组
- `std::unordered_map<K, V>` 和 `std::map<K, V>`

### 🧪 阶段 1 练习
1. 写一个函数，接收 `std::string_view`，统计其中每个单词的出现次数，返回 `std::unordered_map<std::string, int>`
2. 用 `std::optional` 实现一个安全的除法函数
3. 用 `if constexpr` 写一个根据类型输出不同信息的函数

---

## 阶段 2：类与 RAII（1-2 周）

**这是 C++ 最重要的设计哲学 —— RAII（资源获取即初始化）。**

### 2.1 类基础
- 构造函数 / 析构函数
- 成员初始化列表
- `= default` / `= delete`（C++11）
- `explicit` 构造函数

### 2.2 RAII 思想
> **资源在构造函数中获取，在析构函数中释放。永不手动管理。**
- 文件句柄、锁、内存、socket —— 全部交给类管理
- 为什么不需要 `finally` 块

### 2.3 智能指针（告别 `new`/`delete`）
| 智能指针 | 用途 |
|----------|------|
| `std::unique_ptr<T>` | 独占所有权，移动语义 |
| `std::shared_ptr<T>` | 共享所有权，引用计数 |
| `std::weak_ptr<T>` | 打破循环引用 |

**你永远不需要写 `delete`。**

### 2.4 移动语义
- 左值 vs 右值
- 移动构造函数 / 移动赋值运算符
- `std::move` 的实际含义（它不移动任何东西）
- Rule of Five / Rule of Zero

### 🧪 阶段 2 练习
1. 写一个 `FileHandle` 类，RAII 管理文件，自动关闭
2. 写一个 `CircularBuffer<T>` 类模板，支持 push/pop
3. 阅读你写的代码，确认没有一行 `new` 或 `delete`

---

## 阶段 3：STL 算法与迭代器（1-2 周）

**写循环是 C++98 的做法。现代 C++ 用算法。**

### 3.1 迭代器
- `begin()` / `end()`
- 迭代器类别：Input, Forward, Bidirectional, RandomAccess
- 理解迭代器失效的场景

### 3.2 核心算法（按使用频率排序）
| 算法 | 用途 |
|------|------|
| `std::sort` | 排序 |
| `std::find` / `std::find_if` | 查找 |
| `std::copy` / `std::copy_if` | 复制 |
| `std::transform` | 映射转换 |
| `std::accumulate` | 归约（`<numeric>`） |
| `std::remove_if` + erase | 删除元素（Erase-Remove Idiom） |
| `std::any_of` / `all_of` / `none_of` | 条件判断 |
| `std::count` / `std::count_if` | 计数 |
| `std::partition` | 分区 |
| `std::lower_bound` / `std::upper_bound` | 二分查找 |

### 3.3 Lambda 表达式
```cpp
auto it = std::find_if(v.begin(), v.end(),
    [threshold](const auto& x) { return x > threshold; });
```
- 捕获列表：`[=]`, `[&]`, `[this]`, 具名捕获
- 泛型 lambda（C++20 可直接用 `auto`）

### 3.4 C++20 Ranges（了解）
```cpp
// 传统
std::vector<int> result;
std::copy_if(v.begin(), v.end(), std::back_inserter(result),
    [](int x) { return x > 0; });

// C++20 Ranges
auto result = v | std::views::filter([](int x) { return x > 0; })
                | std::ranges::to<std::vector>();
```

### 🧪 阶段 3 练习
1. 不写任何 `for`/`while` 循环，用 STL 算法实现：
   - 过滤一个 vector 中的偶数
   - 将所有正数乘以 2
   - 判断一个 vector 是否所有元素都 > 0
2. 实现一个 trim 函数，去除字符串首尾空格（用 `find_if` + `string_view`）
3. 对一个 `vector<Person>` 按年龄排序，年龄相同按姓名排序

---

## 阶段 4：编译期编程（1 周）

### 4.1 模板基础
- 函数模板：`template<typename T> T max(T a, T b)`
- 类模板：`template<typename T> class Stack { ... }`
- 模板特化与偏特化

### 4.2 C++20 Concepts（学习重点）
```cpp
// 不用 Concepts（旧式 SFINAE，错误信息地狱）
template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
T add(T a, T b) { return a + b; }

// 用 Concepts（清晰、友好）
template<std::integral T>
T add(T a, T b) { return a + b; }
```

### 4.3 编译期计算
- `constexpr` 函数
- `constexpr` 容器（C++20）
- `static_assert` —— 编译期断言
- 折叠表达式（C++17）：
  ```cpp
  template<typename... Args>
  auto sum(Args... args) { return (args + ...); }
  ```

### 🧪 阶段 4 练习
1. 用 Concepts 约束一个 `print` 函数，要求参数必须支持 `<<` 运算符
2. 用折叠表达式实现一个 `print_all` 函数
3. 写一个 `constexpr` 的阶乘 / 斐波那契函数
4. 用 `static_assert` 验证你的类型约束

---

## 阶段 5：C++17 核心库特性（1 周）

### 5.1 词汇类型（Vocabulary Types）
| 类型 | 头文件 | 用途 |
|------|--------|------|
| `std::optional<T>` | `<optional>` | 可能不存在的值 |
| `std::variant<Ts...>` | `<variant>` | 类型安全的 union |
| `std::any` | `<any>` | 类型擦除的"任意值" |
| `std::string_view` | `<string_view>` | 不拥有所有权的字符串视图 |

### 5.2 结构化绑定（Structured Bindings）
```cpp
std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
for (const auto& [key, value] : m) {  // C++17
    std::cout << key << ": " << value << '\n';
}

auto [it, inserted] = m.insert({"c", 3});  // 解包 pair
```

### 5.3 `std::filesystem`
- 遍历目录、创建/删除文件、路径操作
- 替代 `opendir`/`readdir` 等 POSIX 调用

### 5.4 并行算法（C++17）
```cpp
std::sort(std::execution::par, v.begin(), v.end());  // 并行排序
```

### 🧪 阶段 5 练习
1. 用 `std::variant` 实现一个可以存储 `int`、`double`、`std::string` 的安全容器
2. 用 `std::filesystem` 写一个递归列出目录所有 `.cpp` 文件的程序
3. 用结构化绑定重构之前的所有 `for` 循环

---

## 阶段 6：错误处理与调试（3 天）

### 6.1 异常安全（Exception Safety）
- 基本保证 / 强保证 / 不抛出保证
- RAII 是实现异常安全的核心机制
- 析构函数绝不抛异常

### 6.2 现代替代方案
- `std::expected<T, E>`（C++23，但可用第三方实现）
- `std::optional` 作为无错误信息的替代
- 错误码 + `std::optional` 组合

### 6.3 工具
- AddressSanitizer（`-fsanitize=address`）—— 内存错误检测
- UndefinedBehaviorSanitizer（`-fsanitize=undefined`）
- `gdb` / `lldb` 基本操作
- `assert` 和 `static_assert`

### 🧪 阶段 6 练习
1. 用 ASan 编译运行之前的代码，确保无内存错误
2. 写一个 RAII 类，验证异常抛出时资源被正确释放

---

## 阶段 7：实战项目（2-4 周）

按难度递增，每个项目应该覆盖多个阶段的知识点。

### 项目 1：命令行 TODO 工具
**涉及：** 文件 IO, `std::filesystem`, `std::vector`, 算法, 结构化绑定
- 支持 `add`、`list`、`done`、`remove` 命令
- 数据持久化到 JSON（用 [nlohmann/json](https://github.com/nlohmann/json)）
- 按优先级排序、按标签过滤

### 项目 2：简单的线程池
**涉及：** `std::thread`, `std::mutex`, `std::condition_variable`, `std::future`, `std::packaged_task`
- 固定数量工作线程
- 任务队列
- RAII 管理线程生命周期

### 项目 3：CSV 解析器
**涉及：** 模板, `std::string_view`, 算法, `std::variant`
- 模板化支持任意列类型
- 零拷贝解析（用 `string_view`）
- 支持过滤、排序、聚合操作（类似 SQL 的 SELECT WHERE ORDER BY）

### 项目 4：简单的 HTTP 客户端
**涉及：** 网络编程, RAII, `std::optional`, 错误处理
- 发送 GET/POST 请求
- 解析 HTTP 响应
- 超时处理

---

## 贯穿始终的好习惯

### ✅ 要做的
| 习惯 | 说明 |
|------|------|
| `-Wall -Wextra -Wpedantic` | 严格警告，视为错误：`-Werror` |
| `-fsanitize=address,undefined` | 开发阶段始终开启消毒器 |
| 用 `clang-format` | 自动格式化，不纠结风格 |
| 用 `clang-tidy` | 静态分析，捕获常见错误 |
| 读 cppreference.com | 标准库的最佳文档 |
| 用 CMake | 从 hello world 就用 |

### ❌ 不要做的
| 坏习惯 | 为什么 |
|--------|--------|
| `using namespace std;` | 命名污染，尤其头文件中 |
| 裸 `new` / `delete` | 用智能指针和容器 |
| C 风格字符串 `char*` | 用 `std::string` / `std::string_view` |
| C 风格数组 `int arr[10]` | 用 `std::array` / `std::vector` |
| C 风格转换 `(int)x` | 用 `static_cast<int>(x)` |
| 宏定义常量 `#define MAX 100` | 用 `constexpr int MAX = 100;` |
| 拥有原始指针 `T*` 表示所有权 | 用 `unique_ptr` / `shared_ptr` |

---

## 参考资源

| 资源 | 用途 |
|------|------|
| [cppreference.com](https://en.cppreference.com/) | STL / 语言参考，日常查询 |
| [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) | 最佳实践 |
| [Compiler Explorer](https://godbolt.org/) | 在线看编译结果 |
| *A Tour of C++* (Bjarne Stroustrup) | 快速概览，200 页 |
| *Effective Modern C++* (Scott Meyers) | C++11/14 深度，仍然值得读 |
| *C++17 - The Complete Guide* (Nicolai Josuttis) | C++17 特性详解 |

---

## 时间估算（总计 6-10 周）

```
阶段 0: 环境搭建    ██          ~1 天
阶段 1: 基础语法    ████████    ~2 周
阶段 2: 类与 RAII    ████████    ~2 周
阶段 3: STL 算法     ████████    ~2 周
阶段 4: 模板/Concepts ████      ~1 周
阶段 5: C++17 库     ████       ~1 周
阶段 6: 错误处理     ███         ~3 天
阶段 7: 实战项目     ████████████ ~2-4 周
```

**每个阶段学完后再进入下一个，不要跳过练习。** 重点是阶段 2（RAII）和阶段 3（STL 算法），这是 C++ 区别于其他语言的核心竞争力。
