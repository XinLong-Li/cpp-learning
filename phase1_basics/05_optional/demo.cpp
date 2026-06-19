// phase1_basics/05_optional/demo.cpp
// 演示：std::optional 的常见用法

#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <map>

// ── 1. 可能失败的查找 ──────────────────────────────────
std::optional<int> find_value(const std::map<std::string, int>& m,
                               std::string_view key) {
    auto it = m.find(std::string(key));
    if (it != m.end()) {
        return it->second;
    }
    return std::nullopt;  // 明确表达"没找到"
}

// ── 2. 可能失败的解析 ──────────────────────────────────
std::optional<int> parse_int(std::string_view s) {
    try {
        size_t pos;
        int result = std::stoi(std::string(s), &pos);
        if (pos == s.size()) return result;  // 全部解析成功
        return std::nullopt;
    } catch (...) {
        return std::nullopt;
    }
}

// ── 3. 配置项 ─────────────────────────────────────────
struct Config {
    std::optional<std::string> log_file;
    std::optional<int> max_retries;
    std::optional<bool> verbose;
};

void apply_config(const Config& cfg) {
    // value_or 提供默认值
    std::string log = cfg.log_file.value_or("/var/log/app.log");
    int retries = cfg.max_retries.value_or(3);
    bool verbose = cfg.verbose.value_or(false);

    std::cout << "log_file: " << log << '\n';
    std::cout << "max_retries: " << retries << '\n';
    std::cout << "verbose: " << std::boolalpha << verbose << '\n';
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 构造和基础使用
    // ═══════════════════════════════════════════════════════
    std::optional<int> o1;                      // 空
    std::optional<int> o2 = 42;                 // 有值
    std::optional o3 = std::string("hello");    // C++17 CTAD
    std::optional o4 = std::nullopt;            // 显式空

    // ═══════════════════════════════════════════════════════
    // 2. 检查值
    // ═══════════════════════════════════════════════════════
    std::cout << "o1: ";
    if (o1.has_value()) {  // 或 if (o1)
        std::cout << *o1;
    } else {
        std::cout << "empty";
    }
    std::cout << '\n';

    std::cout << "o2: ";
    if (o2) {
        std::cout << *o2 << " (value_or(-1) = " << o2.value_or(-1) << ")";
    }
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 查找用法
    // ═══════════════════════════════════════════════════════
    std::map<std::string, int> scores = {
        {"alice", 95}, {"bob", 88}
    };

    auto alice_score = find_value(scores, "alice");
    std::cout << "alice: " << alice_score.value_or(-1) << '\n';

    auto charlie_score = find_value(scores, "charlie");
    std::cout << "charlie: " << charlie_score.value_or(-1) << " (not found)\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. 解析用法
    // ═══════════════════════════════════════════════════════
    auto n1 = parse_int("123");
    auto n2 = parse_int("12.5");    // 不是纯整数
    auto n3 = parse_int("hello");   // 完全不是数字

    std::cout << "parse_int('123'): " << n1.value_or(-1) << '\n';
    std::cout << "parse_int('12.5'): " << n2.value_or(-1) << '\n';
    std::cout << "parse_int('hello'): " << n3.value_or(-1) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. 配置项用法
    // ═══════════════════════════════════════════════════════
    Config c1 = { .verbose = true };
    std::cout << "Config (partial):\n";
    apply_config(c1);
    std::cout << '\n';

    Config c2 = {
        .log_file = "/tmp/test.log",
        .max_retries = 10,
        .verbose = false
    };
    std::cout << "Config (full):\n";
    apply_config(c2);
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 6. 内存开销
    // ═══════════════════════════════════════════════════════
    std::cout << "sizeof(optional<int>) = " << sizeof(std::optional<int>) << '\n';
    std::cout << "sizeof(int) = " << sizeof(int) << '\n';
    std::cout << "(extra bool + padding, no heap allocation!)\n";

    return 0;
}
