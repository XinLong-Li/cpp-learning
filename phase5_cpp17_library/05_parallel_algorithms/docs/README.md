# C++17 并行算法

## 执行策略

```cpp
#include <execution>
#include <algorithm>
#include <vector>

std::vector<int> v(1'000'000);

// 顺序执行（默认）
std::sort(v.begin(), v.end());

// 并行执行
std::sort(std::execution::par, v.begin(), v.end());

// 并行 + 向量化
std::sort(std::execution::par_unseq, v.begin(), v.end());

// 顺序但不保证顺序（可向量化）
std::sort(std::execution::unseq, v.begin(), v.end());
```

---

## 四种执行策略

| 策略 | 含义 |
|------|------|
| `std::execution::seq` | 顺序执行 |
| `std::execution::par` | 并行（多线程） |
| `std::execution::par_unseq` | 并行 + SIMD 向量化 |
| `std::execution::unseq` | 单线程 SIMD 向量化 |

---

## 支持并行执行的算法

大多数 `<algorithm>` 中的算法都支持，包括：
- `sort`, `partial_sort`
- `for_each`, `for_each_n`
- `find`, `find_if`, `find_end`, `find_first_of`
- `count`, `count_if`
- `copy`, `copy_if`, `copy_n`
- `transform`, `reduce`, `inclusive_scan`, `exclusive_scan`

---

## 注意事项

### 1. 数据竞争由你负责
```cpp
int sum = 0;
std::mutex mtx;
// ❌ 并行执行下有数据竞争
std::for_each(std::execution::par, v.begin(), v.end(),
    [&](int x) { sum += x; });

// ✅ 用 mutex（但会大幅降低并行性）
std::for_each(std::execution::par, v.begin(), v.end(),
    [&](int x) { std::lock_guard lk(mtx); sum += x; });

// ✅ 用 reduce（无锁并行归约）
sum = std::reduce(std::execution::par, v.begin(), v.end(), 0);
```

### 2. 并行可能比顺序慢
- 数据量太小：并行开销大于收益
- 临界值通常 > 10,000 元素以上并行才有优势

### 3. 需要链接 TBB（Intel Threading Building Blocks）
GCC 的并行 STL 实现依赖 TBB：
```bash
sudo apt install libtbb-dev
g++ -std=c++17 main.cpp -ltbb
```

### 4. 不要假设执行顺序
并行算法的执行顺序不确定，不要依赖。
