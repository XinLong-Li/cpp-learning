// phase3_stl_algorithms/04_ranges_cpp20/exercise.cpp
// 练习：C++20 Ranges

#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>

namespace views = std::views;

// ── 练习 1：用 Ranges 改写 ────────────────────────────
// 下面的传统代码用 Ranges 管道改写

void exercise1() {
    std::vector<int> v = {10, -5, 3, -2, 8, -1, 0, 6};

    // 传统：找到所有正数，将它们平方，取前 3 个
    std::vector<int> temp;
    std::copy_if(v.begin(), v.end(), std::back_inserter(temp),
        [](int x) { return x > 0; });
    std::vector<int> squared;
    std::transform(temp.begin(), temp.end(), std::back_inserter(squared),
        [](int x) { return x * x; });
    std::vector<int> first3(squared.begin(),
        squared.begin() + std::min<size_t>(3, squared.size()));

    for (int x : first3) std::cout << x << ' ';

    // TODO: 用 ranges 管道一行完成
    // auto result = v | ...;
}

// ── 练习 2：实现 sliding_window ──────────────────────

// TODO: 用 views::slide (C++23) 或手动实现滑动窗口
// 提示：C++20 没有 slide，但可以用 iota + transform 模拟

// ── 练习 3：字符串分割 ──────────────────────────────
// 用 views::split 分割字符串

// TODO: 实现 split 函数
// auto split_words(std::string_view text) {
//     // 用 views::split(' ') 分割
// }

// ── 练习 4：对比传统和 Ranges ────────────────────────
// 写一个函数，对 vector<int> 做：过滤正数 → 乘以 3 → 取前 5 → 排序
// 分别用传统算法和 Ranges 实现

// TODO: 实现两个版本并比较

// ── 主函数 ───────────────────────────────────────────────
int main() {
    exercise1();
    return 0;
}
