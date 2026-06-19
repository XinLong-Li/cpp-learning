// phase1_basics/07_functions/exercise.cpp
// 练习：函数

#include <iostream>
#include <string>
#include <vector>

// ── 练习 1：修复参数传递 ──────────────────────────────
// 下面的函数每次调用都拷贝了 vector，请修复

// TODO: 修改参数类型以避免不必要的拷贝
double average(const std::vector<int>& vec) {
    if (vec.empty()) return 0.0;
    double sum = 0;
    for (int x : vec) sum += x;
    return sum / vec.size();
}

// ── 练习 2：实现 sum 的重载 ─────────────────────────

// TODO: 实现三个版本的 sum
// 1. sum(int, int) -> int
// 2. sum(double, double) -> double
// 3. sum(const vector<int>&) -> int

// ── 练习 3：安全的 find_index 模板 ─────────────────
// 用 [[nodiscard]] 标记，返回 std::optional<size_t>

// TODO: 实现 find_index
// template<typename Container, typename T>
// [[nodiscard]] std::optional<size_t> find_index(...) {
//     // 返回元素在容器中的索引，找不到返回 nullopt
// }

#include <optional>

// ── 练习 4：RVO 验证 ────────────────────────────
// 写一个函数，创建并返回一个包含 3 个元素的 vector<string>
// 验证 RVO 是否生效（思考：怎么验证？）

// TODO:
// std::vector<std::string> make_list() {
//     std::vector<std::string> result = {...};
//     return ???;  // 不要用 std::move！
// }

// ── 练习 5：Lambda 捕获练习 ──────────────────────────
// 实现一个函数 make_multiplier，接收 int factor，返回一个
// lambda，该 lambda 接收 int 并返回 factor * x

// TODO:
// auto make_multiplier(int factor) {
//     return [???](int x) { return ???; };
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // std::vector<int> v = {1, 2, 3, 4, 5};
    // std::cout << "average: " << average(v) << '\n';

    // 练习 2:
    // std::cout << "sum(1,2) = " << sum(1, 2) << '\n';
    // std::cout << "sum(1.5,2.5) = " << sum(1.5, 2.5) << '\n';

    // 练习 3:
    // std::vector<int> v = {10, 20, 30, 40};
    // auto idx = find_index(v, 30);
    // std::cout << "index of 30: " << idx.value_or(-1) << '\n';

    // 练习 5:
    // auto triple = make_multiplier(3);
    // std::cout << "triple(5) = " << triple(5) << '\n';

    return 0;
}
