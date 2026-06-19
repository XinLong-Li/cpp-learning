// phase5_cpp17_library/02_any/demo.cpp
// 演示：std::any 类型擦除

#include <iostream>
#include <any>
#include <string>
#include <vector>
#include <map>

// ── 1. 通用配置容器 ───────────────────────────────────
class ConfigStore {
public:
    template<typename T>
    void set(const std::string& key, T value) {
        store_[key] = std::any(std::move(value));
    }

    template<typename T>
    T get(const std::string& key, T default_val = {}) const {
        auto it = store_.find(key);
        if (it == store_.end()) return default_val;
        try {
            return std::any_cast<T>(it->second);
        } catch (const std::bad_any_cast&) {
            return default_val;
        }
    }

    bool has(const std::string& key) const {
        return store_.find(key) != store_.end();
    }

private:
    std::map<std::string, std::any> store_;
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 基本用法
    // ═══════════════════════════════════════════════════════
    std::any a;

    a = 42;
    std::cout << "a holds int: " << std::any_cast<int>(a) << '\n';

    a = 3.14159;
    std::cout << "a holds double: " << std::any_cast<double>(a) << '\n';

    a = std::string("hello world");
    std::cout << "a holds string: " << std::any_cast<std::string>(a) << '\n';

    // 类型信息
    std::cout << "type: " << a.type().name() << '\n';
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 2. 安全读取
    // ═══════════════════════════════════════════════════════
    a = 42;
    if (auto* p = std::any_cast<int>(&a)) {
        std::cout << "Safe cast int: " << *p << '\n';
    }
    if (auto* p = std::any_cast<std::string>(&a)) {
        std::cout << "Safe cast string: " << *p << '\n';
    } else {
        std::cout << "Not a string! (safe cast returned nullptr)\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. ConfigStore 示例
    // ═══════════════════════════════════════════════════════
    ConfigStore config;
    config.set("timeout", 30);
    config.set("host", std::string("localhost"));
    config.set("ports", std::vector<int>{8080, 8081, 8082});

    std::cout << "timeout: " << config.get<int>("timeout", 60) << '\n';
    std::cout << "host: " << config.get<std::string>("host", "unknown") << '\n';
    std::cout << "missing: " << config.get<int>("missing", -1) << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. 开销
    // ═══════════════════════════════════════════════════════
    std::cout << "\nsizeof(any): " << sizeof(std::any) << '\n';
    std::cout << "(Small types may be stored inline, large types heap-allocated)\n";

    return 0;
}
