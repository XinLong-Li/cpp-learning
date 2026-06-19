// phase3_stl_algorithms/02_core_algorithms/demo.cpp
// 演示：核心 STL 算法

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

// ── 辅助打印 ──────────────────────────────────────────
template<typename Container>
void print(const Container& c, const char* label = "") {
    if (label[0]) std::cout << label << ": ";
    for (const auto& x : c) std::cout << x << ' ';
    std::cout << '\n';
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 查询算法
    // ═══════════════════════════════════════════════════════
    std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    print(v, "data");

    // find / find_if
    auto it = std::find(v.begin(), v.end(), 5);
    std::cout << "find(5): " << (it != v.end() ? "found" : "not found") << '\n';

    auto first_even = std::find_if(v.begin(), v.end(),
        [](int x) { return x % 2 == 0; });
    std::cout << "first even: " << *first_even << '\n';

    // count / count_if
    std::cout << "count of 5: " << std::count(v.begin(), v.end(), 5) << '\n';
    std::cout << "count even: "
              << std::count_if(v.begin(), v.end(), [](int x) { return x%2==0; })
              << '\n';

    // any_of / all_of / none_of
    std::cout << "any > 8: " << std::any_of(v.begin(), v.end(),
        [](int x) { return x > 8; }) << '\n';
    std::cout << "all > 0: " << std::all_of(v.begin(), v.end(),
        [](int x) { return x > 0; }) << '\n';
    std::cout << "none negative: " << std::none_of(v.begin(), v.end(),
        [](int x) { return x < 0; }) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. 排序
    // ═══════════════════════════════════════════════════════
    std::vector<int> v2 = {3, 1, 4, 1, 5, 9, 2, 6};
    print(v2, "before sort");

    std::sort(v2.begin(), v2.end());
    print(v2, "after sort");

    std::sort(v2.begin(), v2.end(), std::greater<int>{});
    print(v2, "descending");

    // 部分排序：最小的 3 个放在开头
    std::vector<int> v3 = {7, 2, 9, 1, 5, 3, 8};
    std::partial_sort(v3.begin(), v3.begin() + 3, v3.end());
    print(v3, "partial_sort (top 3)");
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. 二分查找（需要先排序）
    // ═══════════════════════════════════════════════════════
    std::vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "binary_search(5): "
              << std::binary_search(sorted.begin(), sorted.end(), 5) << '\n';
    std::cout << "binary_search(10): "
              << std::binary_search(sorted.begin(), sorted.end(), 10) << '\n';

    auto lb = std::lower_bound(sorted.begin(), sorted.end(), 5);
    std::cout << "lower_bound(5) index: " << (lb - sorted.begin()) << '\n';
    auto ub = std::upper_bound(sorted.begin(), sorted.end(), 5);
    std::cout << "upper_bound(5) index: " << (ub - sorted.begin()) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. Erase-Remove Idiom
    // ═══════════════════════════════════════════════════════
    std::vector<int> vr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print(vr, "before erase");

    // 删除所有偶数
    vr.erase(std::remove_if(vr.begin(), vr.end(),
        [](int x) { return x % 2 == 0; }), vr.end());
    print(vr, "after remove_if (evens gone)");
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. transform
    // ═══════════════════════════════════════════════════════
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::vector<int> squared(src.size());

    std::transform(src.begin(), src.end(), squared.begin(),
        [](int x) { return x * x; });
    print(src, "source");
    print(squared, "squared");
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 6. <numeric> 算法
    // ═══════════════════════════════════════════════════════
    std::vector<int> nums = {1, 2, 3, 4, 5};

    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    int product = std::accumulate(nums.begin(), nums.end(), 1,
        std::multiplies<int>{});

    std::cout << "accumulate(sum): " << sum << '\n';
    std::cout << "accumulate(product): " << product << '\n';

    // iota
    std::vector<int> seq(10);
    std::iota(seq.begin(), seq.end(), 100);
    print(seq, "iota(100..109)");

    // C++17 reduce（可并行）
    int reduced = std::reduce(nums.begin(), nums.end(), 0);
    std::cout << "reduce: " << reduced << " (parallelizable!)\n";

    return 0;
}
