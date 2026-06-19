// phase4_templates/03_concepts_cpp20/exercise.cpp
// 练习：C++20 Concepts

#include <iostream>
#include <concepts>
#include <string>
#include <vector>
#include <algorithm>

// ── 练习 1：定义一个 Incrementable Concept ──────────────

// TODO: 定义 Incrementable concept：要求 ++x 和 x++ 都合法
// template<typename T>
// concept Incrementable = requires(T x) {
//     ++x;
//     x++;
// };

// ── 练习 2：用 Concept 约束 range ─────────────────────

// TODO: 实现一个函数 longest，返回两个对象中"较长"的那个
// 要求参数必须有 .size() 方法，返回整数
// template<??? T>
// T longest(const T& a, const T& b) {
//     return a.size() >= b.size() ? a : b;
// }

// ── 练习 3：判断类型是否支持 + 运算 ───────────────────

// TODO: 定义 Addable concept
// template<typename T>
// concept Addable = requires(T a, T b) {
//     { a + b } -> std::same_as<T>;
// };

// 然后用它约束 sum 函数
// template<Addable T>
// T sum(const std::vector<T>& v) { ... }

// ── 练习 4：requires 表达式探测成员 ──────────────────

// TODO: 写一个探测类型的辅助函数，判断 T 是否有 .name() 方法
// 如果有，用它；否则用 typeid

// template<typename T>
// std::string get_name(const T& obj) {
//     if constexpr (requires { obj.name(); }) {
//         return obj.name();
//     } else {
//         return typeid(T).name();
//     }
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // static_assert(Incrementable<int>);
    // static_assert(!Incrementable<std::string>);

    // 练习 2:
    // std::string s1 = "hello", s2 = "world!";
    // std::cout << "longest: " << longest(s1, s2) << '\n';
    // std::vector<int> v1(3), v2(5);
    // std::cout << "longest: size=" << longest(v1, v2).size() << '\n';

    // 练习 3:
    // std::vector<int> v = {1, 2, 3};
    // std::cout << "sum: " << sum(v) << '\n';

    return 0;
}
