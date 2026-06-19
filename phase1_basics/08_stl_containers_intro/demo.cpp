// phase1_basics/08_stl_containers_intro/demo.cpp
// 演示：vector, array, map, unordered_map

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <string>

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. std::vector
    // ═══════════════════════════════════════════════════════
    std::vector<int> v;

    // reserve 预分配
    v.reserve(10);
    std::cout << "After reserve(10): size=" << v.size()
              << ", capacity=" << v.capacity() << '\n';

    for (int i = 0; i < 5; ++i) {
        v.emplace_back(i * 10);  // 原地构造
    }
    std::cout << "After push: size=" << v.size()
              << ", capacity=" << v.capacity() << '\n';

    // 遍历
    std::cout << "Elements: ";
    for (const auto& x : v) std::cout << x << ' ';
    std::cout << '\n';

    // 访问
    std::cout << "v[2] = " << v[2] << '\n';
    std::cout << "v.front() = " << v.front() << '\n';
    std::cout << "v.back() = " << v.back() << "\n\n";

    // shrink_to_fit
    v.shrink_to_fit();
    std::cout << "After shrink: capacity=" << v.capacity() << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. std::array —— 定长，栈上
    // ═══════════════════════════════════════════════════════
    std::array<int, 5> arr = {5, 4, 3, 2, 1};
    std::cout << "array size: " << arr.size() << '\n';
    std::cout << "arr[0] = " << arr[0] << ", arr[4] = " << arr[4] << '\n';
    // arr.push_back(6);  // ❌ 编译错误！array 是定长的
    std::cout << "sizeof(array) on stack: " << sizeof(arr) << " bytes\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. std::unordered_map —— 哈希表，O(1) 平均查找
    // ═══════════════════════════════════════════════════════
    std::unordered_map<std::string, int> scores;

    // 插入的几种方式
    scores.try_emplace("Alice", 95);      // C++17：不存在则插入
    scores.try_emplace("Bob", 88);
    scores["Charlie"] = 72;                // 存在则覆盖，不存在则插入

    // 查找
    std::string name = "Bob";
    if (auto it = scores.find(name); it != scores.end()) {
        std::cout << name << ": " << it->second << '\n';
    } else {
        std::cout << name << " not found\n";
    }

    // operator[] 的陷阱：查找不存在的 key 会插入！
    // std::cout << scores["David"]; // 这会插入 David: 0！

    // 遍历（无序）
    std::cout << "All scores (unordered):\n";
    for (const auto& [name, score] : scores) {
        std::cout << "  " << name << ": " << score << '\n';
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. std::map —— 红黑树，有序，O(log n)
    // ═══════════════════════════════════════════════════════
    std::map<std::string, int> ordered_scores;
    ordered_scores["Zoe"] = 100;
    ordered_scores["Alice"] = 85;
    ordered_scores["Bob"] = 92;

    std::cout << "All scores (ordered by key):\n";
    for (const auto& [name, score] : ordered_scores) {
        std::cout << "  " << name << ": " << score << '\n';
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. 容器 vs 裸数组
    // ═══════════════════════════════════════════════════════
    int c_arr[5] = {1, 2, 3, 4, 5};
    // c_arr.size();        // ❌ 裸数组没有 .size()
    // sizeof(c_arr) / sizeof(c_arr[0]) // C 的方式

    std::array<int, 5> cpp_arr = {1, 2, 3, 4, 5};
    std::cout << "cpp_arr.size() = " << cpp_arr.size() << '\n';
    // 传递给函数不会退化为指针！

    return 0;
}
