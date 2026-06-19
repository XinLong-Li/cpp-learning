# 函数模板

## 为什么需要模板？

```cpp
// ❌ 没有模板：为每种类型写一份
int max_int(int a, int b)       { return a > b ? a : b; }
double max_double(double a, double b) { return a > b ? a : b; }
// ...

// ✅ 模板：编译器为你生成
template<typename T>
T max(T a, T b) { return a > b ? a : b; }

max(3, 5);          // 编译器生成 max<int>
max(3.14, 2.72);    // 编译器生成 max<double>
```

---

## 模板参数推导

```cpp
template<typename T>
T twice(T x) { return x + x; }

twice(5);        // T = int
twice(3.14);     // T = double
// twice(5, 3.14);  // ❌ 歧义！T 是 int 还是 double？
```

### C++17 CTAD（类模板参数推导）

```cpp
std::pair p(42, "hello");   // std::pair<int, const char*>
std::vector v = {1, 2, 3};  // std::vector<int>
std::optional o = 42;       // std::optional<int>
```

---

## 显式指定模板参数

```cpp
template<typename To, typename From>
To narrow_cast(From x) { return static_cast<To>(x); }

// From 可以推导，To 必须显式指定
auto x = narrow_cast<int>(3.14159);  // To=int, From=double
```

---

## C++20 缩写函数模板

```cpp
// 传统写法
template<typename T>
T twice(T x) { return x + x; }

// C++20 缩写（auto 参数）
auto twice(auto x) { return x + x; }  // 完全等价！

// 带约束的缩写
auto twice(std::integral auto x) { return x + x; }
```

---

## 模板特化

```cpp
// 通用版本
template<typename T>
const char* type_name() { return "unknown"; }

// 特化版本
template<>
const char* type_name<int>() { return "int"; }

template<>
const char* type_name<double>() { return "double"; }
```

---

## 常见陷阱

1. **模板代码必须放在头文件中**（或 `.hpp`、`.ipp`）
   - 编译器需要看到完整定义才能实例化
   - 不能像普通函数那样声明和定义分离到 `.cpp`

2. **模板错误信息极长**
   - GCC/Clang 现在改善了一些
   - C++20 Concepts 可以大幅改善（见 03_concepts）

3. **模板不能隐式转换参数**
   ```cpp
   template<typename T>
   T max(T a, T b) { return a > b ? a : b; }
   
   max(5, 3.14);  // ❌ 错误：T 该是 int 还是 double？
   max<double>(5, 3.14);  // ✅ 显式指定
   ```
