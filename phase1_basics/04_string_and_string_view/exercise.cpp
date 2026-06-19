// phase1_basics/04_string_and_string_view/exercise.cpp
// 练习：string 与 string_view

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// ── 练习 1：用 string_view 改写 ─────────────────────────
// 下面的函数只接收 const string&，改写它以接收 string_view
// 这样调用者可以传入 string、string_view、const char* 等任意东西

// 原函数
bool is_prefix_of(const std::string& prefix, const std::string& text) {
    if (prefix.size() > text.size()) return false;
    return text.compare(0, prefix.size(), prefix) == 0;
}

// TODO: 用 string_view 改写
// bool is_prefix_of(...) { ... }

// ── 练习 2：安全的 string_view 工厂 ─────────────────────

// TODO: 审查下面代码中的 string_view 使用，找出潜在的悬垂问题
// 并修复它们

void exercise2() {
    std::string_view bad_view;  // HINT: 悬垂吗？

    {
        std::string temp = "I will be destroyed soon";
        bad_view = temp;  // HINT: 有问题吗？
    }
    // 这里 bad_view 指向的 temp 已经被销毁了！

    // std::cout << bad_view << '\n'; // ❌ 如果取消注释，会发生什么？
}

// ── 练习 3：实现 split 函数 ──────────────────────────
// 用 string_view 实现一个零拷贝的 split
// 输入 "a,b,c" → 返回 {"a", "b", "c"}
// 不要分配任何新的字符串内存！

// TODO: 实现 split
// std::vector<std::string_view> split(std::string_view str, char delimiter) {
//     // 你的代码
//     // 提示：用 find 和 substr (string_view 的 substr 不拷贝!)
// }

// ── 练习 4：trim 实现 ─────────────────────────────────

// TODO: 实现 trim_left, trim_right, trim
// 去掉字符串首尾的空白字符，返回 string_view（零拷贝！）
// 提示：用 find_first_not_of / find_last_not_of

// std::string_view trim(std::string_view s) {
//     // 去掉开头和结尾的 " \t\n\r"
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1 测试:
    // std::cout << is_prefix_of("hello", "hello world") << '\n'; // 1
    // std::cout << is_prefix_of("world", "hello world") << '\n'; // 0

    exercise2();

    // 练习 3 测试:
    // auto parts = split("apple,banana,cherry", ',');
    // for (auto p : parts) std::cout << "[" << p << "] ";
    // std::cout << '\n';

    // 练习 4 测试:
    // std::cout << "[" << trim("  hello  ") << "]\n"; // [hello]
    return 0;
}
