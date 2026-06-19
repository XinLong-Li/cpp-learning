// phase5_cpp17_library/01_variant/exercise.cpp
// 练习：std::variant

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <cmath>

// ── 练习 1：实现安全的计算器 ────────────────────────────
// 用 variant 表示计算结果（int 或 double 或错误消息）

// TODO: 实现
// using CalcResult = std::variant<int, double, std::string>;
//
// CalcResult safe_eval(char op, double a, double b) {
//     switch (op) {
//         case '+': return static_cast<???>(a + b);
//         case '-': return static_cast<???>(a - b);
//         case '*': return static_cast<???>(a * b);
//         case '/':
//             if (b == 0) return std::string("division by zero");
//             return static_cast<???>(a / b);
//         default: return std::string("unknown operator");
//     }
// }

// ── 练习 2：实现 variant_size ───────────────────────────

// TODO: 返回 variant 当前存储的类型的 sizeof
// template<typename... Ts>
// size_t variant_size(const std::variant<Ts...>& v) {
//     return std::visit([](auto&& arg) { return sizeof(arg); }, v);
// }

// ── 练习 3：用 variant 重写 find_value ──────────────────

// TODO: 之前我们用了 std::optional<T> 表示"可能没找到"
// 现在用 variant<T, std::string> 表示"找到"或"错误消息"
// template<typename K, typename V>
// std::variant<V, std::string> get_or_error(
//     const std::map<K, V>& m, const K& key)
// { ... }

#include <map>

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // auto r1 = safe_eval('+', 3, 4);
    // auto r2 = safe_eval('/', 1, 0);
    // std::visit([](auto&& v) { std::cout << v << '\n'; }, r1);
    // std::visit([](auto&& v) { std::cout << v << '\n'; }, r2);

    // 练习 2:
    // std::variant<int, double, std::string> v1 = 42;
    // std::variant<int, double, std::string> v2 = 3.14;
    // std::cout << "size(v1): " << variant_size(v1) << '\n';
    // std::cout << "size(v2): " << variant_size(v2) << '\n';

    return 0;
}
