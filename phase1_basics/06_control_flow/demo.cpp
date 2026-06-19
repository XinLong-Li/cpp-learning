// phase1_basics/06_control_flow/demo.cpp
// 演示：if constexpr、带初始化语句的 if、range-for、结构化绑定

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

// ── 1. if constexpr 编译期分支 ──────────────────────────
template<typename T>
auto get_value(T&& val) {
    if constexpr (std::is_pointer_v<std::decay_t<T>>) {
        return *val;      // 非指针类型时此行不会被编译
    } else {
        return val;
    }
}

template<typename T>
std::string type_name() {
    if constexpr (std::is_integral_v<T>)      return "integral";
    else if constexpr (std::is_floating_point_v<T>) return "floating";
    else if constexpr (std::is_same_v<T, std::string>) return "string";
    else return "other";
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. if constexpr
    // ═══════════════════════════════════════════════════════
    int x = 42;
    int* px = &x;
    std::cout << "get_value(x): " << get_value(x) << '\n';
    std::cout << "get_value(px): " << get_value(px) << '\n';
    std::cout << "type_name<int>: " << type_name<int>() << '\n';
    std::cout << "type_name<string>: " << type_name<std::string>() << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. if 带初始化语句 (C++17)
    // ═══════════════════════════════════════════════════════
    std::map<std::string, int> ages = {{"Alice", 30}, {"Bob", 25}};

    // 旧式：it 泄漏到外部作用域
    auto old_it = ages.find("Alice");
    if (old_it != ages.end()) {
        std::cout << "Alice (old): " << old_it->second << '\n';
    }  // old_it 仍然存在

    // C++17：it 的作用域仅限于 if 语句
    if (auto it = ages.find("Alice"); it != ages.end()) {
        std::cout << "Alice (C++17): " << it->second << '\n';
    }  // it 在此销毁

    if (auto it = ages.find("Charlie"); it != ages.end()) {
        std::cout << "Found Charlie\n";
    } else {
        std::cout << "Charlie not found\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. switch 带初始化语句 (C++17)
    // ═══════════════════════════════════════════════════════
    switch (int code = 2; code) {
        case 1: std::cout << "case 1\n"; break;
        case 2: std::cout << "case 2\n"; break;
        default: std::cout << "default\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. Range-based for + 结构化绑定 (C++17)
    // ═══════════════════════════════════════════════════════
    std::map<std::string, std::string> capitals = {
        {"China", "Beijing"},
        {"Japan", "Tokyo"},
        {"France", "Paris"}
    };

    for (const auto& [country, capital] : capitals) {
        std::cout << country << " -> " << capital << '\n';
    }
    std::cout << '\n';

    // 结构化绑定也支持 tuple/pair
    auto [it, inserted] = capitals.insert({"Germany", "Berlin"});
    std::cout << "Germany " << (inserted ? "inserted" : "already exists") << '\n';

    // 也支持自己的 struct
    struct Point { int x; int y; };
    Point p{10, 20};
    auto [px2, py] = p;  // 绑定到成员
    std::cout << "Point: " << px2 << ", " << py << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. 循环的最佳实践
    // ═══════════════════════════════════════════════════════
    std::vector<std::string> words = {"modern", "C++", "is", "great"};

    // 默认：const auto&（只读，不拷贝）
    for (const auto& w : words) {
        std::cout << w << ' ';
    }
    std::cout << '\n';

    // 需要修改元素时：auto&
    for (auto& w : words) {
        w[0] = std::toupper(w[0]);
    }
    std::cout << "Capitalized: ";
    for (const auto& w : words) std::cout << w << ' ';
    std::cout << '\n';

    return 0;
}
