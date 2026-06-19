# 类模板

## 基本语法

```cpp
template<typename T>
class Stack {
public:
    void push(const T& value) { data_.push_back(value); }
    std::optional<T> pop() {
        if (data_.empty()) return std::nullopt;
        auto val = data_.back();
        data_.pop_back();
        return val;
    }
    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }

private:
    std::vector<T> data_;
};

// 使用
Stack<int> int_stack;
Stack<std::string> str_stack;
```

---

## 多个模板参数

```cpp
template<typename Key, typename Value>
class Cache {
    std::unordered_map<Key, Value> data_;
public:
    void put(const Key& k, const Value& v) { data_[k] = v; }
    std::optional<Value> get(const Key& k) {
        auto it = data_.find(k);
        if (it != data_.end()) return it->second;
        return std::nullopt;
    }
};

Cache<std::string, int> scores;
```

---

## 非类型模板参数

```cpp
template<typename T, size_t Capacity>
class StaticBuffer {
    std::array<T, Capacity> data_;
    size_t size_ = 0;
public:
    bool push(const T& x) {
        if (size_ >= Capacity) return false;
        data_[size_++] = x;
        return true;
    }
    constexpr size_t capacity() const { return Capacity; }
};

StaticBuffer<int, 16> buf;  // 栈上，无堆分配
```

---

## 成员函数模板

```cpp
template<typename T>
class Converter {
public:
    // 成员函数本身也是模板
    template<typename U>
    T convert(const U& val) {
        return static_cast<T>(val);
    }
};

Converter<int> c;
c.convert(3.14);     // double → int
c.convert(100L);     // long → int
```

---

## 默认模板参数

```cpp
template<typename T, typename Container = std::vector<T>>
class Queue {
    Container data_;
    // ...
};

Queue<int> q1;                // Queue<int, vector<int>>
Queue<int, std::deque<int>> q2;  // 显式指定 deque
```

---

## 模板特化

```cpp
// 通用版本
template<typename T>
struct TypeInfo {
    static const char* name() { return "unknown"; }
};

// 全特化
template<>
struct TypeInfo<int> {
    static const char* name() { return "int"; }
};

// 偏特化（指针）
template<typename T>
struct TypeInfo<T*> {
    static const char* name() {
        static std::string s = std::string(TypeInfo<T>::name()) + "*";
        return s.c_str();
    }
};
```

---

## 常见陷阱

1. **模板代码必须在头文件中**（和函数模板一样）
2. **嵌套依赖类型需要 `typename`**
   ```cpp
   template<typename T>
   void foo() {
       typename T::value_type x;  // 告诉编译器 value_type 是类型
   }
   ```
3. **模板 + 继承的构造问题**
   ```cpp
   template<typename T>
   struct Derived : Base<T> {
       using Base<T>::Base;  // 需要 using 声明来继承构造函数
   };
   ```
