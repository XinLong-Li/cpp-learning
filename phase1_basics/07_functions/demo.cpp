// phase1_basics/07_functions/demo.cpp
// 演示：函数参数传递、RVO、重载、默认参数、[[nodiscard]]

#include <iostream>
#include <string>
#include <vector>

// ── 1. 不同传递方式 ───────────────────────────────────
void by_value(std::string s) {
    std::cout << "  by_value: '" << s << "' (copied)\n";
}

void by_const_ref(const std::string& s) {
    std::cout << "  by_const_ref: '" << s << "' (no copy, size="
              << s.size() << ")\n";
}

void by_ref(std::string& s) {
    s += "!";
    std::cout << "  by_ref: modified to '" << s << "'\n";
}

// ── 2. RVO 演示 ──────────────────────────────────────
struct Loud {
    std::string name;
    Loud(std::string n) : name(std::move(n)) {
        std::cout << "  [ctor] " << name << '\n';
    }
    Loud(const Loud& other) : name(other.name + " (copy)") {
        std::cout << "  [copy] " << name << '\n';
    }
    Loud(Loud&& other) noexcept : name(std::move(other.name)) {
        std::cout << "  [move] " << name << '\n';
    }
};

Loud make_loud_rvo() {
    Loud l("rvo");
    return l;               // RVO：零拷贝
}

Loud make_loud_broken() {
    Loud l("broken");
    return std::move(l);    // ❌ std::move 破坏 RVO
}

// ── 3. 重载 + 默认参数 ───────────────────────────────
void log_message(const std::string& msg) {
    std::cout << "[INFO] " << msg << '\n';
}

void log_message(const std::string& msg, int severity) {
    const char* prefix = (severity > 0) ? "[ERROR]" : "[INFO]";
    std::cout << prefix << ' ' << msg << '\n';
}

// ── 4. [[nodiscard]] (C++17) ──────────────────────────
[[nodiscard]] int expensive_computation() {
    return 42;
}

[[nodiscard("You probably want to check this result")]
bool try_open(const std::string& path) {
    return path == "valid.txt";
}

// ── 5. Lambda vs std::function ────────────────────────
#include <functional>

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 传递方式
    // ═══════════════════════════════════════════════════════
    std::string s = "hello";
    std::cout << "Original: '" << s << "'\n";
    by_value(s);
    by_const_ref(s);
    by_ref(s);
    std::cout << "After by_ref: '" << s << "'\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. RVO
    // ═══════════════════════════════════════════════════════
    std::cout << "Good RVO:\n";
    auto l1 = make_loud_rvo();     // 只有一次构造！
    std::cout << "l1: " << l1.name << "\n\n";

    std::cout << "Broken (std::move on return):\n";
    auto l2 = make_loud_broken();  // 构造 + 移动
    std::cout << "l2: " << l2.name << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 重载
    // ═══════════════════════════════════════════════════════
    log_message("system started");
    log_message("disk full", 2);
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. [[nodiscard]]
    // ═══════════════════════════════════════════════════════
    expensive_computation();  // 编译器会警告"忽略了返回值"
    int result = expensive_computation();  // OK

    if (try_open("test.txt")) {
        std::cout << "File opened!\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. Lambda
    // ═══════════════════════════════════════════════════════
    auto is_positive = [](int x) { return x > 0; };
    int threshold = 5;
    auto above_threshold = [threshold](int x) { return x > threshold; };

    std::cout << "is_positive(-3): " << is_positive(-3) << '\n';
    std::cout << "is_positive(7): " << is_positive(7) << '\n';
    std::cout << "above_threshold(3, thresh=" << threshold << "): "
              << above_threshold(3) << '\n';
    std::cout << "above_threshold(8, thresh=" << threshold << "): "
              << above_threshold(8) << '\n';

    return 0;
}
