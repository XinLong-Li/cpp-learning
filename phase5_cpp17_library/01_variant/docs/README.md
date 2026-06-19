# `std::variant<Ts...>`：类型安全的联合体

## `variant` vs `union`

```cpp
// ❌ union：你不知道当前存的是什么类型
union BadUnion {
    int i;
    double d;
    std::string s;  // C++ 中 union 用非平凡类型很麻烦
};

// ✅ variant：类型安全，知道存的是什么
std::variant<int, double, std::string> v;
v = 42;
v = "hello";       // 合法，替换了 int
int* p = std::get_if<int>(&v);  // p == nullptr，因为现在是 string
```

---

## 基本用法

```cpp
std::variant<int, double, std::string> val;

val = 42;                          // 存 int
int i = std::get<int>(val);        // 获取 int（类型不匹配抛异常）
int* pi = std::get_if<int>(&val);  // 获取指针（不抛异常，nullptr 代替）

val = 3.14;                        // 现在存 double
val = std::string("hello");        // 现在存 string
```

---

## `std::visit` —— 最常用的访问方式

```cpp
std::variant<int, double, std::string> val = 42;

// visit 会根据当前存储的类型调用对应的 lambda
std::visit([](auto&& arg) {
    std::cout << arg << '\n';
}, val);

// 不同类型不同处理
std::visit([](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "int: " << arg * 2 << '\n';
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "string: \"" << arg << "\"\n";
    } else {
        std::cout << "other: " << arg << '\n';
    }
}, val);
```

---

## `variant` 的开销

- 大小 = 最大成员的大小 + 一个 `size_t`（索引） + 对齐
- 无堆分配
- `std::visit` 通常用虚表实现，有轻度开销

---

## 典型场景

```cpp
// 1. 错误处理：返回结果或错误
std::variant<Result, ErrorCode> process();

// 2. 状态机
using State = std::variant<Idle, Running, Paused, Stopped>;

// 3. JSON 值
using JsonValue = std::variant<
    std::nullptr_t,
    bool, int, double, std::string,
    std::vector<JsonValue>,
    std::map<std::string, JsonValue>
>;
```
