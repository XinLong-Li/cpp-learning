// phase5_cpp17_library/02_any/exercise.cpp
// 练习：std::any

#include <iostream>
#include <any>
#include <string>
#include <vector>
#include <map>

// ── 练习 1：实现 any 容器版的 filter ──────────────────
// 接收 vector<any>，返回所有能转换成 T 的元素

// TODO: 实现
// template<typename T>
// std::vector<T> filter_by_type(const std::vector<std::any>& items) {
//     std::vector<T> result;
//     for (const auto& item : items) {
//         if (auto* p = std::any_cast<T>(&item)) {
//             result.push_back(*p);
//         }
//     }
//     return result;
// }

// ── 练习 2：variant vs optional vs any ─────────────
// 什么场景用什么？用一句话回答下面三个问题：

// Q: 函数可能返回 int，也可能返回"没找到"。用什么？
// A:

// Q: 函数可能返回 int、string 或 Error 三种之一。用什么？
// A:

// Q: 函数返回的类型在编写时完全未知（如脚本引擎的返回值）。用什么？
// A:

// ── 练习 3：实现类型判断 ─────────────────────────────

// TODO: 实现一个函数 is_type<T>(any)，判断 any 是否存储了 T

// template<typename T>
// bool is_type(const std::any& a) {
//     return a.type() == typeid(T);
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // std::vector<std::any> items = {42, std::string("hello"), 100, 200, "world"};
    // auto ints = filter_by_type<int>(items);
    // for (int x : ints) std::cout << x << ' ';  // 42 100 200

    // 练习 3:
    // std::any a = 42;
    // std::cout << "is int: " << is_type<int>(a) << '\n';
    // std::cout << "is string: " << is_type<std::string>(a) << '\n';

    return 0;
}
