# 折叠表达式（Fold Expressions，C++17）

## 变参模板的老写法

```cpp
// ❌ C++11 递归展开（繁琐、编译慢）
template<typename T>
T sum(T v) { return v; }

template<typename T, typename... Args>
T sum(T first, Args... rest) {
    return first + sum(rest...);  // 递归实例化，每个参数一层
}
```

## C++17 折叠表达式

```cpp
// ✅ 一行搞定
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // 折叠表达式！
}

sum(1, 2, 3, 4, 5);  // (1 + 2) + 3 + 4 + 5 = 15
```

---

## 四种折叠方式

| 语法 | 展开结果 |
|------|---------|
| `(pack op ...)` | `(a₁ op (a₂ op ... op (aₙ₋₁ op aₙ)))` |
| `(... op pack)` | `((((a₁ op a₂) op a₃) ...) op aₙ)` |
| `(pack op ... op init)` | `(a₁ op (a₂ op ... op (aₙ op init)))` |
| `(init op ... op pack)` | `((((init op a₁) op a₂) ...) op aₙ)` |

---

## 实际例子

```cpp
// 打印所有参数
template<typename... Args>
void print(Args&&... args) {
    ((std::cout << args << ' '), ...);  // 逗号折叠
}

// 全部为 true？
template<typename... Args>
bool all(Args... args) {
    return (... && args);  // 左折叠 &&，全 true 才 true
}

// 任意一个为 true？
template<typename... Args>
bool any(Args... args) {
    return (... || args);  // 左折叠 ||
}

// push_back 多个参数
template<typename Container, typename... Args>
void push_all(Container& c, Args&&... args) {
    (c.push_back(std::forward<Args>(args)), ...);
}
```

---

## 逗号折叠的经典用法

逗号折叠 `(expr, ...)` 对每个参数执行 expr，丢弃结果：

```cpp
// 调用每个参数上的某个函数
template<typename... Ts>
void call_all(Ts&&... args) {
    (args.process(), ...);  // 调用每个 args 的 process()
}

// 检查多个条件，抛出第一个失败
template<typename... Conditions>
void check_all(Conditions... conditions) {
    ((conditions.ok() ? void() : throw std::runtime_error(conditions.msg())), ...);
}
```
