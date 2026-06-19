# 智能指针：告别 `new` 和 `delete`

## 三种智能指针速查

| 智能指针 | 所有权模型 | 典型场景 |
|----------|-----------|---------|
| `unique_ptr<T>` | 独占所有权 | 工厂函数返回、PIMPL、独占资源 |
| `shared_ptr<T>` | 共享所有权（引用计数） | 多个对象共享同一个资源 |
| `weak_ptr<T>` | 不拥有，观察 | 打破循环引用、缓存 |

---

## `std::unique_ptr<T>` —— 你应该用的默认选择

```cpp
auto p = std::make_unique<Widget>(arg1, arg2);  // 创建（C++14）
auto arr = std::make_unique<int[]>(100);         // 数组

// 移动所有权
auto p2 = std::move(p);   // p2 现在拥有 Widget，p == nullptr

// 作为函数参数：接收所有权
void consume(std::unique_ptr<Widget> w);  // 调用方必须 std::move

// 作为函数参数：只是使用，不接管所有权
void use(const Widget* w);  // 或 const Widget&
void use(const std::unique_ptr<Widget>& w);  // 很少用

// 释放原始指针（给 C API）
Widget* raw = p.release();  // p 放弃所有权，调用方负责 delete
```

### `unique_ptr` 自定义删除器

```cpp
auto file_deleter = [](FILE* f) { if (f) fclose(f); };
std::unique_ptr<FILE, decltype(file_deleter)> file(fopen("a.txt","r"), file_deleter);
```

---

## `std::shared_ptr<T>` —— 谨慎使用

### 何时用

- 多个对象共享同一个资源，且最后一个使用者负责清理
- 无法确定谁最后一个用完资源时

### 何时不用

- 大多数场景用 `unique_ptr` 就够了
- 不要因为"懒得想所有权"就用 `shared_ptr`

```cpp
auto p1 = std::make_shared<Widget>();    // 一次分配（C++17 及之前也能用）
auto p2 = p1;                             // 引用计数 +1
auto p3 = p1;                             // 引用计数 +1

p1.reset();  // p1 释放，计数 -1
p2.reset();  // p2 释放，计数 -1
p3.reset();  // 计数归零，Widget 被 delete
```

### `shared_ptr` 的代价

1. **控制块**（引用计数 + 弱引用计数 + 删除器）—— 额外内存分配
2. **引用计数操作是原子的**（线程安全，但有开销）
3. **循环引用**会导致**内存泄漏**

---

## `std::weak_ptr<T>` —— 打破循环引用

```cpp
std::shared_ptr<Node> a = std::make_shared<Node>();
std::shared_ptr<Node> b = std::make_shared<Node>();
a->next = b;  // shared_ptr 指向 b
b->prev = a;  // shared_ptr 指向 a → 循环引用！a 和 b 永远不会销毁！

// 解决：prev 用 weak_ptr
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;   // 不增加引用计数！
};
```

使用 `weak_ptr` 时需要先 `lock()`：
```cpp
if (auto sp = weak.lock()) {  // 提升为 shared_ptr（如果原对象还在）
    sp->do_something();
}
```

---

## 与原始指针的对比

| 代码 | 含义 | 推荐？ |
|------|------|-------|
| `T* ptr` | 不拥有所有权，只观察/使用 | ✅ 观察者、可选引用 |
| `T& ref` | 不拥有所有权，确定非空 | ✅ 首选（明确非空） |
| `unique_ptr<T>` | 独占所有权 | ✅ 工厂返回、PIMPL |
| `shared_ptr<T>` | 共享所有权 | ⚠️ 仅在确实需要时 |
| 裸 `new` / `delete` | — | ❌ 永远不要写 |

---

## 工厂函数模式

```cpp
// ✅ 工厂返回 unique_ptr：明确传递所有权
std::unique_ptr<Shape> create_shape(const std::string& type) {
    if (type == "circle") return std::make_unique<Circle>();
    if (type == "rect")   return std::make_unique<Rectangle>();
    return nullptr;
}
```
