// phase4_templates/01_function_templates/demo.cpp
// 演示：函数模板、参数推导、缩写模板

#include <iostream>
#include <string>
#include <vector>

// ── 1. 基本函数模板 ─────────────────────────────────────
template<typename T>
T max_value(T a, T b) {
    return a > b ? a : b;
}

// ── 2. 多个模板参数 ─────────────────────────────────────
template<typename T1, typename T2>
auto multiply(T1 a, T2 b) {
    return a * b;  // 返回类型自动推导
}

// ── 3. C++20 缩写函数模板 ──────────────────────────────
auto add_abbrev(auto a, auto b) { return a + b; }

// ── 4. 类型萃取 + 模板 ──────────────────────────────────
#include <type_traits>

template<typename T>
std::string classify() {
    if constexpr (std::is_integral_v<T>) {
        return "integer";
    } else if constexpr (std::is_floating_point_v<T>) {
        return "floating-point";
    } else if constexpr (std::is_same_v<T, std::string>) {
        return "string";
    } else {
        return "other";
    }
}

// ── 5. 非类型模板参数 ──────────────────────────────────
template<typename T, size_t N>
constexpr size_t array_size(const T (&)[N]) {
    return N;  // 编译期获取数组大小
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 模板函数使用
    // ═══════════════════════════════════════════════════════
    std::cout << "max(5, 3): " << max_value(5, 3) << '\n';
    std::cout << "max(3.14, 2.72): " << max_value(3.14, 2.72) << '\n';
    std::cout << "max(\"abc\", \"xyz\"): " << max_value("abc", std::string("xyz")) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. 多参数模板 + 返回类型推导
    // ═══════════════════════════════════════════════════════
    auto r1 = multiply(3, 2.5);     // int * double → double
    auto r2 = multiply(4L, 3.14f);  // long * float → double
    std::cout << "multiply(3, 2.5) = " << r1 << '\n';
    std::cout << "multiply(4L, 3.14f) = " << r2 << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. C++20 缩写模板
    // ═══════════════════════════════════════════════════════
    std::cout << "add_abbrev(1, 2) = " << add_abbrev(1, 2) << '\n';
    std::cout << "add_abbrev(1.5, 2.5) = " << add_abbrev(1.5, 2.5) << '\n';
    std::cout << "add_abbrev(s1, s2) = "
              << add_abbrev(std::string("hello "), std::string("world")) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. 类型信息
    // ═══════════════════════════════════════════════════════
    std::cout << "int: " << classify<int>() << '\n';
    std::cout << "double: " << classify<double>() << '\n';
    std::cout << "string: " << classify<std::string>() << '\n';
    std::cout << "vector<int>: " << classify<std::vector<int>>() << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. 非类型模板参数：编译期数组大小
    // ═══════════════════════════════════════════════════════
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    std::cout << "array size: " << array_size(arr) << '\n';
    // 比 sizeof(arr) / sizeof(arr[0]) 安全得多！

    return 0;
}
