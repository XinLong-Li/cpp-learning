// phase1_basics/05_optional/exercise.cpp
// 练习：std::optional

#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// ── 练习 1：安全除法 ────────────────────────────────────
// 实现一个安全的除法：除以 0 或溢出时返回 nullopt

// TODO: 实现 safe_divide
// std::optional<int> safe_divide(int a, int b) {
//     // 考虑：除零？INT_MIN / -1 溢出？
// }

// ── 练习 2：实现 find_first_even ──────────────────────────

// TODO: 实现 find_first_even
// 在 vector<int> 中查找第一个偶数，找到返回它的值，找不到返回 nullopt

// std::optional<int> find_first_even(const std::vector<int>& numbers) {
//     // 你的代码
// }

// ── 练习 3：用 optional 重写以下代码 ─────────────────────
// 下面是一个典型的 "输出参数" 模式，用 optional 重写

// 旧代码：
bool get_user_age(const std::string& name, int& age_out) {
    if (name == "alice") { age_out = 30; return true; }
    if (name == "bob")   { age_out = 25; return true; }
    return false;
}

// TODO: 用 std::optional 重写，消除输出参数
// std::optional<int> get_user_age(const std::string& name) {
//     // 你的代码
// }

// ── 练习 4：实现 find_and_transform ──────────────────────
// 在 vector 中查找满足 predicate 的元素，找到后用 transform 转换它
// 如果没找到，返回 nullopt
// 示范：找到第一个 > 10 的数字，然后把它 * 2

// TODO: 实现 find_and_transform
// 提示：用 std::find_if + 手动应用变换函数

// template<typename Container, typename Predicate, typename Transform>
// auto find_and_transform(const Container& c, Predicate p, Transform t)
//     -> std::optional<decltype(t(*c.begin()))> {
//     // 你的代码
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1 测试：
    // std::cout << "10/2 = " << safe_divide(10, 2).value_or(-1) << '\n';
    // std::cout << "10/0 = " << safe_divide(10, 0).value_or(-1) << '\n';

    // 练习 2 测试：
    // std::vector<int> v = {1, 3, 5, 8, 9};
    // auto even = find_first_even(v);
    // if (even) std::cout << "first even: " << *even << '\n';

    // 练习 3 测试：
    // std::cout << "alice's age: " << get_user_age("alice").value_or(-1) << '\n';
    // std::cout << "charlie's age: " << get_user_age("charlie").value_or(-1) << '\n';

    // 练习 4 测试：
    // std::vector<int> nums = {3, 7, 12, 5, 15};
    // auto result = find_and_transform(nums,
    //     [](int x) { return x > 10; },
    //     [](int x) { return x * 2; });
    // std::cout << "first >10 *2: " << result.value_or(-1) << '\n';

    return 0;
}
