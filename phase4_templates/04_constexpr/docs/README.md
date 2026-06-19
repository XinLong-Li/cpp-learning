# `constexpr`：编译期计算

## 为什么需要编译期计算？

- **性能**：值直接嵌入二进制，零运行时开销
- **安全**：编译期就能发现错误（`static_assert`）
- **减少魔法数字**：用 `constexpr` 函数替代宏

---

## `constexpr` 函数（C++14+）

C++14 起，`constexpr` 函数可以包含循环和多个 return：

```cpp
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

constexpr int f10 = factorial(10);  // 编译期求值
int x;
std::cin >> x;
int fx = factorial(x);               // 运行期求值（同一份代码！）
```

---

## `constexpr` 容器（C++20）

```cpp
constexpr int sum_of_first_n(int n) {
    std::vector<int> v(n);   // C++20: vector 可以在编译期使用！
    std::iota(v.begin(), v.end(), 1);
    return std::accumulate(v.begin(), v.end(), 0);
}

constexpr int s100 = sum_of_first_n(100);  // 5050，编译期求值
```

但注意：`constexpr` 中分配的内存**必须在编译期释放**，不能把 `constexpr vector` 传递到运行期。

---

## `consteval`（C++20）—— 强制编译期

```cpp
consteval int compile_only(int n) {
    return n * n;
}

constexpr int x = compile_only(10);  // ✅ OK
int y;
std::cin >> y;
// int z = compile_only(y);          // ❌ 编译错误！y 不是常量
```

---

## `constinit`（C++20）—— 强制编译期初始化

```cpp
constinit int global = 42;  // 必须在编译期初始化
// constinit int bad = rand();  // ❌ rand() 不是 constexpr
```

与 `constexpr` 的区别：`constinit` 变量不一定是 const（可以修改）。

---

## `static_assert` —— 编译期断言

```cpp
static_assert(sizeof(void*) == 8, "This code requires 64-bit");
static_assert(factorial(10) == 3628800);  // 编译期验证！
```

---

## 一个实用的 `constexpr` 例子：编译期哈希

```cpp
constexpr uint32_t hash(const char* str, uint32_t h = 0) {
    return *str ? hash(str + 1, h * 31 + *str) : h;
}

// 字符串字面量被哈希成整数
switch (hash(key)) {
    case hash("start"): /* ... */ break;
    case hash("stop"):  /* ... */ break;
}
```
