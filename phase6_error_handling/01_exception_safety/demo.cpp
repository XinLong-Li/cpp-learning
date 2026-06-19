// phase6_error_handling/01_exception_safety/demo.cpp
// 演示：异常安全、RAII 与异常、noexcept

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

// ── 1. RAII 保证异常安全 ──────────────────────────────
struct Resource {
    std::string name;
    Resource(std::string n) : name(std::move(n)) {
        std::cout << "  Resource(" << name << ") acquired\n";
    }
    ~Resource() {
        std::cout << "  Resource(" << name << ") released\n";
    }
};

void risky_operation(bool should_throw) {
    Resource r1("db_connection");
    Resource r2("file_handle");
    auto data = std::make_unique<int[]>(100);

    std::cout << "  Doing work...\n";
    if (should_throw) {
        throw std::runtime_error("Something went wrong!");
    }
    std::cout << "  Success!\n";
    // r1, r2, data 无论如何都会自动释放
}

// ── 2. noexcept 演示 ──────────────────────────────────
class MoveTracker {
public:
    std::string name;

    MoveTracker(std::string n) : name(std::move(n)) {
        std::cout << "  [ctor] " << name << '\n';
    }

    // 有 noexcept 的移动构造
    MoveTracker(MoveTracker&& other) noexcept
        : name(std::move(other.name)) {
        std::cout << "  [move] " << name << " (noexcept)\n";
    }

    MoveTracker(const MoveTracker& other) : name(other.name + "(copy)") {
        std::cout << "  [copy] " << name << '\n';
    }
};

// ── 3. 自定义异常 ────────────────────────────────────
class ConfigError : public std::runtime_error {
public:
    explicit ConfigError(const std::string& key)
        : std::runtime_error("Config error: " + key), key_(key) {}

    const std::string& key() const { return key_; }

private:
    std::string key_;
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. RAII + 异常
    // ═══════════════════════════════════════════════════════
    std::cout << "=== success case ===\n";
    try {
        risky_operation(false);
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << '\n';
    }
    std::cout << '\n';

    std::cout << "=== failure case ===\n";
    try {
        risky_operation(true);
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << '\n';
        std::cout << "(But all resources were properly released!)\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 2. noexcept 让 vector 扩容用移动而非拷贝
    // ═══════════════════════════════════════════════════════
    std::cout << "=== vector resize with noexcept move ===\n";
    std::vector<MoveTracker> v;
    v.reserve(1);
    v.emplace_back("first");
    std::cout << "Resizing (will move 'first' because move is noexcept):\n";
    v.emplace_back("second");  // 扩容：移动 "first"，不拷贝！
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. 自定义异常
    // ═══════════════════════════════════════════════════════
    try {
        throw ConfigError("database.host");
    } catch (const ConfigError& e) {
        std::cout << "Caught ConfigError: " << e.what() << '\n';
        std::cout << "  missing key: " << e.key() << '\n';
    }

    // ═══════════════════════════════════════════════════════
    // 4. noexcept 检查
    // ═══════════════════════════════════════════════════════
    std::cout << "\nMoveTracker move ctor noexcept: "
              << std::is_nothrow_move_constructible_v<MoveTracker> << '\n';

    return 0;
}
