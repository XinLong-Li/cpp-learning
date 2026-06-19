// phase5_cpp17_library/05_parallel_algorithms/demo.cpp
// 演示：C++17 并行算法

#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>
#include <chrono>
#include <random>

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
    constexpr size_t N = 10'000'000;

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
    // 2. sort 对比
    // ═══════════════════════════════════════════════════════
    {
        auto v = data_seq;
        Timer t("sort (sequential)");
        std::sort(v.begin(), v.end());
    }
    {
        auto v = data_seq;
        Timer t("sort (parallel)");
        std::sort(std::execution::par, v.begin(), v.end());
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. accumulate vs reduce
    // ═══════════════════════════════════════════════════════
    {
        Timer t("accumulate (sequential)");
        volatile auto sum = std::accumulate(data_seq.begin(), data_seq.end(), 0LL);
    }
    {
        Timer t("reduce (parallel)");
        volatile auto sum = std::reduce(std::execution::par,
                                        data_seq.begin(), data_seq.end(), 0LL);
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. find_if 对比
    // ═══════════════════════════════════════════════════════
    {
        Timer t("find_if (sequential)");
        auto it = std::find_if(data_seq.begin(), data_seq.end(),
            [](int x) { return x > 999'000; });
    }
    {
        Timer t("find_if (parallel)");
        auto it = std::find_if(std::execution::par, data_seq.begin(), data_seq.end(),
            [](int x) { return x > 999'000; });
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. transform
    // ═══════════════════════════════════════════════════════
    std::vector<int> result_seq(N);
    std::vector<int> result_par(N);
    {
        Timer t("transform (sequential)");
        std::transform(data_seq.begin(), data_seq.end(), result_seq.begin(),
            [](int x) { return x * 2 + 1; });
    }
    {
        Timer t("transform (parallel)");
        std::transform(std::execution::par,
            data_seq.begin(), data_seq.end(), result_par.begin(),
            [](int x) { return x * 2 + 1; });
    }

    std::cout << "\nNote: Parallel algorithms shine with large datasets\n";
    std::cout << "      GCC requires linking with -ltbb for actual parallelism\n";

    return 0;
}
