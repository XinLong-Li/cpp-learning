# `const` 与 `constexpr`

## 核心区别

| | `const` | `constexpr` |
|---|---------|-------------|
| 含义 | "我不会修改这个值" | "这个值在编译期就能确定" |
| 初始化 | 运行期也可以 | 必须在编译期可求值 |
| 用于 | 变量、引用、成员函数、参数 | 变量、函数、`if` 分支 |
| 是 `const` 吗？ | — | ✅ 所有 `constexpr` 变量隐式 `const` |

```cpp
const int r = rand();        // ✅ 运行期初始化，只读
constexpr int c = 42;        // ✅ 编译期常量
constexpr int e = rand();    // ❌ rand() 不是 constexpr 函数
```

---

## `const` 的三种位置（读法）

```cpp
//        ← 从右往左读 →
const int* p1;        // p1 指向 const int（指向的内容不可改）
int const* p2;        // 同上，另一种写法

int* const p3 = &x;   // p3 是 const 指针（指针本身不可改）
const int* const p4 = &x; // 指针和内容都不可改
```

口诀：**const 修饰它左边的东西；如果它在最左边，就修饰右边的东西。**

---

## `const` 成员函数

```cpp
class Person {
    std::string name_;
public:
    const std::string& name() const { return name_; }
    //  ↑ 返回值是 const 引用    ↑ 这个成员函数不修改对象
};
```

- `const` 成员函数**承诺不修改对象状态**
- 只能在 `const` 对象/引用上调用 `const` 成员函数
- **逻辑 const vs 物理 const**：`mutable` 关键字可以打破物理 const

---

## `constexpr` 函数

```cpp
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

// 参数是编译期常量 → 函数在编译期执行
constexpr int f10 = factorial(10);  // 3628800，存在二进制里

// 参数是运行期变量 → 函数在运行期执行（同一份代码）
int x;
std::cin >> x;
int fx = factorial(x);              // 运行期计算
```

---

## `constexpr` vs `#define`

```cpp
// ❌ 坏：宏没有类型、没有作用域、调试信息中不可见
#define MAX_SIZE 1024

// ✅ 好：有类型、有作用域、可调试
constexpr int MAX_SIZE = 1024;
constexpr double PI = 3.14159265358979323846;
```

**永远用 `constexpr` 代替宏定义常量。**

---

## `if constexpr`（C++17，编译期条件）

```cpp
template<typename T>
void print(const T& val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "整数: " << val;        // 对浮点类型，这段代码不会被编译
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "浮点: " << std::fixed << val;
    } else {
        std::cout << "其他: " << val;
    }
}
```

和普通 `if` 的区别：
- `if constexpr` 在**编译期**决定走哪个分支
- 没走到的分支**不会被编译**（所以可以写不合法的代码在其中）

---

## 常见陷阱

1. **const 引用延长临时对象生命周期**
   ```cpp
   const int& r = 42;  // ✅ 临时 int 的生命期延长到 r 的生存期
   int& r2 = 42;       // ❌ 编译错误！非 const 引用不能绑定到临时对象
   ```

2. **const 成员函数中返回非 const 引用/指针会破坏封装**
   ```cpp
   class Foo {
       int* data_;
   public:
       int* get() const { return data_; } // ✅ 指针本身是 const，但指向的数据不是！
   };
   ```

3. **顶层 const vs 底层 const**
   ```cpp
   const int n = 10;     // 顶层 const：n 本身不可改
   const int* p = &n;    // 底层 const：p 指向的内容不可改（p 本身可改）
   ```
