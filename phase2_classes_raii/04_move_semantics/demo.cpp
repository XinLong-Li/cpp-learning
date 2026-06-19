// phase2_classes_raii/04_move_semantics/demo.cpp
// 演示：移动语义、std::move、Rule of Five/Zero

#include <iostream>
#include <string>
#include <vector>
#include <cstring>    // memcpy

// ── 1. 带移动语义的自定义类 ─────────────────────────────
class Buffer {
public:
    Buffer(const char* data, size_t size) : size_(size) {
        data_ = new char[size_];
        std::memcpy(data_, data, size_);
        std::cout << "  [Buffer ctor] " << size_ << " bytes\n";
    }

    // 拷贝构造
    Buffer(const Buffer& other) : size_(other.size_) {
        data_ = new char[size_];
        std::memcpy(data_, other.data_, size_);
        std::cout << "  [Buffer copy] " << size_ << " bytes (deep copy)\n";
    }

    // 移动构造（noexcept 很重要！vector 扩容时会用到）
    Buffer(Buffer&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "  [Buffer move] " << size_ << " bytes (stolen)\n";
    }

    // 移动赋值
    Buffer& operator=(Buffer&& other) noexcept {
        std::cout << "  [Buffer move assign]\n";
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~Buffer() {
        if (data_) std::cout << "  [Buffer dtor] " << size_ << " bytes freed\n";
        delete[] data_;
    }

    size_t size() const { return size_; }
    const char* data() const { return data_; }

private:
    char* data_ = nullptr;
    size_t size_ = 0;
};

// ── 2. Rule of Zero 示例 ───────────────────────────────
struct GoodConfig {
    std::vector<int> items;
    std::string name;
    // 不需要写任何特殊成员函数！
};

// ── 3. 演示 std::move 在 return 上是坏习惯 ─────────────
struct LoudMove {
    std::string name;
    LoudMove(std::string n) : name(std::move(n)) {
        std::cout << "  [LoudMove ctor] " << name << '\n';
    }
    LoudMove(const LoudMove&) : name("(copied)") {
        std::cout << "  [LoudMove copy]\n";
    }
    LoudMove(LoudMove&&) noexcept : name("(moved)") {
        std::cout << "  [LoudMove move]\n";
    }
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 拷贝 vs 移动
    // ═══════════════════════════════════════════════════════
    {
        std::cout << "=== copy ===\n";
        Buffer b1("hello", 5);
        Buffer b2 = b1;                        // 深拷贝
        std::cout << "b1: " << b1.size() << " bytes\n";
        std::cout << "b2: " << b2.size() << " bytes\n\n";

        std::cout << "=== move ===\n";
        Buffer b3 = std::move(b1);             // 移动（偷资源）
        std::cout << "b1 after move: " << b1.size() << " bytes\n";
        std::cout << "b3: " << b3.size() << " bytes\n\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 2. std::move 不移动，只是类型转换
    // ═══════════════════════════════════════════════════════
    {
        int x = 100;
        int&& r = std::move(x);     // 只是类型转换：int → int&&
        std::cout << "x is still: " << x << '\n';  // x 没被改变
        r = 200;
        std::cout << "after r=200, x = " << x << "\n\n";
    }

    // ═══════════════════════════════════════════════════════
    // 3. 向容器中放入对象
    // ═══════════════════════════════════════════════════════
    {
        std::vector<std::string> v;

        std::string s1 = "hello world, this is a long string";
        std::cout << "push_back (copy):\n";
        v.push_back(s1);                      // 拷贝
        std::cout << "s1 still: " << s1.size() << " bytes\n";

        std::cout << "push_back (move):\n";
        v.push_back(std::move(s1));           // 移动！
        std::cout << "s1 after move: " << s1.size() << " bytes\n";

        std::cout << "emplace_back (construct in-place):\n";
        v.emplace_back("from emplace");       // 最优：原地构造，没有拷贝或移动
        std::cout << '\n';
    }

    // ═══════════════════════════════════════════════════════
    // 4. const 对象不能真正被 move
    // ═══════════════════════════════════════════════════════
    {
        std::cout << "=== const object 'move' ===\n";
        const std::string cs = "immutable";
        auto s2 = std::move(cs);              // 实际调用了拷贝构造！
        std::cout << "cs: '" << cs << "'\n";  // cs 完好，因为做的是拷贝
        std::cout << "s2: '" << s2 << "'\n\n";
    }

    // ═══════════════════════════════════════════════════════
    // 5. noexcept 的重要性
    // ═══════════════════════════════════════════════════════
    {
        std::cout << "=== noexcept matters ===\n";
        // 如果没有 noexcept 移动构造，vector 扩容时会用拷贝而不是移动！
        std::cout << std::boolalpha;
        std::cout << "Buffer move ctor noexcept: "
                  << std::is_nothrow_move_constructible_v<Buffer> << '\n';
        // 如果为 true，vector 扩容时会调用移动构造（高效）
        // 如果为 false，vector 扩容时会调用拷贝构造（安全但不高效）
    }

    return 0;
}
