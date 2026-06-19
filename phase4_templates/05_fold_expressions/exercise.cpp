// phase4_templates/05_fold_expressions/exercise.cpp
// 练习：折叠表达式

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ── 练习 1：实现 max_of ──────────────────────────────
// 返回所有参数中最大的

// TODO: 用折叠表达式实现
// template<typename T, typename... Args>
// T max_of(T first, Args... rest) {
//     // 提示：用三元运算符 + 折叠
// }

// ── 练习 2：实现 min_of ─────────────────────────────

// TODO: 用折叠表达式实现 min_of

// ── 练习 3：实现 for_each_arg ──────────────────────
// 对每个参数调用同一个函数

// template<typename F, typename... Args>
// void for_each_arg(F&& f, Args&&... args) {
//     (f(std::forward<Args>(args)), ...);
// }

// ── 练习 4：收集满足条件的参数 ──────────────────────
// 实现 filter_args，收集满足 predicate 的参数到 vector

// TODO: 实现
// template<typename Pred, typename... Args>
// auto filter_args(Pred pred, Args&&... args) {
//     std::vector<std::common_type_t<Args...>> result;
//     // 用折叠表达式 + if
//     ((pred(args) ? result.push_back(args) : void()), ...);
//     return result;
// }

// ── 练习 5：is_homogeneous ─────────────────────────
// 判断所有参数是否是同一类型
// 提示：用折叠表达式 + std::is_same_v

// template<typename T, typename... Args>
// constexpr bool is_homogeneous(T, Args...) {
//     return (std::is_same_v<T, Args> && ...);
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // std::cout << "max_of(3, 7, 2, 9, 1): " << max_of(3, 7, 2, 9, 1) << '\n'; // 9

    // 练习 3:
    // for_each_arg([](auto x) { std::cout << x << ' '; }, 1, "hello", 3.14);

    // 练习 4:
    // auto v = filter_args([](int x) { return x > 5; }, 3, 7, 1, 9, 2, 8);
    // for (int x : v) std::cout << x << ' ';  // 7 9 8

    // 练习 5:
    // static_assert(is_homogeneous(1, 2, 3));
    // static_assert(!is_homogeneous(1, 2.0, 3));

    return 0;
}
