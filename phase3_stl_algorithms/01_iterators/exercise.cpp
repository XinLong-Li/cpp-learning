// phase3_stl_algorithms/01_iterators/exercise.cpp
// 练习：迭代器

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <iterator>

// ── 练习 1：实现 find ────────────────────────────────
// 用迭代器实现一个简单的 find 函数
// 返回指向第一个匹配元素的迭代器，找不到返回 end

// TODO: 实现 my_find
// template<typename Iterator, typename T>
// Iterator my_find(Iterator first, Iterator last, const T& value) {
//     // 你的代码
// }

// ── 练习 2：找出迭代器失效 ──────────────────────────
// 下面的代码中，哪些迭代器在使用时已经失效？

void exercise2() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it1 = v.begin() + 2;   // 指向 3
    auto it2 = v.begin();        // 指向 1

    v.erase(v.begin());         // 删除第一个元素

    // *it1;  // TODO: 安全吗？
    // *it2;  // TODO: 安全吗？

    v.push_back(6);
    v.push_back(7);
    v.push_back(8);            // 可能触发重分配

    // *it1;  // TODO: 安全吗？
}

// ── 练习 3：用反向迭代器找最后一个负数 ─────────────

// TODO: 实现 find_last_negative
// template<typename Container>
// auto find_last_negative(const Container& c) {
//     // 返回指向最后一个负数的迭代器，找不到返回 c.cend()
//     // 提示：用 std::find_if + rbegin/rend
// }

// ── 练习 4：实现 copy_if ──────────────────────────

// TODO: 实现自己的 copy_if
// 提示：遍历源范围，对满足条件的元素写入目标迭代器

// template<typename InputIt, typename OutputIt, typename Predicate>
// OutputIt my_copy_if(InputIt first, InputIt last,
//                     OutputIt dst, Predicate pred) {
//     // 你的代码
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // std::vector<int> v = {10, 20, 30, 40};
    // auto it = my_find(v.begin(), v.end(), 30);
    // if (it != v.end()) std::cout << "Found: " << *it << '\n';

    exercise2();
    return 0;
}
