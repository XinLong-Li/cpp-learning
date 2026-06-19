// phase1_basics/04_string_and_string_view/demo.cpp
// 演示：std::string 与 std::string_view

#include <iostream>
#include <string>
#include <string_view>

// ── 用 string_view 做参数（零开销） ───────────────────────
int count_words(std::string_view text) {
    if (text.empty()) return 0;
    int count = 0;
    bool in_word = false;
    for (char c : text) {
        if (c == ' ' || c == '\n' || c == '\t') {
            in_word = false;
        } else if (!in_word) {
            in_word = true;
            ++count;
        }
    }
    return count;
}

// ── 零拷贝解析 ──────────────────────────────────────────
void parse_key_value(std::string_view line) {
    auto eq = line.find('=');
    if (eq != std::string_view::npos) {
        std::string_view key = line.substr(0, eq);
        std::string_view value = line.substr(eq + 1);
        std::cout << "  key='" << key << "', value='" << value << "'\n";
    }
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 构造方式对比
    // ═══════════════════════════════════════════════════════
    std::string s1 = "hello world";
    std::string s2("direct init");
    std::string s3(5, 'x');                  // "xxxxx"

    std::string_view sv1 = "literal";        // 直接指向字面量
    std::string_view sv2 = s1;               // 指向 s1 的数据
    std::string_view sv3(s1.data(), 5);      // 只取前 5 个字符 "hello"

    std::cout << "s1: " << s1 << '\n';
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s3: " << s3 << '\n';
    std::cout << "sv1: " << sv1 << '\n';
    std::cout << "sv2: " << sv2 << '\n';
    std::cout << "sv3 (first 5 chars): " << sv3 << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. substr 对比
    // ═══════════════════════════════════════════════════════
    std::string big(10000, 'a');
    // string::substr - 拷贝！分配新内存
    std::string small = big.substr(0, 5);     // 从10000字符中取5个 → 分配
    // string_view::substr - 零拷贝！只是调整视图窗口
    std::string_view big_view(big);
    std::string_view small_view = big_view.substr(0, 5); // 零分配
    std::cout << "string substr: " << small << '\n';
    std::cout << "string_view substr: " << small_view << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 函数参数：string、const string&、string_view
    // ═══════════════════════════════════════════════════════
    std::string text = "the quick brown fox";
    std::cout << "count_words(string_view): "
              << count_words(text) << '\n';              // ✅ 隐式转换
    std::cout << "count_words(literal): "
              << count_words("one two three") << '\n';   // ✅ 直接指向字面量
    std::cout << "count_words(substr): "
              << count_words(text) << "\n\n";  // ✅ 不需要构造临时 string

    // ═══════════════════════════════════════════════════════
    // 4. 零拷贝解析
    // ═══════════════════════════════════════════════════════
    std::string_view config = "host=localhost\nport=8080\nmode=debug";
    size_t pos = 0;
    while (pos < config.size()) {
        auto end = config.find('\n', pos);
        if (end == std::string_view::npos) end = config.size();
        parse_key_value(config.substr(pos, end - pos));
        pos = end + 1;
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. SSO（小字符串优化）
    // ═══════════════════════════════════════════════════════
    std::string tiny = "hi";
    std::string huge(100, 'x');
    std::cout << "sizeof(string) = " << sizeof(s1) << '\n';
    std::cout << "sizeof(string_view) = " << sizeof(sv1) << '\n';
    std::cout << "tiny capacity: " << tiny.capacity()
              << " (no heap if <= " << sizeof(s1) - 1 << ")\n";

    return 0;
}
