# C++20 Ranges：管道式算法

> **这属于 C++20 的"了解"范畴，不需要像 STL 算法那样熟练掌握。**

## 传统算法的痛点

```cpp
std::vector<int> v = {1, -2, 3, -4, 5, -6};
std::vector<int> result;

// 传统写法：嵌套调用，读起来很累
std::transform(
    std::copy_if(v.begin(), v.end(), std::back_inserter(temp),
        [](int x) { return x > 0; }),
    // ... 等等，这甚至写起来就很困难
);
```

## Ranges 版本：管道风格

```cpp
#include <ranges>

auto result = v
    | std::views::filter([](int x) { return x > 0; })    // 过滤
    | std::views::transform([](int x) { return x * 2; }) // 转换
    | std::views::take(3)                                 // 取前 3 个
    | std::ranges::to<std::vector>();                     // C++23: 转为容器
```

**优点**：代码从左读到右，逻辑清晰。**惰性求值**：中间步骤不创建临时容器。

---

## 常用 Views

| View | 用途 | 等价操作 |
|------|------|---------|
| `views::filter(pred)` | 过滤 | `copy_if` |
| `views::transform(f)` | 转换 | `transform` |
| `views::take(n)` | 前 n 个 | — |
| `views::drop(n)` | 跳过前 n 个 | — |
| `views::reverse` | 反转 | 反向迭代器 |
| `views::keys` / `views::values` | map 的键/值 | — |
| `views::iota(start, end)` | 生成范围 | `std::iota` |
| `views::split(delim)` | 分割 | — |
| `views::join` | 扁平化 | — |

---

## Ranges 算法

C++20 在 `<algorithm>` 中添加了 `std::ranges::` 版本：

```cpp
// 传统
std::sort(v.begin(), v.end());

// Ranges 版本（可以传整个容器）
std::ranges::sort(v);
std::ranges::find(v, 42);
std::ranges::any_of(v, [](int x) { return x > 0; });
```

---

## 目前（2026）的局限

- **编译速度**：Ranges 代码编译较慢
- **错误信息**：嵌套 views 的错误信息非常长
- **`to<>` 是 C++23**：C++20 中转回容器需要手动 `std::vector(v.begin(), v.end())`
- **编译器支持**：GCC 12+, Clang 16+ 基本可用，但部分 views 仍有 bug

**建议**：
- 学习阶段了解 Ranges 的写法即可
- 实际项目中先用传统算法保证正确性
- 当编译器支持成熟后逐步迁移
