// phase1_basics/02_const_and_constexpr/demo.cpp
// 演示：const, constexpr, if constexpr

#include <iostream>
#include <string>
#include <type_traits>

// ═══════════════════════════════════════════════════════════
// 1. constexpr 函数 —— 编译期和运行期都能用
// ═══════════════════════════════════════════════════════════
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

// C++20: constexpr 容器
constexpr int sum_of_first_n(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

// ═══════════════════════════════════════════════════════════
// 2. if constexpr —— 编译期分支
// ═══════════════════════════════════════════════════════════
template<typename T>
std::string describe(const T& val) {
    if constexpr (std::is_integral_v<T>) {
        return "int: " + std::to_string(val);
    } else if constexpr (std::is_floating_point_v<T>) {
        return "float: " + std::to_string(val);
    } else if constexpr (std::is_same_v<T, std::string>) {
        return "string: \"" + val + "\"";
    } else {
        return "unknown type";
    }
}

// ═══════════════════════════════════════════════════════════
// 3. const 成员函数
// ═══════════════════════════════════════════════════════════
class Counter {
    int count_ = 0;
public:
    void increment() { ++count_; }           // 非 const：修改对象
    int value() const { return count_; }     // const：只读

    // 重载：const 和非 const 可以共存
    const std::string& tag() const {
        static std::string s = "const";
        return s;
    }
    std::string& tag() {
        static std::string s = "non-const";
        return s;
    }
};

// ═══════════════════════════════════════════════════════════
// 主函数
// ═══════════════════════════════════════════════════════════
int main() {
    // ── constexpr 变量 ──────────────────────────────────
    constexpr int compile_time = factorial(10);   // 编译期求值
    std::cout << "factorial(10) = " << compile_time << '\n';
    std::cout << "sum(100) = " << sum_of_first_n(100) << '\n';

    int n = 5;
    std::cout << "factorial(" << n << ") = " << factorial(n)
              << " (runtime)\n\n";

    // ── const 三种读法 ─────────────────────────────────
    int x = 10;
    const int* p1 = &x;      // p1 指向 const int
    int const* p2 = &x;      // 同上
    int* const p3 = &x;      // p3 是 const 指针
    const int* const p4 = &x; // 指针和值都 const

    // *p1 = 20;             // ❌ 编译错误，指向的内容不可改
    x = 20;                  // ✅ 直接通过 x 改没问题
    // p3 = &n;              // ❌ 编译错误，p3 本身不可改
    *p3 = 30;                // ✅ p3 指向的内容可以改（x 不是 const）
    std::cout << "x = " << x << "\n\n";

    // ── if constexpr ───────────────────────────────────
    std::cout << describe(42) << '\n';
    std::cout << describe(3.14) << '\n';
    std::cout << describe(std::string("hello")) << '\n';
    std::cout << describe(true) << "\n\n";

    // ── const 成员函数重载 ─────────────────────────────
    Counter c;
    const Counter& cc = c;

    std::cout << "non-const tag: " << c.tag() << '\n';   // 调用非 const 版
    std::cout << "const tag: " << cc.tag() << '\n';       // 调用 const 版

    c.increment();
    std::cout << "value: " << c.value() << '\n';          // const 成员函数
    // cc.increment();  // ❌ cc 是 const 引用，不能调用非 const 函数

    return 0;
}
