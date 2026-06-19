// phase3_stl_algorithms/03_lambda/demo.cpp
// 演示：Lambda 表达式各种用法

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. Lambda 基础
    // ═══════════════════════════════════════════════════════
    auto add = [](int a, int b) { return a + b; };
    std::cout << "add(3, 4) = " << add(3, 4) << '\n';

    // 作为算法参数（lambda 最常见的用途）
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it = std::find_if(v.begin(), v.end(),
        [](int x) { return x > 3; });
    std::cout << "first > 3: " << *it << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. 各种捕获方式
    // ═══════════════════════════════════════════════════════
    int threshold = 5;
    int count = 0;

    std::cout << "threshold = " << threshold << ", count = " << count << '\n';

    // 值捕获：拷贝 threshold
    auto by_value = [threshold](int x) { return x > threshold; };

    // 引用捕获：修改外部 count
    auto by_ref = [&count](int x) { if (x > 0) ++count; };

    // 泛型 lambda（C++14）
    auto twice = [](auto x) { return x + x; };

    std::cout << "by_value(7): " << by_value(7) << '\n';
    by_ref(3); by_ref(-1); by_ref(5);
    std::cout << "count after by_ref calls: " << count << '\n';
    std::cout << "twice(21): " << twice(21) << '\n';
    std::cout << "twice(std::string): " << twice(std::string("ha")) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. mutable lambda
    // ═══════════════════════════════════════════════════════
    int outer = 0;
    auto counter = [outer]() mutable {
        return ++outer;  // 修改的是 lambda 内部的拷贝
    };
    std::cout << "mutable counter: " << counter() << ' '
              << counter() << ' ' << counter() << '\n';
    std::cout << "outer is still: " << outer << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. C++14 广义捕获（移动捕获）
    // ═══════════════════════════════════════════════════════
    auto ptr = std::make_unique<int>(42);
    auto owner = [p = std::move(ptr)]() { return *p; };
    std::cout << "moved unique_ptr: " << owner() << '\n';
    // ptr 现在是 nullptr（已被移动）
    std::cout << "ptr after move: " << (ptr == nullptr) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. Lambda 与排序
    // ═══════════════════════════════════════════════════════
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6};

    // 降序
    std::sort(numbers.begin(), numbers.end(),
        [](int a, int b) { return a > b; });
    std::cout << "descending: ";
    for (int n : numbers) std::cout << n << ' ';
    std::cout << '\n';

    // 按绝对值排序
    std::vector<int> with_neg = {-3, 1, -4, 1, -5, 9};
    std::sort(with_neg.begin(), with_neg.end(),
        [](int a, int b) { return std::abs(a) < std::abs(b); });
    std::cout << "by abs value: ";
    for (int n : with_neg) std::cout << n << ' ';
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 6. std::function vs auto
    // ═══════════════════════════════════════════════════════
    // auto —— 零开销，但每个 lambda 类型不同
    auto lambda1 = [](int x) { return x * 2; };
    auto lambda2 = [](int x) { return x * 3; };
    // lambda1 = lambda2;  // ❌ 编译错误：类型不同！

    // std::function —— 有开销，但可以装不同类型的 lambda
    std::function<int(int)> func = [](int x) { return x * 2; };
    func = [](int x) { return x * 3; };  // ✅ OK
    std::cout << "std::function: " << func(5) << '\n';

    return 0;
}
