// phase6_error_handling/01_exception_safety/exercise.cpp
// 练习：异常安全

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

// ── 练习 1：实现 copy-and-swap ────────────────────────

// TODO: 实现一个简单的 Buffer 类，用 copy-and-swap 实现强异常安全保证

// class SafeBuffer {
// public:
//     explicit SafeBuffer(size_t size) : data_(std::make_unique<char[]>(size)), size_(size) {}
//
//     // 拷贝构造（可能抛异常，因为 make_unique 可能抛）
//     SafeBuffer(const SafeBuffer& other);
//
//     // 拷贝赋值（强异常安全：copy-and-swap）
//     SafeBuffer& operator=(const SafeBuffer& other);
//
//     // 移动（noexcept）
//     SafeBuffer(SafeBuffer&& other) noexcept = default;
//     SafeBuffer& operator=(SafeBuffer&& other) noexcept = default;
//
//     void swap(SafeBuffer& other) noexcept {
//         data_.swap(other.data_);
//         std::swap(size_, other.size_);
//     }
//
// private:
//     std::unique_ptr<char[]> data_;
//     size_t size_ = 0;
// };

// ── 练习 2：识别异常安全问题 ────────────────────────
// 下面的代码有什么异常安全问题？

void unsafe_transfer(BankAccount& from, BankAccount& to, double amount) {
    from.withdraw(amount);  // 如果这里抛异常？
    to.deposit(amount);     // 如果这里抛异常，钱已经从 from 扣了！
}

// TODO: 解释问题并修复（提示：先记录，再操作）

// ── 练习 3：异常规格与 noexcept ────────────────────
// 判断下列函数哪些应该标记为 noexcept

// int get_size() const;                    // TODO: noexcept?
// void swap(Widget& other);                // TODO: noexcept?
// void parse_config(const std::string&);   // TODO: noexcept?
// ~Widget();                               // TODO: noexcept?

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // SafeBuffer buf1(100), buf2(200);
    // buf1 = buf2;  // 强异常安全

    return 0;
}
