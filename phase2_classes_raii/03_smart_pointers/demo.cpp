// phase2_classes_raii/03_smart_pointers/demo.cpp
// 演示：unique_ptr, shared_ptr, weak_ptr

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ── 示例类 ──────────────────────────────────────────────
struct Widget {
    std::string name;
    Widget(std::string n) : name(std::move(n)) {
        std::cout << "  [Widget ctor] " << name << '\n';
    }
    ~Widget() { std::cout << "  [Widget dtor] " << name << '\n'; }
    void greet() const { std::cout << "  Hi from " << name << '\n'; }
};

// ── 工厂函数：返回 unique_ptr 传递所有权 ──────────────
std::unique_ptr<Widget> create_widget(const std::string& name) {
    return std::make_unique<Widget>(name);
}

// ── 接管所有权的函数 ──────────────────────────────────
void consume(std::unique_ptr<Widget> w) {
    std::cout << "  consume: ";
    w->greet();
    // w 在此析构，Widget 被销毁
}

// ── 只使用的函数（不接管所有权） ──────────────────────
void use(const Widget& w) {
    std::cout << "  use: ";
    w.greet();
}

// ── 循环引用演示 ──────────────────────────────────────
struct ListNode {
    int value;
    std::shared_ptr<ListNode> next;
    std::weak_ptr<ListNode> prev;  // weak_ptr 打破循环！

    ListNode(int v) : value(v) {
        std::cout << "  ListNode(" << v << ") created\n";
    }
    ~ListNode() { std::cout << "  ListNode(" << value << ") destroyed\n"; }
};

// ── shared_ptr + weak_ptr 缓存 ────────────────────────
class Cache {
    std::vector<std::weak_ptr<Widget>> items_;
public:
    void add(std::shared_ptr<Widget> w) {
        items_.push_back(w);  // weak_ptr 不增加引用计数！
    }

    void clean_expired() {
        std::erase_if(items_, [](const auto& wp) { return wp.expired(); });
    }

    size_t size() const { return items_.size(); }
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. unique_ptr 基础
    // ═══════════════════════════════════════════════════════
    std::cout << "=== unique_ptr basics ===\n";
    {
        auto w = std::make_unique<Widget>("unique_widget");
        w->greet();

        // auto w2 = w;          // ❌ 编译错误！不能拷贝
        auto w2 = std::move(w);  // ✅ 移动所有权
        std::cout << "  w is null: " << (w == nullptr) << '\n';
        w2->greet();
    }  // w2 析构，Widget 被销毁
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 2. unique_ptr 工厂 + 所有权传递
    // ═══════════════════════════════════════════════════════
    std::cout << "=== factory + ownership transfer ===\n";
    auto w = create_widget("factory_widget");
    use(*w);                        // 只使用，不接管
    consume(std::move(w));          // 所有权转移
    std::cout << "  w after move: " << (w == nullptr) << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. shared_ptr 基础
    // ═══════════════════════════════════════════════════════
    std::cout << "=== shared_ptr basics ===\n";
    {
        auto sp1 = std::make_shared<Widget>("shared_widget");
        std::cout << "  use_count: " << sp1.use_count() << '\n';
        {
            auto sp2 = sp1;           // 共享所有权
            std::cout << "  use_count: " << sp1.use_count() << '\n';
            auto sp3 = sp1;
            std::cout << "  use_count: " << sp1.use_count() << '\n';
        }  // sp2, sp3 析构，计数减少
        std::cout << "  after inner scope, use_count: " << sp1.use_count() << '\n';
    }  // Widget 在此析构
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. weak_ptr 打破循环引用
    // ═══════════════════════════════════════════════════════
    std::cout << "=== weak_ptr breaks cycles ===\n";
    {
        auto n1 = std::make_shared<ListNode>(1);
        auto n2 = std::make_shared<ListNode>(2);

        n1->next = n2;  // shared_ptr -> shared_ptr
        n2->prev = n1;  // weak_ptr -> shared_ptr   ← 不增加引用计数！

        std::cout << "  n1 use_count: " << n1.use_count() << '\n';
        std::cout << "  n2 use_count: " << n2.use_count() << '\n';

        // weak_ptr 使用方式
        if (auto prev = n2->prev.lock()) {  // lock() 返回 shared_ptr
            std::cout << "  n2.prev value: " << prev->value << '\n';
        }
    }  // n1, n2 都能正常销毁（没有循环引用）
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. 自定义删除器
    // ═══════════════════════════════════════════════════════
    std::cout << "=== custom deleter ===\n";
    {
        // 用 unique_ptr 管理 FILE*
        auto file_deleter = [](FILE* f) {
            if (f) {
                std::cout << "  [custom deleter] closing file\n";
                fclose(f);
            }
        };
        std::unique_ptr<FILE, decltype(file_deleter)> file(
            fopen("/tmp/test_smart.txt", "w"), file_deleter
        );
        if (file) fprintf(file.get(), "Hello from smart pointer!\n");
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 6. weak_ptr 做缓存（不阻止销毁）
    // ═══════════════════════════════════════════════════════
    std::cout << "=== weak_ptr cache ===\n";
    Cache cache;
    {
        auto w = std::make_shared<Widget>("cached");
        cache.add(w);
        std::cout << "  cache size: " << cache.size() << '\n';
    }  // w 在此销毁，cache 中的 weak_ptr 过期
    std::cout << "  after Widget destroyed, cache size: " << cache.size() << '\n';
    cache.clean_expired();
    std::cout << "  after cleanup, cache size: " << cache.size() << '\n';

    return 0;
}
