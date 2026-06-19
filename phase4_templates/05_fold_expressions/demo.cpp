// phase4_templates/05_fold_expressions/demo.cpp
// 演示：C++17 折叠表达式

#include <iostream>
#include <string>
#include <vector>

// ── 1. 求和（右折叠） ───────────────────────────────────
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);  // (1 + (2 + (3 + 4)))
}

// ── 2. 求积（左折叠 + 初始值） ──────────────────────────
template<typename... Args>
auto product(Args... args) {
    return (1 * ... * args);  // (((1 * a1) * a2) * a3)
}

// ── 3. 全部为 true？ ──────────────────────────────────
template<typename... Args>
bool all(Args... args) {
    return (... && args);
}

// ── 4. 任意为 true？ ──────────────────────────────────
template<typename... Args>
bool any(Args... args) {
    return (... || args);
}

// ── 5. 逗号折叠：打印所有参数 ──────────────────────────
template<typename... Args>
void println(Args&&... args) {
    ((std::cout << args << ' '), ...) << '\n';
}

// ── 6. 逗号折叠：批量 push_back ──────────────────────
template<typename Container, typename... Args>
void push_all(Container& c, Args&&... args) {
    (c.push_back(std::forward<Args>(args)), ...);
}

// ── 7. 逗号折叠：依次调用函数 ──────────────────────────
template<typename... Callables>
void call_each(Callables&&... fns) {
    (fns(), ...);
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 算术折叠
    // ═══════════════════════════════════════════════════════
    std::cout << "sum(1, 2, 3, 4, 5) = " << sum(1, 2, 3, 4, 5) << '\n';
    std::cout << "sum(1.5, 2.5, 3.0) = " << sum(1.5, 2.5, 3.0) << '\n';
    std::cout << "product(2, 3, 4) = " << product(2, 3, 4) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. 布尔折叠
    // ═══════════════════════════════════════════════════════
    std::cout << std::boolalpha;
    std::cout << "all(true, true, false) = " << all(true, true, false) << '\n';
    std::cout << "all(true, true, true) = " << all(true, true, true) << '\n';
    std::cout << "any(false, false, true) = " << any(false, false, true) << '\n';
    std::cout << "any(false, false, false) = " << any(false, false, false) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 逗号折叠：打印
    // ═══════════════════════════════════════════════════════
    println("Hello", 42, 3.14, std::string("C++"));
    // 输出：Hello 42 3.14 C++

    // ═══════════════════════════════════════════════════════
    // 4. 逗号折叠：push_all
    // ═══════════════════════════════════════════════════════
    std::vector<int> v;
    push_all(v, 10, 20, 30, 40, 50);
    std::cout << "push_all result: ";
    for (int x : v) std::cout << x << ' ';
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 5. 逗号折叠：call_each
    // ═══════════════════════════════════════════════════════
    int counter = 0;
    call_each(
        [&] { std::cout << "fn1 called; "; ++counter; },
        [&] { std::cout << "fn2 called; "; ++counter; },
        [&] { std::cout << "fn3 called; "; ++counter; }
    );
    std::cout << "\ncounter = " << counter << '\n';

    return 0;
}
