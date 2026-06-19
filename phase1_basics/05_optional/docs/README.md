# `std::optional<T>` —— 可能不存在的值

## 为什么需要 `optional`？

```cpp
// ❌ 旧式做法 1：特殊值
int find_index(const std::vector<int>& v, int target) {
    for (size_t i = 0; i < v.size(); ++i)
        if (v[i] == target) return i;
    return -1;  // "找不到"用 -1 表示 —— 但如果 -1 是合法索引怎么办？
}

// ❌ 旧式做法 2：输出参数
bool find_index(const std::vector<int>& v, int target, int& out) {
    // 返回 bool + 输出参数 —— 繁琐！
}

// ✅ 现代做法：std::optional
std::optional<size_t> find_index(const std::vector<int>& v, int target) {
    for (size_t i = 0; i < v.size(); ++i)
        if (v[i] == target) return i;
    return std::nullopt;  // 明确表达"没有值"
}
```

---

## 基本用法

```cpp
#include <optional>

std::optional<int> maybe = 42;

// 检查是否有值
if (maybe.has_value()) { /* ... */ }
if (maybe) { /* ... */ }  // operator bool，更简洁

// 获取值
int x = maybe.value();           // 无值时抛 std::bad_optional_access
int y = *maybe;                  // 不检查，无值时 UB！
int z = maybe.value_or(-1);     // 无值时返回默认值

// 赋空值
maybe = std::nullopt;
maybe.reset();
```

---

## 典型使用场景

### 1. 可能失败的查找
```cpp
std::optional<Person> find_by_id(int id);
```

### 2. 可能失败的解析
```cpp
std::optional<int> parse_int(std::string_view s);
```

### 3. 延迟初始化
```cpp
class Widget {
    std::optional<Expensive> data_;
public:
    void init_data() { data_ = Expensive{...}; }
    const Expensive* get() const {
        return data_ ? &*data_ : nullptr;
    }
};
```

### 4. 配置项
```cpp
struct Config {
    std::optional<std::string> log_file;      // 可能不指定
    std::optional<int> max_retries;           // 可能用默认值
};
```

---

## 与指针的对比

| | `std::optional<T>` | `T*` | `std::unique_ptr<T>` |
|---|---|---|---|
| 所有权 | 值语义（栈上） | 无所有权 | 独占所有权 |
| 内存 | 栈（无堆分配） | 指向堆或栈 | 堆分配 |
| 语义 | "可能有值" | "可能是空指针" 或 "持有引用" | "拥有对象" |
| 移动 | 支持 | 不支持 | 支持 |

**优先用 `optional`，除非你需要所有权（`unique_ptr`）或引用现有对象（`T*`）。**

---

## 常见陷阱

1. **不要用 `*optional` 而不检查**
   ```cpp
   std::optional<int> o;
   int x = *o;  // ❌ 未定义行为！o 无值
   ```
   始终先检查：`if (o) { int x = *o; }`

2. **`value()` 抛出异常，`*op` 不检查**
   ```cpp
   o.value();  // 无值时抛 std::bad_optional_access
   *o;         // 无值时 UB —— 只在确定有值时用
   ```

3. **`optional` 的开销**
   - 比裸 `T` 多一个 `bool` + 对齐填充
   - 无堆分配，性能友好

4. **`optional<optional<T>>` 一般不必要**
   - C++17 不允许 `optional<optional<T>>`（被禁止了）
