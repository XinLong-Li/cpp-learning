// phase4_templates/01_function_templates/exercise.cpp
// 练习：函数模板

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

// ── 练习 1：实现通用的 min 模板 ────────────────────────

// TODO: 实现 min 模板（不能用 <，要用 > 或者自定义比较）
// 考虑：要支持 int, double, string 等

// ── 练习 2：实现 print_container ───────────────────────
// 接收任意容器（有 begin/end），打印所有元素

// TODO: 实现 print_container
// template<typename Container>
// void print_container(const Container& c, const char* sep = " ") {
//     // 你的代码
// }

// ── 练习 3：实现 are_equal ─────────────────────────
// 一个模板函数，接收两个任意类型的参数
// 如果类型不同，直接返回 false
// 如果类型相同，比较值

// TODO: 实现
// template<typename T, typename U>
// bool are_equal(const T& a, const U& b) {
//     if constexpr (std::is_same_v<T, U>) {
//         return a == b;
//     } else {
//         return false;
//     }
// }

// ── 练习 4：用缩写模板重写 ──────────────────────────

// 将下面的函数用 C++20 缩写模板重写
template<typename T>
T double_value(T x) { return x + x; }

// TODO: 用 auto 参数重写
// auto double_value_v2(auto x) { return ...; }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 2:
    // std::vector<int> v = {1, 2, 3};
    // print_container(v);  // "1 2 3"
    // std::vector<std::string> s = {"a", "b"};
    // print_container(s, ", ");  // "a, b"

    // 练习 3:
    // std::cout << are_equal(1, 1) << ' ';      // true
    // std::cout << are_equal(1, 1.0) << ' ';    // false (type mismatch)
    // std::cout << are_equal(5, 3) << '\n';     // false

    return 0;
}
