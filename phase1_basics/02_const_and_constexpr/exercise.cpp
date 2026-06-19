// phase1_basics/02_const_and_constexpr/exercise.cpp
// 练习：const 与 constexpr

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

// ── 练习 1：读 const 声明 ──────────────────────────────────
// 写出下面每个变量的含义（指针本身可改？指向的内容可改？）

void exercise1() {
    int val = 42;

    const int a = 10;          // TODO: 含义：a 是 _______（本身不可改）
    int* p1 = &val;            // TODO: 含义：_______ 可改，_______ 可改
    const int* p2 = &val;      // TODO: 含义：_______ 可改，_______ 不可改
    int* const p3 = &val;      // TODO: 含义：_______ 不可改，_______ 可改
    const int* const p4 = &val; // TODO: 含义：_______ 不可改，_______ 不可改

    std::cout << "Exercise 1: answer in comments above.\n";
}

// ── 练习 2：用 constexpr 替换宏 ───────────────────────────
// 下面是 C 风格的代码，用 constexpr 替换掉所有的 #define

#define MAX_STUDENTS 50
#define PASSING_SCORE 60
#define PI_APPROX 3.14

// TODO: 用 constexpr 重写上面的三个常量，类型要精确：
// MAX_STUDENTS -> size_t 或 int
// PASSING_SCORE -> int
// PI_APPROX -> double

// constexpr ...

// ── 练习 3：实现 constexpr 函数 ──────────────────────────

// TODO: 实现 constexpr 版本的 is_prime
// 提示：constexpr 函数在 C++14 之后可以包含循环和多个 return

// constexpr bool is_prime(int n) {
//     // 你的代码
// }

// static_assert(is_prime(2), "2 is prime");
// static_assert(is_prime(7), "7 is prime");
// static_assert(!is_prime(1), "1 is not prime");
// static_assert(!is_prime(4), "4 is not prime");

// ── 练习 4：increment_if 函数 ────────────────────────────

// TODO: 实现一个函数 increment_if，接收一个 int& 和一个条件布尔值
// 如果条件为 true，increment 这个 int
// 这演示了：接收可修改引用 &，但不修改的用 const &

// void increment_if(???, ???) {
//     if (condition) { ... }
// }

// ── 练习 5：用 if constexpr 实现编译期分支 ────────────────

// TODO: 实现一个函数模板 print_elements，用 if constexpr
// 判断容器是否是 const 可迭代的，相应地打印 "[const] " 前缀

// template<typename Container>
// void print_elements(const Container& c) {
//     // 提示：std::is_const_v<std::remove_reference_t<decltype(*c.begin())>>
//     // 检查解引用迭代器得到的元素是否是 const
//     ...
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    exercise1();

    // 练习 3 验证：
    // std::cout << "is_prime(7): " << is_prime(7) << '\n';
    // std::cout << "is_prime(15): " << is_prime(15) << '\n';

    // 练习 4 验证：
    // int score = 50;
    // increment_if(score, true);
    // std::cout << "score after inc: " << score << '\n';

    // 练习 5 验证：
    // std::vector<int> v = {1, 2, 3};
    // print_elements(v);

    return 0;
}
