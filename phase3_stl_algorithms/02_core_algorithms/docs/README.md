# STL 核心算法

## 理念：用算法代替循环

```cpp
// ❌ 手写循环（C++98 风格）
std::vector<int> result;
for (size_t i = 0; i < v.size(); ++i) {
    if (v[i] > 0) result.push_back(v[i] * 2);
}

// ✅ STL 算法（C++11+ 风格）—— 更清晰、更不容易出错
std::vector<int> result;
std::transform(v.begin(), v.end(), std::back_inserter(result),
    [](int x) { return x * 2; });  // 但这里没加过滤
```

---

## 算法分类速查表

### 不修改元素的查询

| 算法 | 用途 | 复杂度 |
|------|------|--------|
| `find` / `find_if` | 查找第一个匹配 | O(n) |
| `count` / `count_if` | 计数 | O(n) |
| `any_of` / `all_of` / `none_of` | 条件判断 | O(n) |
| `equal` | 两个范围相等？ | O(n) |
| `search` | 查找子序列 | O(n·m) |
| `binary_search` | 二分查找 | O(log n) |
| `lower_bound` / `upper_bound` | 二分定位 | O(log n) |

### 修改元素的

| 算法 | 用途 |
|------|------|
| `copy` / `copy_if` | 复制（可能过滤） |
| `transform` | 转换每个元素 |
| `fill` / `generate` | 填充 |
| `replace` / `replace_if` | 替换 |
| `remove` / `remove_if` | 逻辑删除（配合 `erase`） |
| `unique` | 去重 |

### 排序相关

| 算法 | 用途 |
|------|------|
| `sort` | 排序 O(n log n) |
| `stable_sort` | 稳定排序 |
| `partial_sort` | 局部排序 |
| `nth_element` | 第 n 大元素 |
| `is_sorted` | 判断是否已排序 |

### 数值（`<numeric>`）

| 算法 | 用途 |
|------|------|
| `accumulate` | 求和/归约 |
| `inner_product` | 内积 |
| `iota` | 生成递增序列 |
| `reduce`（C++17） | 并行归约 |

---

## Erase-Remove 惯用法

**终极重要！** 从容其中删除满足条件的元素：

```cpp
std::vector<int> v = {1, 2, 3, 4, 5, 6};

// ❌ 错误！在遍历中删除导致迭代器失效
for (auto it = v.begin(); it != v.end(); ) {
    if (*it % 2 == 0) it = v.erase(it);  // 虽然正确但繁琐
    else ++it;
}

// ✅ Erase-Remove Idiom（C++ 的标准姿势）
v.erase(std::remove_if(v.begin(), v.end(),
    [](int x) { return x % 2 == 0; }), v.end());

// C++20 简化：std::erase_if(v, [](int x) { return x % 2 == 0; });
```

执行过程：
1. `remove_if` 把要保留的元素往前搬，返回"新末尾"迭代器
2. `erase` 真正删除从"新末尾"到 `end()` 的元素

---

## 排序

```cpp
std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// 默认升序
std::sort(v.begin(), v.end());

// 自定义比较器
std::sort(v.begin(), v.end(), std::greater<int>{});

// 自定义 lambda
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });

// 稳定排序（相等元素保持原序）
std::stable_sort(v.begin(), v.end());
```

---

## `<numeric>` 算法

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};

int sum = std::accumulate(v.begin(), v.end(), 0);           // 15
int prod = std::accumulate(v.begin(), v.end(), 1,
    std::multiplies<int>{});                                // 120

// iota：生成序列
std::vector<int> seq(5);
std::iota(seq.begin(), seq.end(), 10);  // {10, 11, 12, 13, 14}
```
