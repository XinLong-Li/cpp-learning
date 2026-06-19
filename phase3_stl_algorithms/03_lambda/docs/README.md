# Lambda 表达式

## Lambda 语法

```cpp
//  [捕获列表] (参数列表) -> 返回类型 { 函数体 }
auto add = [](int a, int b) -> int { return a + b; };
add(3, 4);  // 7

// 返回类型通常可以省略
auto square = [](int x) { return x * x; };
```

---

## 捕获列表

| 捕获方式 | 语法 | 说明 |
|----------|------|------|
| 值捕获 | `[x]` | 拷贝一份 x |
| 引用捕获 | `[&x]` | 引用外部 x |
| 全部值捕获 | `[=]` | 拷贝所有使用到的外部变量 |
| 全部引用捕获 | `[&]` | 引用所有使用到的外部变量 |
| 混合 | `[=, &y]` | 默认值捕获，y 例外用引用 |
| 移动捕获 | `[x = std::move(x)]` | C++14 广义捕获 |
| this 捕获 | `[this]` / `[*this]` | 捕获当前对象 |

```cpp
int threshold = 5;
int multiplier = 2;

// 值捕获 threshold，引用捕获 multiplier
auto f = [threshold, &multiplier](int x) {
    return (x > threshold) ? x * multiplier : 0;
};

threshold = 10;    // f 中的 threshold 不受影响（拷贝）
multiplier = 3;    // f 中的 multiplier 受影响（引用）
```

---

## 什么时候用什么捕获？

| 场景 | 捕获方式 |
|------|---------|
| Lambda 在当前作用域内立即执行 | `[&]` |
| Lambda 会超出当前作用域（如线程、回调） | `[=]` 或具体变量值捕获 |
| 捕获大对象，想要移动 | `[obj = std::move(obj)]` |
| 只读 | 值捕获 `[x]` |
| 需要修改外部变量 | 引用捕获 `[&x]` |
| 成员函数中的 lambda | `[this]` 或 `[*this]`（C++17） |

---

## 泛型 Lambda（C++14）

```cpp
// 参数类型用 auto
auto twice = [](auto x) { return x + x; };

twice(5);       // 10
twice(3.14);    // 6.28
twice(std::string("ha"));  // "haha"
```

C++20 更进一步：模板 lambda（可以加约束）：
```cpp
auto add = []<typename T>(T a, T b) requires std::is_arithmetic_v<T> {
    return a + b;
};
```

---

## `mutable` Lambda

默认情况下，lambda 的 `operator()` 是 const 的，值捕获的变量不能修改：

```cpp
int counter = 0;
// auto inc = [counter]() { return ++counter; };  // ❌ 编译错误：counter 是 const

auto inc = [counter]() mutable { return ++counter; };  // ✅ OK
std::cout << inc() << '\n';  // 1
std::cout << inc() << '\n';  // 2
std::cout << counter << '\n'; // 0（外部 counter 未被修改）
```

---

## Lambda 与 `std::function`

```cpp
#include <functional>

// std::function 有运行时开销（类型擦除）
std::function<int(int, int)> f1 = [](int a, int b) { return a + b; };

// auto（Lambda 自己的类型）零开销
auto f2 = [](int a, int b) { return a + b; };

// 何时用 std::function？
// 1. 需要存储不同类型的可调用对象
// 2. 递归 lambda（但也能用 auto + Y-combinator 避免）
```
