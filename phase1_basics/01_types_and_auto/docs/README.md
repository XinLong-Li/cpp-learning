# 类型推导与 `auto`

## 为什么需要类型推导？

C++ 的类型名可能非常长：

```cpp
std::vector<std::pair<std::string, int>>::const_iterator it = m.begin();
```

用 `auto` 后：

```cpp
auto it = m.begin(); // 编译器自动推导类型
```

**`auto` 是现代 C++ 的第一习惯。** 它让代码更简洁、更易重构。

---

## `auto` 的推导规则

`auto` 的行为类似于模板参数推导，但有几个坑要注意：

### 1. `auto` 会剥除引用和 const（顶层）

```cpp
const int& foo();
auto x = foo();   // x 是 int（const 和 & 都被剥掉了）
auto& y = foo();  // y 是 const int&（显式加上 & 保留引用）
```

### 2. 想要什么就写清楚

| 想得到 | 写法 |
|--------|------|
| 值拷贝 | `auto x = expr;` |
| 引用（可修改） | `auto& x = expr;` |
| 常量引用 | `const auto& x = expr;` |
| 万能引用/转发引用 | `auto&& x = expr;` |
| 指针 | `auto* x = expr;` 或 `auto x = expr;`（对指针无区别） |

### 3. `decltype(auto)` —— 完美转发类型

```cpp
const int& foo();
decltype(auto) x = foo(); // x 是 const int&，不做任何剥除
```

---

## 什么时候应该用 `auto`？

### ✅ 应该用

- 迭代器：`auto it = v.begin();`
- Lambda：`auto f = [](int x) { return x * 2; };`
- 模板/泛型代码中类型不明确时
- Range-based for：`for (const auto& item : container)`
- 结构化绑定：`auto [key, value] = pair;`

### ❌ 不应该用

- 当类型名本身就是文档，用 `auto` 会降低可读性时
- 类型推导结果和预期不一致时（比如上面的剥 const 问题）

---

## 关键类型一览

| 类型 | 大小 (64位) | 范围 | 用途 |
|------|------------|------|------|
| `int` | 4 字节 | ±2.1×10⁹ | 默认整数 |
| `double` | 8 字节 | ±1.7×10³⁰⁸ | 默认浮点 |
| `bool` | 1 字节 | true/false | 布尔值 |
| `size_t` | 8 字节 | 0 ~ 1.8×10¹⁹ | 容器大小/索引 |
| `char` | 1 字节 | -128~127 | 单个字符 |
| `std::string` | 32 字节 | 动态 | 字符串（默认选择） |
| `std::string_view` | 16 字节 | 只读视图 | 不拥有所有权的字符串引用 |

---

## 常见陷阱

1. **`auto` 推导出 `initializer_list`**
   ```cpp
   auto x = {1, 2, 3}; // x 的类型是 std::initializer_list<int>，不是 vector！
   auto y = {1};       // 也是 initializer_list
   ```

2. **`auto` 推导会剥除引用和顶层 const**
   ```cpp
   const int ci = 42;
   auto a = ci;  // a 是 int，不是 const int
   const auto b = ci; // b 是 const int
   ```

3. **在 range-based for 中忘了加引用**
   ```cpp
   for (auto item : vec)      // 拷贝每个元素 —— 昂贵！
   for (const auto& item : vec) // 只读引用 —— 正确做法
   for (auto& item : vec)       // 可修改引用
   ```

---

## 下一步

➡️ 阅读 [`demo.cpp`](./demo.cpp) 看完整示例  
✏️ 完成 [`exercise.cpp`](./exercise.cpp) 的练习
