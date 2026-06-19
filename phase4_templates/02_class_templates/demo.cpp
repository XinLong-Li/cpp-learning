// phase4_templates/02_class_templates/demo.cpp
// 演示：类模板、非类型参数、特化

#include <iostream>
#include <vector>
#include <array>
#include <optional>
#include <string>
#include <unordered_map>

// ── 1. 基本类模板：Stack ──────────────────────────────
template<typename T>
class Stack {
public:
    void push(const T& value) { data_.push_back(value); }
    void push(T&& value) { data_.push_back(std::move(value)); }

    std::optional<T> pop() {
        if (data_.empty()) return std::nullopt;
        auto val = std::move(data_.back());
        data_.pop_back();
        return val;
    }

    const T& top() const { return data_.back(); }
    bool empty() const { return data_.empty(); }
    size_t size() const { return data_.size(); }

private:
    std::vector<T> data_;
};

// ── 2. 非类型模板参数 ─────────────────────────────────
template<typename T, size_t Capacity>
class RingBuffer {
public:
    bool push(const T& value) {
        if (size_ >= Capacity) return false;
        data_[write_pos_] = value;
        write_pos_ = (write_pos_ + 1) % Capacity;
        ++size_;
        return true;
    }

    std::optional<T> pop() {
        if (size_ == 0) return std::nullopt;
        auto val = data_[read_pos_];
        read_pos_ = (read_pos_ + 1) % Capacity;
        --size_;
        return val;
    }

    constexpr size_t capacity() const { return Capacity; }
    size_t size() const { return size_; }

private:
    std::array<T, Capacity> data_{};
    size_t write_pos_ = 0;
    size_t read_pos_ = 0;
    size_t size_ = 0;
};

// ── 3. 模板特化 ──────────────────────────────────────
template<typename T>
struct TypeName {
    static std::string get() { return "unknown"; }
};

template<>
struct TypeName<int> {
    static std::string get() { return "int"; }
};

template<>
struct TypeName<std::string> {
    static std::string get() { return "string"; }
};

// 偏特化：指针
template<typename T>
struct TypeName<T*> {
    static std::string get() { return TypeName<T>::get() + "*"; }
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. Stack 模板
    // ═══════════════════════════════════════════════════════
    Stack<int> si;
    si.push(10);
    si.push(20);
    si.push(30);
    std::cout << "int stack: ";
    while (!si.empty()) {
        std::cout << *si.pop() << ' ';
    }
    std::cout << '\n';

    Stack<std::string> ss;
    ss.push("hello");
    ss.push("world");
    std::cout << "string stack top: " << ss.top() << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. RingBuffer（非类型模板参数）
    // ═══════════════════════════════════════════════════════
    RingBuffer<int, 4> buf;  // 栈上，容量 4，无堆分配！
    buf.push(1); buf.push(2); buf.push(3); buf.push(4);
    std::cout << "RingBuffer capacity: " << buf.capacity() << '\n';
    std::cout << "RingBuffer size: " << buf.size() << '\n';

    bool overflow = buf.push(5);  // 满了
    std::cout << "push(5) when full: " << (overflow ? "ok" : "full") << '\n';

    std::cout << "RingBuffer content: ";
    for (int i = 0; i < 4; ++i) std::cout << *buf.pop() << ' ';
    std::cout << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. 类型名（特化）
    // ═══════════════════════════════════════════════════════
    std::cout << "TypeName<int>: " << TypeName<int>::get() << '\n';
    std::cout << "TypeName<double>: " << TypeName<double>::get() << '\n';
    std::cout << "TypeName<string>: " << TypeName<std::string>::get() << '\n';
    std::cout << "TypeName<int*>: " << TypeName<int*>::get() << '\n';
    std::cout << "TypeName<string*>: " << TypeName<std::string*>::get() << '\n';

    return 0;
}
