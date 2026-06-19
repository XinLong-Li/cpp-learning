# C++20 Concepts：约束模板

## 模板的老问题

```cpp
template<typename T>
T add(T a, T b) { return a + b; }

add(1, 2);           // ✅ OK
add("hello", 3.14);  // ❌ 编译错误：不能加 const char* 和 double
                     // 但错误信息有 300 行，淹没在模板实例化栈里
```

## Concepts 解决什么？

**让模板错误信息变得可读，并在调用点就报错。**

---

## 基本用法

```cpp
#include <concepts>

// 约束：T 必须是整数类型
template<std::integral T>
T add(T a, T b) { return a + b; }

add(1, 2);           // ✅ OK
add(1.5, 2.5);       // ❌ 错误信息：double 不满足 integral 约束
```

---

## 预定义 Concepts

| Concept | 含义 |
|---------|------|
| `std::integral<T>` | 整数类型 |
| `std::floating_point<T>` | 浮点类型 |
| `std::signed_integral<T>` | 有符号整数 |
| `std::unsigned_integral<T>` | 无符号整数 |
| `std::same_as<T, U>` | T 和 U 是同一类型 |
| `std::derived_from<T, Base>` | T 继承自 Base |
| `std::convertible_to<From, To>` | From 可转换为 To |
| `std::movable<T>` | 可移动构造和移动赋值 |
| `std::copyable<T>` | 可拷贝 |
| `std::swappable<T>` | 可交换 |
| `std::invocable<F, Args...>` | F 可用 Args... 调用 |

---

## 自定义 Concept

```cpp
// 定义一个 Concept：可哈希
template<typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

// 使用
template<Hashable T>
void use_in_unordered_set(T value) { ... }
```

### `requires` 表达式的四种检查

```cpp
template<typename T>
concept Container = requires(T c) {
    typename T::value_type;          // 1. 必须有嵌套类型 value_type
    c.begin();                       // 2. 必须有 begin() 方法
    c.end();                         // 3. 必须有 end() 方法
    { c.size() } -> std::integral;   // 4. size() 返回整数类型
};
```

---

## 三种 Concepts 语法

```cpp
// 1. requires 子句
template<typename T>
    requires std::integral<T>
T add1(T a, T b) { return a + b; }

// 2. 直接放 typename 位置
template<std::integral T>
T add2(T a, T b) { return a + b; }

// 3. 缩写模板 + Concept
auto add3(std::integral auto a, std::integral auto b) { return a + b; }
```

三种写法等价，选可读性最好的。

---

## `requires` 也可以做条件

```cpp
template<typename T>
void process(const T& val) {
    if constexpr (requires { val.to_string(); }) {
        std::cout << val.to_string();   // 有 to_string() 时调用
    } else {
        std::cout << val;               // 否则用 <<
    }
}
```
