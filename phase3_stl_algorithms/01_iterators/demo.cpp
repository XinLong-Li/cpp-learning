// phase3_stl_algorithms/01_iterators/demo.cpp
// 演示：迭代器类别、操作、失效问题

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 基本迭代器操作
    // ═══════════════════════════════════════════════════════
    std::vector<int> v = {10, 20, 30, 40, 50};

    std::cout << "Forward: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    std::cout << "Reverse: ";
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
        std::cout << *rit << ' ';
    }
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. 不同容器的迭代器能力
    // ═══════════════════════════════════════════════════════
    std::vector<int> rvec = {1, 2, 3, 4, 5};
    std::list<int> lst = {1, 2, 3, 4, 5};

    // RandomAccess 迭代器支持 +n
    std::cout << "vector[3] via iterator: " << *(rvec.begin() + 3) << '\n';

    // Bidirectional 迭代器不支持 +n
    // auto x = *(lst.begin() + 3);  // ❌ 编译错误！
    auto lit = lst.begin();
    ++lit; ++lit; ++lit;
    std::cout << "list[3] via 3x++: " << *lit << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 插入迭代器
    // ═══════════════════════════════════════════════════════
    std::vector<int> src = {1, 2, 3};
    std::vector<int> dst;

    std::copy(src.begin(), src.end(), std::back_inserter(dst));
    std::cout << "After back_inserter: ";
    for (int x : dst) std::cout << x << ' ';
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. 迭代器失效演示（vector）
    // ═══════════════════════════════════════════════════════
    std::vector<int> v2 = {1, 2, 3};
    std::cout << "Before push: capacity=" << v2.capacity() << '\n';

    auto it2 = v2.begin();           // it2 指向 v2[0]
    std::cout << "*it2 = " << *it2 << '\n';

    v2.push_back(4);                 // 可能重分配！
    // 如果 capacity 从 3 变成 6，内存移动了
    // *it2 = 100;                   // ❌ 未定义行为！

    // 安全做法：重新获取迭代器
    it2 = v2.begin();
    *it2 = 100;
    std::cout << "*it2 after re-fetch = " << *it2 << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. map 删除不失效其他迭代器
    // ═══════════════════════════════════════════════════════
    std::map<int, std::string> m = {{1, "a"}, {2, "b"}, {3, "c"}};
    auto it_a = m.find(1);
    m.erase(2);   // 删除 key=2

    // it_a 仍然有效！
    std::cout << "After erase(2), it_a->second = " << it_a->second << '\n';

    // ═══════════════════════════════════════════════════════
    // 6. 流迭代器
    // ═══════════════════════════════════════════════════════
    std::istringstream iss("100 200 300 400");
    std::vector<int> numbers(
        std::istream_iterator<int>(iss),
        std::istream_iterator<int>()
    );
    std::cout << "From string stream: ";
    for (int n : numbers) std::cout << n << ' ';
    std::cout << '\n';

    return 0;
}

// Needed for istringstream
#include <sstream>
