// phase1_basics/01_types_and_auto/demo.cpp
// 演示：基本类型、auto 类型推导

#include <iostream>
#include <string>
#include <vector>
#include <map>

// ── 辅助函数 ─────────────────────────────────────────────
const int& get_const_ref() {
    static int value = 42;
    return value;
}

int get_value() { return 100; }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 基本类型
    // ═══════════════════════════════════════════════════════
    int i = 42;             // 默认整数
    double d = 3.14159;     // 默认浮点
    bool b = true;          // 布尔
    size_t n = 100;         // 容器大小/索引
    char c = 'A';           // 单个字符

    std::cout << "int: " << i << ", sizeof: " << sizeof(i) << " bytes\n";
    std::cout << "double: " << d << ", sizeof: " << sizeof(d) << " bytes\n";
    std::cout << "bool: " << b << ", sizeof: " << sizeof(b) << " bytes\n";
    std::cout << "size_t: " << n << ", sizeof: " << sizeof(n) << " bytes\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. auto 基本用法
    // ═══════════════════════════════════════════════════════
    auto ai = 42;            // int
    auto ad = 3.14159;       // double
    auto ab = true;          // bool
    auto as = std::string("hello"); // std::string

    // auto 在迭代器场景下最有用
    std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};
    // 不用 auto：std::map<std::string, int>::const_iterator
    auto it = ages.find("Alice");  // 简洁！

    // ═══════════════════════════════════════════════════════
    // 3. auto 剥除规则
    // ═══════════════════════════════════════════════════════
    auto x1 = get_const_ref();   // x1 是 int（剥除了 const 和 &）
    x1 = 999;                    // OK，x1 是一个独立的 int

    auto& x2 = get_const_ref();  // x2 是 const int&（保留了引用）
    // x2 = 999;                 // ❌ 编译错误！x2 是 const 引用

    const auto& x3 = get_value(); // x3 是 const int&（绑定到临时对象，生命周期延长）

    std::cout << "x1 (auto, stripped): " << x1 << '\n';
    std::cout << "x2 (auto&, kept ref): " << x2 << '\n';
    std::cout << "x3 (const auto&, lifetime extended): " << x3 << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. Range-based for 中的 auto
    // ═══════════════════════════════════════════════════════
    std::vector<std::string> words = {"hello", "world", "c++"};

    std::cout << "By value (copies): ";
    for (auto word : words) {        // 每次循环拷贝一个 string
        std::cout << word << " ";
    }
    std::cout << '\n';

    std::cout << "By const ref (no copy): ";
    for (const auto& word : words) { // 不拷贝，推荐写法
        std::cout << word << " ";
    }
    std::cout << '\n';

    std::cout << "By ref (mutable): ";
    for (auto& word : words) {       // 不拷贝，可修改
        word[0] = toupper(word[0]);  // 首字母大写
        std::cout << word << " ";
    }
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. 陷阱：auto 和 initializer_list
    // ═══════════════════════════════════════════════════════
    auto il = {1, 2, 3};           // std::initializer_list<int>，不是 vector！
    std::cout << "auto x = {1,2,3} -> type: initializer_list, size: "
              << il.size() << '\n';

    // 明确你想要什么：
    std::vector<int> v = {1, 2, 3}; // 这才是 vector

    return 0;
}
