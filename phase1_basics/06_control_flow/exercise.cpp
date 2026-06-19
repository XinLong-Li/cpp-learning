// phase1_basics/06_control_flow/exercise.cpp
// 练习：现代 C++ 控制流

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <type_traits>

// ── 练习 1：用 if constexpr 实现通用打印 ─────────────────
// 实现 print_value，对整数直接打印，对字符串加引号，对其他类型打印 "?"

// TODO: 实现 print_value
// template<typename T>
// void print_value(const T& val) {
//     if constexpr (...) { ... }
//     else if constexpr (...) { ... }
//     else { ... }
// }

// ── 练习 2：用带初始化的 if 改写代码 ──────────────────────
// 下面是旧式代码，用 C++17 带初始化的 if 改写

void exercise2() {
    std::map<int, std::string> students = {
        {1, "Alice"}, {2, "Bob"}, {3, "Charlie"}
    };

    // TODO: 用 if (auto it = ...; it != ...) 改写

    // 旧代码：
    auto it1 = students.find(2);
    if (it1 != students.end()) {
        std::cout << "Found: " << it1->second << '\n';
    }

    auto it2 = students.find(5);
    if (it2 != students.end()) {
        std::cout << "Found: " << it2->second << '\n';
    }
}

// ── 练习 3：结构化绑定练习 ──────────────────────────────

void exercise3() {
    // TODO: 用结构化绑定遍历下面的 map
    // for (const auto& [???] : ...)

    std::map<std::string, double> prices = {
        {"apple", 1.2}, {"banana", 0.8}, {"cherry", 2.5}
    };

    // 你的遍历代码：
}

// ── 练习 4：实现 for_each_arg ──────────────────────────
// 用折叠表达式（C++17）实现一个函数，对每个参数调用 f
// for_each_arg([](auto x) { cout << x << " "; }, 1, "hello", 3.14);

// TODO:
// template<typename F, typename... Args>
// void for_each_arg(F&& f, Args&&... args) {
//     (f(std::forward<Args>(args)), ...);
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // exercise1:
    // print_value(42);
    // print_value(std::string("hello"));
    // print_value(3.14);

    exercise2();
    exercise3();

    // exercise4:
    // for_each_arg([](auto x) { std::cout << x << " "; }, 1, "hello", 3.14);

    return 0;
}
