// phase4_templates/04_constexpr/demo.cpp
// 演示：constexpr、consteval、static_assert

#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <string>

// ── 1. constexpr 函数 ──────────────────────────────────
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

// 编译时常量
constexpr int F10 = factorial(10);
static_assert(F10 == 3628800, "factorial(10) should be 3628800");

// ── 2. constexpr 数据结构 ──────────────────────────────
struct Point {
    int x, y;

    constexpr Point(int x_, int y_) : x(x_), y(y_) {}

    constexpr int manhattan() const { return (x > 0 ? x : -x) + (y > 0 ? y : -y); }

    constexpr Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }
};

constexpr Point p1{3, 4};
constexpr Point p2{1, -2};
constexpr Point p3 = p1 + p2;
static_assert(p3.x == 4 && p3.y == 2);
static_assert(p1.manhattan() == 7);

// ── 3. consteval（强制编译期） ──────────────────────────
consteval int compile_only_sqr(int n) {
    return n * n;
}

// ── 4. constexpr 数组 ──────────────────────────────────
constexpr std::array<int, 10> generate_squares() {
    std::array<int, 10> arr{};
    for (int i = 0; i < 10; ++i) arr[i] = i * i;
    return arr;
}

constexpr auto squares = generate_squares();
static_assert(squares[5] == 25);

// ── 5. 编译期字符串哈希 ────────────────────────────────
constexpr uint32_t hash_string(const char* str, uint32_t h = 0) {
    return *str ? hash_string(str + 1, (h * 31 + *str) & 0xFFFFFFFF) : h;
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. constexpr 运行期也可用
    // ═══════════════════════════════════════════════════════
    std::cout << "factorial(10) (compile-time): " << F10 << '\n';

    int n = 5;
    std::cout << "factorial(" << n << ") (runtime): " << factorial(n) << '\n';
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 2. constexpr Point
    // ═══════════════════════════════════════════════════════
    std::cout << "p1: (" << p1.x << ", " << p1.y << "), manhattan: "
              << p1.manhattan() << '\n';
    std::cout << "p3 = p1 + p2: (" << p3.x << ", " << p3.y << ")\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. consteval
    // ═══════════════════════════════════════════════════════
    constexpr int sq = compile_only_sqr(7);
    std::cout << "consteval sqr(7) = " << sq << '\n';
    // int y = compute_only_sqr(n);  // ❌ 编译错误！n 不是常量
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. 编译期生成数组
    // ═══════════════════════════════════════════════════════
    std::cout << "squares (compile-time generated): ";
    for (int x : squares) std::cout << x << ' ';
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. 编译期字符串哈希
    // ═══════════════════════════════════════════════════════
    constexpr uint32_t h_hello = hash_string("hello");
    constexpr uint32_t h_world = hash_string("world");
    std::cout << "hash('hello') = " << h_hello << '\n';
    std::cout << "hash('world') = " << h_world << '\n';

    // 可以用于 switch！
    std::string input = "hello";
    switch (hash_string(input.c_str())) {
        case hash_string("hello"):
            std::cout << "matched 'hello'!\n"; break;
        case hash_string("world"):
            std::cout << "matched 'world'!\n"; break;
        default:
            std::cout << "no match\n";
    }

    return 0;
}
