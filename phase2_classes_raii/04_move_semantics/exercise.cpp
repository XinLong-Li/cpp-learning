// phase2_classes_raii/04_move_semantics/exercise.cpp
// 练习：移动语义

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ── 练习 1：实现移动操作的 StringWrapper ───────────────
// 实现一个简单的字符串包装类，支持拷贝和移动

// TODO: 实现
// class StringWrapper {
// public:
//     explicit StringWrapper(std::string s);
//
//     // 拷贝构造
//     StringWrapper(const StringWrapper& other);
//
//     // 移动构造 (noexcept!)
//     StringWrapper(StringWrapper&& other) noexcept;
//
//     // 拷贝赋值
//     StringWrapper& operator=(const StringWrapper& other);
//
//     // 移动赋值
//     StringWrapper& operator=(StringWrapper&& other) noexcept;
//
//     ~StringWrapper();
//
//     const std::string& get() const { return *data_; }
//
// private:
//     // 用 unique_ptr 持有（模仿需要手动管理的资源）
//     // 如果是 std::string 成员，就可以用 Rule of Zero 了
//     std::unique_ptr<std::string> data_;
// };

// ── 练习 2：判断代码行为 ──────────────────────────────
// 下面的每段代码会调用拷贝还是移动？

void exercise2() {
    std::string s = "hello";

    auto s1 = s;                    // TODO: 拷贝还是移动？
    auto s2 = std::move(s);        // TODO: 拷贝还是移动？
    auto&& s3 = std::move(s1);     // TODO: 拷贝还是移动？（提示：&& 只是引用）

    std::cout << "s: '" << s << "' (should be empty or valid state)\n";
    std::cout << "s2: '" << s2 << "'\n";
}

// ── 练习 3：消除不必要的拷贝 ──────────────────────────
// 优化下面的函数，减少不必要的拷贝

// TODO: 优化下面的函数
std::vector<std::string> build_messages() {
    std::vector<std::string> result;
    std::string a = "hello";
    std::string b = "world";

    result.push_back(a);       // 怎么优化？
    result.push_back(b);       // 怎么优化？

    return result;             // 会被拷贝吗？（不会，RVO）
}

// ── 练习 4：Rule of Five 分析 ────────────────────────
// 下面这个类是否需要自定义析构/拷贝/移动？为什么？

// TODO: 分析
struct ManagedResource {
    std::vector<int> data;
    std::unique_ptr<char[]> name;
    std::shared_ptr<double> cached;

    // 需要自定义任何特殊成员函数吗？
    // 答案：不需要！Rule of Zero 适用
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // StringWrapper sw1("hello world");
    // StringWrapper sw2 = std::move(sw1);
    // std::cout << "sw2: " << sw2.get() << '\n';
    // // sw1 现在处于什么状态？

    exercise2();

    // 练习 3:
    // auto msgs = build_messages();
    // for (const auto& m : msgs) std::cout << m << '\n';

    return 0;
}
