// phase3_stl_algorithms/02_core_algorithms/exercise.cpp
// 练习：STL 核心算法

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

// ── 练习 1：不用循环，用算法实现 ─────────────────────

// TODO: 用 STL 算法实现以下功能（不写任何 for/while 循环）
void exercise1() {
    std::vector<int> v = {7, 2, -3, 8, -1, 5, 0, 4};

    // a) 判断是否所有元素都 >= 0
    // bool all_non_negative = ???

    // b) 找到第一个负数
    // auto it = ???

    // c) 计算正数的和
    // int positive_sum = ???

    // d) 把所有正数替换为 1，负数替换为 -1
    // ???
}

// ── 练习 2：实现 top_n ──────────────────────────────
// 找到一个 vector 中最大的 n 个元素（用 partial_sort_copy 或 nth_element）

// TODO: 实现
// std::vector<int> top_n(const std::vector<int>& v, size_t n) {
//     // 提示：用 std::partial_sort_copy 或 std::nth_element
// }

// ── 练习 3：用 Erase-Remove 清理数据 ────────────────

// TODO: 实现一个函数，移除 vector<string> 中所有空字符串和纯空格字符串
// void clean_strings(std::vector<std::string>& v) {
//     // 你的代码
//     // 提示：erase + remove_if，条件用 find_first_not_of
// }

// ── 练习 4：累计聚合 ──────────────────────────────
// 给一个 vector<Product> 计算总价（价格 × 数量）

struct Product {
    std::string name;
    double price;
    int quantity;
};

// TODO: 实现
// double total_value(const std::vector<Product>& products) {
//     // 用 std::accumulate
// }

// ── 练习 5：自定义排序 ────────────────────────────────
// 给一个 vector<Student> 排序：先按成绩降序，成绩相同按姓名升序

struct Student {
    std::string name;
    int score;
};

// TODO: 实现
// void sort_students(std::vector<Student>& students) {
//     // 用 std::sort + 自定义比较器
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    exercise1();

    // 练习 2:
    // std::vector<int> v = {3, 7, 1, 9, 2, 8, 4, 6, 5};
    // auto top3 = top_n(v, 3);  // {9, 8, 7}

    // 练习 3:
    // std::vector<std::string> vs = {"hello", "", "  ", "world", "\t"};
    // clean_strings(vs);  // {"hello", "world"}

    // 练习 4:
    // std::vector<Product> cart = {{"apple", 1.0, 3}, {"banana", 0.5, 6}};
    // std::cout << "Total: " << total_value(cart) << '\n';

    // 练习 5:
    // std::vector<Student> students = {{"alice",90},{"bob",85},{"charlie",90}};
    // sort_students(students);

    return 0;
}
