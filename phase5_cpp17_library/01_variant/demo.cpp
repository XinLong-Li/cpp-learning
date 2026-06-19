// phase5_cpp17_library/01_variant/demo.cpp
// 演示：std::variant + std::visit

#include <iostream>
#include <variant>
#include <string>
#include <vector>

// ── 1. 用 variant 表示多种返回值 ─────────────────────
using Number = std::variant<int, double>;

Number parse_number(const std::string& s) {
    if (s.find('.') != std::string::npos) {
        return std::stod(s);
    } else {
        return std::stoi(s);
    }
}

// ── 2. 用 visit 统一处理 ─────────────────────────────
void print_number(const Number& n) {
    std::visit([](auto&& val) {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "integer: " << val << " (doubled: " << val * 2 << ")";
        } else {
            std::cout << "floating: " << val;
        }
    }, n);
}

// ── 3. variant 做简单状态机 ───────────────────────────
struct Idle { std::string name; };
struct Running { int progress; };
struct Error { std::string message; };

using State = std::variant<Idle, Running, Error>;

void print_state(const State& state) {
    std::visit([](auto&& s) {
        using T = std::decay_t<decltype(s)>;
        if constexpr (std::is_same_v<T, Idle>) {
            std::cout << "Idle: " << s.name;
        } else if constexpr (std::is_same_v<T, Running>) {
            std::cout << "Running: " << s.progress << "%";
        } else {
            std::cout << "Error: " << s.message;
        }
    }, state);
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 基础操作
    // ═══════════════════════════════════════════════════════
    std::variant<int, double, std::string> v;
    v = 42;
    std::cout << "v holds int: " << std::holds_alternative<int>(v) << '\n';
    std::cout << "value: " << std::get<int>(v) << '\n';

    v = std::string("hello");
    // std::get<int>(v);  // ❌ 抛 std::bad_variant_access
    if (auto* p = std::get_if<std::string>(&v)) {
        std::cout << "safely got string: " << *p << '\n';
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 2. parse_number + visit
    // ═══════════════════════════════════════════════════════
    auto n1 = parse_number("42");
    auto n2 = parse_number("3.14159");

    std::cout << "parse_number('42'): ";
    print_number(n1);
    std::cout << '\n';

    std::cout << "parse_number('3.14159'): ";
    print_number(n2);
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 状态机
    // ═══════════════════════════════════════════════════════
    State state = Idle{"worker"};
    std::cout << "state: "; print_state(state); std::cout << '\n';

    state = Running{42};
    std::cout << "state: "; print_state(state); std::cout << '\n';

    state = Error{"connection lost"};
    std::cout << "state: "; print_state(state); std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. variant 大小
    // ═══════════════════════════════════════════════════════
    std::cout << "\nsizeof(variant<int, double, string>): "
              << sizeof(v) << '\n';
    std::cout << "sizeof(string): " << sizeof(std::string) << '\n';
    std::cout << "(variant adds only the type index overhead, no heap!)\n";

    return 0;
}
