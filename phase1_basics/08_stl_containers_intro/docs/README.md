# STL 容器入门

## 容器选择速查表

| 需求 | 首选容器 | 备选 |
|------|---------|------|
| 顺序存储，随机访问 | `std::vector<T>` | `std::deque<T>` |
| 定长数组 | `std::array<T, N>` | 裸数组 `T[N]`（不推荐） |
| 键值查找，快速 | `std::unordered_map<K,V>` | `std::map<K,V>` |
| 键值查找，有序遍历 | `std::map<K,V>` | — |
| 唯一键，快速查找 | `std::unordered_set<T>` | `std::set<T>` |
| 字符串 | `std::string` | `std::string_view`（只读） |

**90% 的场景：`vector` + `unordered_map`。**

---

## `std::vector<T>` —— 默认容器

```cpp
#include <vector>

std::vector<int> v;           // 空
std::vector<int> v2(5, 42);   // {42, 42, 42, 42, 42}
std::vector<int> v3 = {1, 2, 3};  // 初始化列表

v.push_back(4);               // 尾部追加
v.emplace_back(5);            // 原地构造（更高效）
auto x = v[2];                // 不检查边界（快但危险）
auto y = v.at(2);             // 检查边界（安全，越界抛异常）
v.size();                     // 元素数量
v.capacity();                 // 已分配的空间
v.reserve(100);               // 预分配（避免多次重分配）
```

### Vector 的核心优化：`reserve`

```cpp
// ❌ 坏：多次重分配
std::vector<int> v;
for (int i = 0; i < 10000; ++i)
    v.push_back(i);  // 可能触发 ~14 次内存重分配

// ✅ 好：预分配
std::vector<int> v;
v.reserve(10000);
for (int i = 0; i < 10000; ++i)
    v.emplace_back(i);  // 零重分配
```

---

## `std::array<T, N>` —— 定长数组

```cpp
std::array<int, 5> arr = {1, 2, 3, 4, 5};
// 优于 int arr[5]：
// - 有 .size(), .at(), .front(), .back()
// - 传递给函数不会退化为指针
// - 支持迭代器和 STL 算法
```

---

## `std::unordered_map<K, V>` vs `std::map<K, V>`

| | `unordered_map` | `map` |
|---|-----------------|-------|
| 实现 | 哈希表 | 红黑树 |
| 查找 | O(1) 平均 | O(log n) |
| 有序 | ❌ | ✅（按键排序） |
| 内存 | 较高（桶数组） | 较低 |
| Key 要求 | 可哈希 | 可比较（`operator<`） |

```cpp
std::unordered_map<std::string, int> ages;
ages["Alice"] = 30;
ages.try_emplace("Bob", 25);  // 仅当 Bob 不存在时插入 (C++17)

if (auto it = ages.find("Alice"); it != ages.end()) {
    std::cout << it->second << '\n';
}
```

---

## 容器遍历

```cpp
// 默认：只读引用
for (const auto& item : container) { ... }

// 需要修改
for (auto& item : container) { ... }

// C++17 结构化绑定（map）
for (const auto& [key, value] : map) { ... }
```

---

## 常见陷阱

1. **Vector 的引用/迭代器失效**
   ```cpp
   std::vector<int> v = {1, 2, 3};
   int& ref = v[0];        // ref 引用 v[0]
   v.push_back(4);         // 可能触发重分配，ref 失效！
   std::cout << ref;        // ❌ 未定义行为
   ```

2. **`operator[]` vs `find` vs `try_emplace`**
   ```cpp
   // ❌ map[key] 不存在时会插入默认值
   int age = ages["Charlie"];  // 插入 Charlie: 0
   
   // ✅ 只查找，不插入
   if (auto it = ages.find("Charlie"); it != ages.end()) { ... }
   
   // ✅ 只在不存在时插入 (C++17)
   ages.try_emplace("Charlie", 35);
   ```

3. **Vector<bool> 是特殊的**
   ```cpp
   std::vector<bool> bv(10);
   auto bit = bv[0];  // bit 不是 bool&！是代理对象
   // 如果需要 bit 容器，用 vector<char> 或 deque<bool>
   ```
