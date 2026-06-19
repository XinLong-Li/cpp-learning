// phase5_cpp17_library/03_structured_bindings/exercise.cpp
// 练习：结构化绑定

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <array>

// ── 练习 1：用结构化绑定实现 minmax3 ─────────────────
// 返回三个数的最小值和最大值
// 返回类型用 tuple 或 pair

// TODO: 实现
// std::tuple<int, int> minmax3(int a, int b, int c) {
//     auto [lo, hi] = std::minmax({a, b, c});
//     return {lo, hi};
// }
// 然后用结构化绑定接收

// ── 练习 2：重构下面的循环 ───────────────────────
// 用结构化绑定 + range-for 重写

void exercise2() {
    std::map<std::string, std::vector<int>> student_scores = {
        {"Alice", {95, 88, 92}},
        {"Bob", {78, 85, 80}},
        {"Charlie", {90, 91, 89}}
    };

    // TODO: 用结构化绑定重写这个循环
    // 旧写法：
    for (const auto& entry : student_scores) {
        const auto& name = entry.first;
        const auto& scores = entry.second;
        int total = 0;
        for (int s : scores) total += s;
        double avg = static_cast<double>(total) / scores.size();
        std::cout << name << " average: " << avg << '\n';
    }
}

// ── 练习 3：实现 insert_or_update ──────────────────

// TODO: 用结构化绑定接收 insert 的返回值

// ── 练习 4：struct 与结构化绑定 ───────────────────

struct Vector3 { double x, y, z; };

// TODO: 实现 dot_product (用结构化绑定)

// double dot_product(const Vector3& a, const Vector3& b) {
//     auto [ax, ay, az] = a;
//     auto [bx, by, bz] = b;
//     return ax * bx + ay * by + az * bz;
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // auto [lo, hi] = minmax3(7, 2, 9);
    // std::cout << "minmax3(7,2,9) → min=" << lo << " max=" << hi << '\n';

    exercise2();

    // 练习 4:
    // Vector3 v1{1, 0, 0}, v2{0, 1, 0};
    // std::cout << "dot = " << dot_product(v1, v2) << '\n'; // 0

    return 0;
}
