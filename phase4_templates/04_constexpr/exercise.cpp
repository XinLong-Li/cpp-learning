// phase4_templates/04_constexpr/exercise.cpp
// 练习：constexpr、consteval

#include <iostream>
#include <array>
#include <vector>
#include <numeric>

// ── 练习 1：实现 constexpr 斐波那契 ──────────────────────

// TODO: 实现 constexpr fibonacci
// constexpr int fib(int n) { ... }
// static_assert(fib(10) == 55);

// ── 练习 2：constexpr 编译期素数表 ──────────────────────
// 编译期生成前 N 个素数
// 提示：用 constexpr array + constexpr is_prime 函数

// TODO: 实现
// template<size_t N>
// constexpr std::array<int, N> generate_primes() { ... }

// ── 练习 3：consteval vs constexpr ───────────────────
// 为什么下面第二行不能编译？

// constexpr int runtime_val = []() {
//     int x;
//     std::cin >> x;
//     return x;  // ❌：读取 cin 不是 constexpr
// }();

// TODO: 解释 constexpr vs consteval vs constinit 的区别

// ── 练习 4：实现 constexpr 的 is_palindrome ────────────

// TODO: 实现一个 constexpr 函数判断字符串是否是回文
// constexpr bool is_palindrome(std::string_view s) { ... }
// static_assert(is_palindrome("racecar"));
// static_assert(!is_palindrome("hello"));

#include <string_view>

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // constexpr int f20 = fib(20);
    // std::cout << "fib(20) = " << f20 << '\n';

    // 练习 2:
    // constexpr auto primes = generate_primes<10>();
    // for (int p : primes) std::cout << p << ' ';

    return 0;
}
