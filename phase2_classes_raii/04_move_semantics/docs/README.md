# 移动语义（Move Semantics）

## 拷贝 vs 移动

```cpp
std::string s1 = "hello world";      // s1 拥有 "hello world"
std::string s2 = s1;                 // 拷贝：s2 有自己的副本（深拷贝）
std::string s3 = std::move(s1);      // 移动：s3 接管了 s1 的数据，s1 变成空
```

- **拷贝** = 完整复制数据（昂贵）
- **移动** = 转移内部指针（便宜，O(1)）

---

## `std::move` 做了什么？

**`std::move` 不移动任何东西！** 它只是一个**类型转换**：将左值转换为右值引用。

```cpp
int x = 42;
int&& r = std::move(x);  // std::move 只是把 x 转成右值引用
// 此时 x 仍然是有效的 int，没有被"移走"
```

真正的"移动"发生在**移动构造函数**或**移动赋值运算符**中。

---

## 移动操作怎么写？

```cpp
class Buffer {
    char* data_;
    size_t size_;

public:
    // 拷贝构造（深拷贝）
    Buffer(const Buffer& other)
        : size_(other.size_) {
        data_ = new char[size_];
        std::memcpy(data_, other.data_, size_);
    }

    // 移动构造（偷资源）
    Buffer(Buffer&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;   // 让原对象处于安全状态
        other.size_ = 0;
    }

    // 移动赋值
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;             // 释放自己的资源
            data_ = other.data_;        // 偷
            size_ = other.size_;
            other.data_ = nullptr;      // 让原对象安全
            other.size_ = 0;
        }
        return *this;
    }

    ~Buffer() { delete[] data_; }
};
```

---

## Rule of Five / Rule of Zero

### Rule of Five
如果定义了下面任一个，通常需要定义全部五个：
1. 析构函数
2. 拷贝构造
3. 拷贝赋值
4. 移动构造
5. 移动赋值

### Rule of Zero（推荐！）
**不要定义任何特殊成员函数。** 让编译器自动生成，或者用成员类型管理资源（如 `vector`, `string`, `unique_ptr`）。

```cpp
// ✅ Rule of Zero：所有成员都管理好自己的资源
class Good {
    std::vector<int> data_;
    std::string name_;
    std::unique_ptr<Expensive> extra_;
    // 不需要手动写任何析构/拷贝/移动
};
```

---

## 什么时候用 `std::move`？

### ✅ 要用的地方
```cpp
// 1. 显式移动所有权
auto p2 = std::move(p1);

// 2. 向容器中放入大对象
std::vector<std::string> v;
v.push_back(std::move(str));  // 放入后 str 为空

// 3. unique_ptr 的所有权转移
consume(std::move(ptr));
```

### ❌ 不要用的地方
```cpp
// 1. return 语句 —— 破坏 RVO！
std::string bad() {
    std::string s = "hello";
    return std::move(s);  // ❌ 阻止了 RVO
}

// 2. const 对象 —— move 退化为 copy
const std::string s = "hello";
auto s2 = std::move(s);  // 实际上做的是拷贝！（const 不能 move）
```

---

## 移动后的对象

**移动后的对象处于"有效但未指定"的状态。** 你仍然可以：
- 销毁它
- 给它赋新值
- 调用不依赖具体值的操作（如 `.empty()`, `.size()`）

```cpp
std::string s = "hello";
std::string s2 = std::move(s);

s.clear();     // ✅ OK：赋新值
s = "world";   // ✅ OK：赋新值
// std::cout << s[0];  // ⚠️ 未指定（空字符串还是原数据？实现定义）
```

**不要依赖移动后对象的具体内容，除非类型明确文档化。**
