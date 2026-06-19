// phase1_basics/03_references/demo.cpp
// 演示：左值引用、右值引用、传参方式

#include <iostream>
#include <string>
#include <vector>

// ── 按值传递（拷贝） ──────────────────────────────────────
void by_value(std::string s) {
    s += " (modified)";
    std::cout << "  inside by_value: " << s << '\n';
}

// ── 按左值引用传递（可修改原值） ──────────────────────────
void by_ref(std::string& s) {
    s += " (modified)";
    std::cout << "  inside by_ref: " << s << '\n';
}

// ── 按 const 引用传递（只读，不拷贝） ────────────────────
void by_const_ref(const std::string& s) {
    // s += "x";  // ❌ 编译错误：不能修改 const 引用
    std::cout << "  inside by_const_ref: " << s
              << " (size=" << s.size() << ")\n";
}

// ── 右值引用（接管临时对象） ─────────────────────────────
void by_rvalue_ref(std::string&& s) {
    std::string stolen = std::move(s);  // 拿走资源
    stolen += " (stolen)";
    std::cout << "  inside by_rvalue_ref: " << stolen << '\n';
}

// ── 重载：左值版本和右值版本可以共存 ──────────────────────
void consume(const std::string& s) {
    std::cout << "  consume(lvalue): copying...\n";
    std::string copy = s;  // 拷贝
}

void consume(std::string&& s) {
    std::cout << "  consume(rvalue): moving!\n";
    std::string moved = std::move(s);  // 移动（不拷贝）
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 左值引用基础
    // ═══════════════════════════════════════════════════════
    int x = 42;
    int& r = x;
    r = 100;                     // 修改 r 就是修改 x
    std::cout << "x = " << x << " (modified via ref)\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. const 引用绑定规则
    // ═══════════════════════════════════════════════════════
    // int& r1 = 10;             // ❌ 左值引用不能绑定右值
    const int& cr = 10;          // ✅ const 左值引用绑定右值
    // int&& rr1 = x;            // ❌ 右值引用不能绑定左值
    int&& rr2 = 100;             // ✅ 右值引用绑定右值
    std::cout << "const ref: " << cr << ", rvalue ref: " << rr2 << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 传递方式对比
    // ═══════════════════════════════════════════════════════
    std::string original = "hello world";
    std::cout << "original: '" << original << "'\n";

    std::cout << "by_value:\n";
    by_value(original);
    std::cout << "  original after by_value: " << original
              << " (unchanged, was copied)\n\n";

    std::cout << "by_ref:\n";
    by_ref(original);
    std::cout << "  original after by_ref: " << original
              << " (changed!)\n\n";

    std::string copy = original;
    std::cout << "by_const_ref:\n";
    by_const_ref(copy);
    std::cout << "  copy after by_const_ref: " << copy
              << " (unchanged)\n\n";

    std::cout << "by_rvalue_ref (with temporary):\n";
    by_rvalue_ref(std::string("temporary object"));
    std::cout << "  move is cheap - no allocation!\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. 左值/右值重载自动选择
    // ═══════════════════════════════════════════════════════
    std::string s = "data";
    std::cout << "Passing lvalue:\n";
    consume(s);                    // 调用左值版本（拷贝）

    std::cout << "Passing rvalue:\n";
    consume(std::string("temp"));  // 调用右值版本（移动）
    std::cout << "Passing std::move(lvalue):\n";
    consume(std::move(s));         // 调用右值版本（移动），s 内容被移走

    return 0;
}
