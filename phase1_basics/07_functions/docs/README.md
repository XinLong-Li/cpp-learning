# 函数最佳实践

## 参数传递速查表

| 意图 | 写法 | 说明 |
|------|------|------|
| 只读，小对象 | `T x` | int, double, enum 等 |
| 只读，大对象 | `const T& x` | string, vector 等 |
| 修改参数 | `T& x` | 输出参数 |
| 移动/接管 | `T x`（调用方 `std::move`） | 接收所有权 |
| 完美转发 | `T&& x`（模板） | 转发到其他函数 |

---

## RVO / NRVO（返回值优化）

**C++17 强制要求在某些场景下消除拷贝。放心 return 大对象！**

```cpp
std::vector<int> make_large_vector() {
    std::vector<int> v(10000);
    for (int i = 0; i < 10000; ++i) v[i] = i;
    return v;  // ✅ RVO：零拷贝！v 直接在调用方的内存位置构造
}

// 调用方
auto v = make_large_vector();  // 没有任何拷贝发生
```

**你不需要写 `std::move` 在 return 语句上**——这会**禁用** RVO！

```cpp
std::string bad_return() {
    std::string s = "hello";
    return std::move(s);  // ❌ 破坏了 RVO！强制拷贝
}

std::string good_return() {
    std::string s = "hello";
    return s;             // ✅ RVO：零拷贝
}
```

---

## 函数重载

```cpp
void process(int x);
void process(double x);
void process(const std::string& s);

// 重载决议规则大致按：
// 1. 精确匹配 > 提升 > 转换 > 用户定义转换
// 2. 非模板 > 模板
// 3. 参数少的 > 参数多的
```

### 重载的坑

```cpp
void f(int x);
void f(const int& x);  // 编译器可能无法区分（平台相关）
```

---

## 默认参数

```cpp
void log(const std::string& msg, int severity = 0, bool to_file = false);
log("error");            // severity=0, to_file=false
log("warning", 1);       // severity=1, to_file=false
log("info", 0, true);    // 全部指定
```

### 默认参数 vs 重载

```cpp
// 默认参数 —— 简单场景
void print(const std::string& s, int indent = 0);

// 重载 —— 参数有不同的类型/数量/语义
void print(const std::string& s);
void print(const std::string& s, std::ostream& os);
void print(int n, const std::string& label);
```

---

## 函数对象 vs Lambda

```cpp
// 函数指针（C 风格）
using Predicate = bool(*)(int);

// std::function —— 类型擦除（有运行时开销）
std::function<bool(int)> pred = [](int x) { return x > 0; };

// Lambda —— 零开销
auto pred = [](int x) { return x > 0; };

// 模板 —— 最高效（编译时多态）
template<typename F>
void apply(F&& f) { f(); }
```

**优先使用 Lambda 或模板，避免 `std::function` 除非需要存储不同类型的可调用对象。**

---

## `[[nodiscard]]` 属性（C++17）

标记返回值不应该被丢弃：

```cpp
[[nodiscard]] int compute();  // 调用方必须用返回值
compute();                    // ⚠️ 编译器警告

[[nodiscard("check error code")]] bool try_parse();  // C++20 带消息
```

---

## 常见陷阱

1. **忘记 `const&` 导致意外拷贝**
   ```cpp
   void print(std::string s);  // 每次都拷贝！
   void print(const std::string& s);  // 零拷贝
   ```

2. **return 时写 `std::move` 破坏 RVO**
3. **重载决议歧义导致编译错误**
4. **默认参数在声明和定义中重复**
   ```cpp
   // header.h
   void f(int x = 10);
   // source.cpp
   void f(int x = 10) { ... }  // ❌ 重复默认参数
   ```
