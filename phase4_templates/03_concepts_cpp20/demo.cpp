// phase4_templates/03_concepts_cpp20/demo.cpp
// 演示：C++20 Concepts

#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <type_traits>

// ── 1. 使用标准 Concepts ────────────────────────────────
template<std::integral T>
T gcd(T a, T b) {
    while (b != 0) {
        T t = b;
        b = a % b;
        a = t;
    }
    return a;
}

template<std::floating_point T>
auto safe_sqrt(T x) -> T {
    return x >= 0 ? std::sqrt(x) : T{0};
}

// ── 2. 自定义 Concept ──────────────────────────────────
template<typename T>
concept Printable = requires(T x, std::ostream& os) {
    { os << x } -> std::same_as<std::ostream&>;
};

template<Printable T>
void print(const T& value) {
    std::cout << "[Printable] " << value << '\n';
}

// 没有 << 的类型不能用 print
// print(std::vector<int>{1,2,3});  // ❌ 编译错误，信息清晰！

// ── 3. 组合 Concepts ───────────────────────────────────
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
T square(T x) { return x * x; }

// ── 4. requires 表达式检查 ─────────────────────────────
template<typename T>
concept ContainerLike = requires(T c) {
    typename T::value_type;        // 有 value_type
    c.begin();                     // 有 begin()
    c.end();                       // 有 end()
    c.size();                      // 有 size()
};

template<ContainerLike C>
void print_size(const C& container) {
    std::cout << "Container size: " << container.size() << '\n';
}

// ── 5. requires 子句做编译期分支 ─────────────────────────
template<typename T>
std::string describe(const T& val) {
    if constexpr (requires { std::to_string(val); }) {
        return "has to_string: " + std::to_string(val);
    } else if constexpr (requires { std::to_string(val.size()); }) {
        return "has size: " + std::to_string(val.size()) + " elements";
    } else {
        return "no description available";
    }
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. Concepts 约束
    // ═══════════════════════════════════════════════════════
    std::cout << "gcd(48, 18) = " << gcd(48, 18) << '\n';
    // gcd(1.5, 2.5);  // ❌ 编译错误：double 不满足 integral
    std::cout << "safe_sqrt(9.0) = " << safe_sqrt(9.0) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. 自定义 Concept
    // ═══════════════════════════════════════════════════════
    print(42);
    print(3.14);
    print(std::string("hello"));
    // print(std::vector{1, 2, 3});  // ❌ vector 没有 <<
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. 组合 Concepts
    // ═══════════════════════════════════════════════════════
    std::cout << "square(5) = " << square(5) << '\n';
    std::cout << "square(3.14) = " << square(3.14) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. ContainerLike
    // ═══════════════════════════════════════════════════════
    std::vector<int> v = {1, 2, 3, 4, 5};
    print_size(v);
    // print_size(42);  // ❌ int 不满足 ContainerLike
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. requires 分支
    // ═══════════════════════════════════════════════════════
    std::cout << describe(42) << '\n';
    std::cout << describe(v) << '\n';

    return 0;
}
