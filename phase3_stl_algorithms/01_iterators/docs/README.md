# 迭代器（Iterators）

## 迭代器是算法和容器的桥梁

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto it = v.begin();   // 指向第一个元素
auto end = v.end();    // 指向最后一个元素之后（哨兵）

*it;       // 解引用 → 1
++it;      // 前进
*it;       // 解引用 → 2
it == end; // 比较是否到达末尾
```

---

## 迭代器类别

| 类别 | 能力 | 典型容器 |
|------|------|---------|
| Input | 只读，单向 ++ | `istream_iterator` |
| Forward | 读写，单向 ++ | `forward_list` |
| Bidirectional | 读写，++ 和 -- | `list`, `set`, `map` |
| RandomAccess | 读写，++, --, +n, [], < | `vector`, `array`, `deque`, `string` |
| Contiguous (C++17) | RandomAccess + 连续内存 | `vector`, `array`, `string` |

---

## 常见迭代器操作

```cpp
std::vector<int> v = {10, 20, 30, 40, 50};

// 基本
auto it = v.begin();
*it;           // 10
*(it + 2);     // 30（仅 RandomAccess）
it[2];         // 30（同上）

// 反向迭代器
for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
    std::cout << *rit << ' ';  // 50 40 30 20 10
}

// 常量迭代器（不可修改）
auto cit = v.cbegin();  // C++11

// 插入迭代器
std::vector<int> out;
std::copy(v.begin(), v.end(), std::back_inserter(out));  // 在 out 尾部插入
```

---

## 迭代器失效

**这是 C++ 最常见的 bug 来源之一！**

### Vector
```cpp
std::vector<int> v = {1, 2, 3};
auto it = v.begin();  // it 指向 v[0]

v.push_back(4);       // 可能触发重分配 → it 失效！
// *it;               // ❌ 未定义行为

it = v.begin() + 10;
v.erase(v.begin());   // erase 点之后的迭代器全部失效
// *it;               // ❌ 未定义行为
```

### Map / Set
```cpp
std::map<int, std::string> m = {{1, "a"}, {2, "b"}};
auto it = m.find(1);
m.erase(2);           // ✅ 其他迭代器不受影响（map/set 的删除不影响别的）
m.erase(it);          // ✅ 删除 it 指向的元素，it 失效但其他 OK
// *it;               // ❌ it 本身已失效
```

---

## 迭代器适配器

```cpp
// 反向迭代
std::vector<int> v = {1, 2, 3, 4, 5};
auto it = std::find(v.rbegin(), v.rend(), 3);  // 从后往前找

// 流迭代器
std::vector<int> from_stream(
    std::istream_iterator<int>(std::cin),
    std::istream_iterator<int>()
);

// 插入迭代器
std::copy(src.begin(), src.end(), std::back_inserter(dst));   // push_back
std::copy(src.begin(), src.end(), std::inserter(s, s.end())); // insert
```

---

## 迭代器 vs 索引

```cpp
// ❌ 坏：C 风格索引遍历（只有 RandomAccess 能用）
for (size_t i = 0; i < v.size(); ++i) {
    process(v[i]);
}

// ✅ 好：range-based for（所有容器通用）
for (const auto& item : v) {
    process(item);
}

// ✅ 好：算法（最高级抽象）
std::for_each(v.begin(), v.end(), process);
```
