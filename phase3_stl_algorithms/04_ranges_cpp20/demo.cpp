// phase3_stl_algorithms/04_ranges_cpp20/demo.cpp
// 演示：C++20 Ranges 管道式算法

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>

namespace views = std::views;

// ── 辅助打印 ──────────────────────────────────────────
template<typename Range>
void print_range(const Range& r, const char* label = "") {
    if (label[0]) std::cout << label << ": ";
    for (const auto& x : r) std::cout << x << ' ';
    std::cout << '\n';
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 基础管道
    // ═══════════════════════════════════════════════════════
    std::vector<int> v = {1, -2, 3, -4, 5, -6, 7, -8, 9, -10};
    print_range(v, "original");

    // 传统写法
    std::vector<int> traditional;
    std::copy_if(v.begin(), v.end(), std::back_inserter(traditional),
        [](int x) { return x > 0; });
    print_range(traditional, "traditional filter");

    // C++20 Ranges 写法：管道
    auto pipeline = v
        | views::filter([](int x) { return x > 0; })
        | views::transform([](int x) { return x * 10; })
        | views::take(3);

    std::cout << "ranges pipeline (filter>0, *10, take 3): ";
    for (int x : pipeline) std::cout << x << ' ';
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. std::ranges:: 算法
    // ═══════════════════════════════════════════════════════
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};

    // 传统
    std::sort(nums.begin(), nums.end());

    // C++20 ranges 风格（直接传容器）
    std::ranges::sort(nums);  // 不需要 .begin()/.end()！
    print_range(nums, "ranges::sort");

    auto it = std::ranges::find(nums, 5);
    if (it != nums.end()) {
        std::cout << "ranges::find(5) found at index "
                  << std::distance(nums.begin(), it) << '\n';
    }

    bool all_positive = std::ranges::all_of(nums,
        [](int x) { return x > 0; });
    std::cout << "all positive: " << all_positive << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 其他 views
    // ═══════════════════════════════════════════════════════
    // iota：生成序列（惰性）
    auto seq = views::iota(1, 11);  // 1, 2, ..., 10 (惰性，不分配内存)
    std::cout << "iota(1,11): ";
    for (int x : seq) std::cout << x << ' ';
    std::cout << '\n';

    // iota + filter + transform 组合
    auto even_squares = views::iota(1)
        | views::filter([](int x) { return x % 2 == 0; })
        | views::transform([](int x) { return x * x; })
        | views::take(5);
    std::cout << "first 5 even squares: ";
    for (int x : even_squares) std::cout << x << ' ';
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. drop, reverse, keys/values
    // ═══════════════════════════════════════════════════════
    std::vector<int> d = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 跳过前 3 个，取剩下的前 4 个
    auto skipped = d | views::drop(3) | views::take(4);
    std::cout << "drop(3) | take(4): ";
    for (int x : skipped) std::cout << x << ' ';  // 4 5 6 7
    std::cout << '\n';

    // 反转
    std::cout << "reverse of {1,2,3,4,5}: ";
    for (int x : std::vector{1, 2, 3, 4, 5} | views::reverse) {
        std::cout << x << ' ';  // 5 4 3 2 1
    }
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. 惰性求值：中间不产生临时容器
    // ═══════════════════════════════════════════════════════
    auto lazy = views::iota(1, 10000000)  // 1000 万个整数（不分配！）
        | views::filter([](int x) { return x % 2 == 0; })
        | views::transform([](int x) { return x * x; })
        | views::take(5);
    std::cout << "Lazy: first 5 even squares from 1..10M: ";
    for (int x : lazy) std::cout << x << ' ';
    std::cout << "\n(No 10M-element vector was created!)\n";

    return 0;
}
