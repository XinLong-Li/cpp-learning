// phase5_cpp17_library/05_parallel_algorithms/demo.cpp
// 演示：C++17 并行算法
//
// 注意：Apple Clang/libc++ 尚未实现 std::execution::par
//       本文件会自动检测并用顺序算法替代

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>

#ifdef __cpp_lib_parallel_algorithm
#include <execution>
#endif

// ── Timer 辅助 ───────────────────────────────────────
struct Timer {
    const char* name;
    std::chrono::steady_clock::time_point start;
    Timer(const char* n) : name(n), start(std::chrono::steady_clock::now()) {}
    ~Timer() {
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "  " << name << ": " << ms << " ms\n";
    }
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
#ifdef __cpp_lib_parallel_algorithm
    constexpr bool has_parallel = true;
#else
    constexpr bool has_parallel = false;
    std::cout << "⚠ 当前编译器不支持 std::execution::par（Apple Clang 已知限制）\n"
              << "  并行算法演示将使用顺序版本替代\n\n";
#endif

    constexpr size_t N = 2'000'000;

    // ═══════════════════════════════════════════════════════
    // 1. 生成测试数据
    // ═══════════════════════════════════════════════════════
    std::vector<int> data_seq(N);
    {
        Timer t("Generate data");
        std::mt19937 rng(42);
        std::uniform_int_distribution<int> dist(1, 1'000'000);
        for (size_t i = 0; i < N; ++i) data_seq[i] = dist(rng);
    }
    std::cout << "Data size: " << N << " elements\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. sort
    // ═══════════════════════════════════════════════════════
    {
        auto v = data_seq;
        Timer t("sort (sequential)");
        std::sort(v.begin(), v.end());
    }
#if __cpp_lib_parallel_algorithm
    {
        auto v = data_seq;
        Timer t("sort (parallel)");
        std::sort(std::execution::par, v.begin(), v.end());
    }
#endif
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. accumulate vs reduce
    // ═══════════════════════════════════════════════════════
    {
        Timer t("accumulate (sequential)");
        volatile auto sum = std::accumulate(data_seq.begin(), data_seq.end(), 0LL);
    }
#if __cpp_lib_parallel_algorithm
    {
        Timer t("reduce (parallel)");
        volatile auto sum = std::reduce(std::execution::par,
                                        data_seq.begin(), data_seq.end(), 0LL);
    }
#endif
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. find_if
    // ═══════════════════════════════════════════════════════
    {
        Timer t("find_if (sequential)");
        auto it = std::find_if(data_seq.begin(), data_seq.end(),
            [](int x) { return x > 999'000; });
    }
#if __cpp_lib_parallel_algorithm
    {
        Timer t("find_if (parallel)");
        auto it = std::find_if(std::execution::par, data_seq.begin(), data_seq.end(),
            [](int x) { return x > 999'000; });
    }
#endif
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. transform
    // ═══════════════════════════════════════════════════════
    std::vector<int> result_seq(N);
    {
        Timer t("transform (sequential)");
        std::transform(data_seq.begin(), data_seq.end(), result_seq.begin(),
            [](int x) { return x * 2 + 1; });
    }
#if __cpp_lib_parallel_algorithm
    {
        std::vector<int> result_par(N);
        Timer t("transform (parallel)");
        std::transform(std::execution::par,
            data_seq.begin(), data_seq.end(), result_par.begin(),
            [](int x) { return x * 2 + 1; });
    }
#endif

    std::cout << "\nNote: 并行算法在大数据集上优势明显\n";
    std::cout << "      GCC 需链接 -ltbb 才能真正并行\n";

    return 0;
}
