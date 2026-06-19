# 异常安全（Exception Safety）

## 异常安全的三个保证级别

| 级别 | 含义 | 示例 |
|------|------|------|
| **不抛出保证** (nothrow) | 绝对不抛异常 | 析构函数、移动构造（noexcept）、swap |
| **强保证** (strong) | 抛异常时状态回滚到调用前 | 拷贝后交换（copy-and-swap） |
| **基本保证** (basic) | 抛异常时对象仍然有效（不泄漏），但状态可能改变 | 大多数代码 |

---

## RAII 是异常安全的基础

```cpp
void safe_function() {
    auto data = std::make_unique<Data>();
    auto lock = std::lock_guard(mtx);
    // 即使这里抛出异常，data 和 lock 的析构函数保证被调用
    risky_operation();
}
```

---

## 析构函数绝不抛异常

```cpp
~MyClass() noexcept {  // C++11 起，析构函数隐式 noexcept
    // 如果这里抛出异常且栈正在展开 → std::terminate
}
```

---

## `noexcept`

```cpp
void nofail() noexcept;       // 承诺不抛异常
void nofail() noexcept(true); // 同上

template<typename T>
void maybe() noexcept(std::is_nothrow_move_constructible_v<T>);
// 条件 noexcept：取决于 T 的移动构造是否不抛
```

`noexcept` 的价值：
1. 编译器能生成更优化的代码
2. `std::vector` 扩容时优先用 `noexcept` 移动构造

---

## 常见安全模式

### Copy-and-Swap（强保证）
```cpp
class Buffer {
    void swap(Buffer& other) noexcept { /* 交换内部指针 */ }

    Buffer& operator=(const Buffer& other) {
        Buffer tmp(other);   // 可能抛异常（拷贝）
        swap(tmp);           // 不抛异常
        return *this;
    }   // tmp 析构，释放旧资源
};
```

### 先操作后提交
```cpp
void append_to_file(const std::string& path, const std::string& data) {
    auto tmp_path = path + ".tmp";
    std::ofstream(tmp_path) << data;  // 先写临时文件
    fs::rename(tmp_path, path);       // 原子重命名
}
```

---

## Sanitizers（必用工具）

```bash
# AddressSanitizer：内存错误
g++ -fsanitize=address -g main.cpp && ./a.out

# UndefinedBehaviorSanitizer：未定义行为
g++ -fsanitize=undefined -g main.cpp && ./a.out

# 同时开启
g++ -fsanitize=address,undefined -g main.cpp && ./a.out
```

| Sanitizer | 检测 |
|-----------|------|
| AddressSanitizer | use-after-free, buffer overflow, memory leak |
| UndefinedBehaviorSanitizer | 整数溢出, null deref, 越界 shift |
| ThreadSanitizer | 数据竞争 |
| MemorySanitizer | 未初始化内存读 |
