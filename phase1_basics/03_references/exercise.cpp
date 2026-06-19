// phase1_basics/03_references/exercise.cpp
// 练习：引用

#include <iostream>
#include <string>
#include <vector>

// ── 练习 1：找出错误 ─────────────────────────────────────
// 下面的代码中有些行无法编译。请注释掉错误的行，并解释原因。

void exercise1() {
    int a = 10, b = 20;

    int& ref1 = a;       // ✅ 可以编译吗？为什么？
    // int& ref2;        // ❌ 可以编译吗？为什么？
    // int& ref3 = 5;    // ❌ 可以编译吗？为什么？
    const int& ref4 = 5;  // ✅ 可以编译吗？为什么？

    ref1 = b;             // 这是修改 a，还是让 ref1 绑定到 b？

    std::cout << "a = " << a << " (expected 20?)\n";
    std::cout << "b = " << b << '\n';
}

// ── 练习 2：安全的 swap ─────────────────────────────────
// 实现一个 swap 函数，交换两个 int 的值（用引用）
// TODO: 实现 swap(int&, int&)

// void swap(???, ???) {
//     // 你的代码
// }

// ── 练习 3：实现 largest_of_three ─────────────────────────
// 返回三个 std::string 中最大的那个（按字典序）
// 要求：不拷贝任何一个字符串
// TODO: 实现 largest_of_three(const string&, const string&, const string&)

// ??? largest_of_three(???, ???, ???) {
//     // 你的代码
// }

// ── 练习 4：字符串拼接优化 ──────────────────────────────
// 下面的函数效率很低（多次创建临时 string）。请用引用优化它。

std::string bad_concat(const std::string& a, const std::string& b,
                       const std::string& c) {
    return a + b + c;  // 会产生几个临时对象？
}

// TODO: 写一个更好的版本（其实这个已经可以了，RVO 会优化）
// 真正的问题是：如果参数是传递值而非引用，会有更多拷贝

// ── 练习 5：找悬垂引用 ──────────────────────────────────
// 下面的代码中有一处会引发未定义行为，找到它并修复。

// TODO: 审查下面的代码，找出悬垂引用

// const std::string& get_greeting() {
//     return "hello";  // 有问题吗？
// }

// int& get_local() {
//     int x = 42;
//     return x;  // 有问题吗？
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    exercise1();

    // exercise2:
    // int x = 10, y = 20;
    // swap(x, y);
    // std::cout << "x=" << x << ", y=" << y << '\n'; // 期望 x=20, y=10

    // exercise3:
    // std::string a = "apple", b = "banana", c = "cherry";
    // std::cout << "largest: " << largest_of_three(a, b, c) << '\n';

    return 0;
}
