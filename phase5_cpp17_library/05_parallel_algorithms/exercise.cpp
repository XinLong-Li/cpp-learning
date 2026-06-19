// phase5_cpp17_library/05_parallel_algorithms/exercise.cpp
// 练习：并行算法

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>
#include <chrono>

// ── 练习 1：并行 for_each 计数 ──────────────────────────
// 用并行 for_each 统计 vector 中满足条件的元素个数
// 注意：需要用原子操作或 reduce

#include <atomic>

// TODO: 实现
// template<typename Container, typename Predicate>
// size_t parallel_count_if(const Container& c, Predicate pred) {
//     std::atomic<size_t> count = 0;
//     std::for_each(std::execution::par, c.begin(), c.end(),
//         [&](const auto& x) { if (pred(x)) ++count; });
//     return count;
// }

// ── 练习 2：比较并行算法在不同数据量下的性能 ─────────

// TODO: 写一个 benchmark 函数
// 测试不同数据量（1K, 10K, 100K, 1M, 10M）下 sort 的并行和顺序耗时
// void benchmark_sort() { ... }

// ── 练习 3：并行 map-reduce ─────────────────────────
// 实现 parallel_map_reduce:
// 1. 并行 transform 每个元素
// 2. 并行 reduce 汇总

// TODO: 实现
// template<typename Container, typename Transform, typename Reduce>
// auto parallel_map_reduce(const Container& c, Transform t, Reduce r,
//                          decltype(t(c[0])) init) {
//     std::vector<decltype(init)> transformed(c.size());
//     std::transform(std::execution::par, c.begin(), c.end(),
//         transformed.begin(), t);
//     return std::reduce(std::execution::par,
//         transformed.begin(), transformed.end(), init, r);
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // std::vector<int> v(100000);
    // std::iota(v.begin(), v.end(), 1);
    // size_t even_count = parallel_count_if(v, [](int x) { return x % 2 == 0; });
    // std::cout << "Even numbers: " << even_count << '\n';

    // 练习 2:
    // benchmark_sort();

    // 练习 3:
    // std::vector<int> v(100000, 1);
    // auto result = parallel_map_reduce(v,
    //     [](int x) { return x * 2; },          // map
    //     std::plus<>{},                          // reduce
    //     0);
    // std::cout << "Result: " << result << '\n';

    return 0;
}
