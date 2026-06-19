// phase1_basics/08_stl_containers_intro/exercise.cpp
// 练习：STL 容器

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <string>
#include <string_view>

// ── 练习 1：用 vector 实现简单的栈 ─────────────────────
// 实现 push, pop（返回 std::optional<int>）, top, empty

// TODO: 实现
// class IntStack {
//     std::vector<int> data_;
// public:
//     void push(int x) { data_.push_back(x); }
//     std::optional<int> pop() { ... }
//     int top() const { ... }
//     bool empty() const { ... }
// };

#include <optional>

// ── 练习 2：词频统计 ───────────────────────────
// 输入一个 string_view，统计每个单词的出现次数
// 返回 unordered_map<string, int>
// 提示：需要手动切分单词（用空格分隔）

// TODO: 实现
// std::unordered_map<std::string, int> word_count(std::string_view text) {
//     // 你的代码
// }

// ── 练习 3：用 array 实现矩阵 ────────────────────
// 用 std::array<std::array<int, 3>, 3> 表示 3x3 矩阵
// 实现矩阵乘法

// TODO: 实现
// using Matrix3x3 = std::array<std::array<int, 3>, 3>;
// Matrix3x3 multiply(const Matrix3x3& a, const Matrix3x3& b) {
//     // 你的代码
// }

// ── 练习 4：合并两个 map ──────────────────────
// 合并两个 unordered_map<string, int>
// 如果 key 冲突，value 相加

// TODO: 实现
// std::unordered_map<std::string, int> merge_scores(
//     const std::unordered_map<std::string, int>& a,
//     const std::unordered_map<std::string, int>& b) {
//     // 你的代码
// }

// ── 练习 5：容器性能意识 ─────────────────────────
// 下面的代码有什么性能问题？如何改进？

void exercise5() {
    std::vector<std::string> log_lines;
    // 模拟：读 1000 行日志
    for (int i = 0; i < 1000; ++i) {
        log_lines.push_back("log line " + std::to_string(i));
        // TODO: 这里有什么问题？如何优化？
    }
    std::cout << "Processed " << log_lines.size() << " lines\n";
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // IntStack s;
    // s.push(10); s.push(20);
    // std::cout << "pop: " << *s.pop() << '\n';
    // std::cout << "top: " << s.top() << '\n';

    // 练习 2:
    // auto wc = word_count("hello world hello c++");
    // for (const auto& [word, count] : wc)
    //     std::cout << word << ": " << count << '\n';

    // 练习 3:
    // Matrix3x3 a = {{{1,2,3},{4,5,6},{7,8,9}}};
    // Matrix3x3 b = {{{9,8,7},{6,5,4},{3,2,1}}};
    // auto c = multiply(a, b);

    // 练习 4:
    // auto merged = merge_scores({{"a",10},{"b",20}}, {{"b",5},{"c",30}});
    // // 期望: a=10, b=25, c=30

    exercise5();
    return 0;
}
