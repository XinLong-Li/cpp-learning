// phase1_basics/01_types_and_auto/exercise.cpp
// 练习：类型与 auto

#include <iostream>
#include <string>
#include <vector>
#include <map>

// ── 练习 1：写出 auto 推导出来的类型 ───────────────────────
// 阅读下面的代码，在注释中写出每个 auto 变量推导出的精确类型

void exercise1() {
    const int ci = 100;

    auto a1 = ci;           // TODO: a1 的类型是？          (a) int
                             //                                    (b) const int
                             //                                    (c) int&

    auto& a2 = ci;          // TODO: a2 的类型是？          (a) int
                             //                                    (b) const int&
                             //                                    (c) int&

    const auto& a3 = 42;    // TODO: a3 的类型是？          (a) int
                             //                                    (b) const int&
                             //                                    (c) int&&

    std::cout << "Exercise 1: Uncomment and test yourself.\n";
    // 取消下面的注释来验证你的答案：
    // std::cout << "a1 is int: " << std::is_same_v<decltype(a1), int> << '\n';
    // std::cout << "a2 is const int&: " << std::is_same_v<decltype(a2), const int&> << '\n';
    // std::cout << "a3 is const int&: " << std::is_same_v<decltype(a3), const int&> << '\n';
}

// ── 练习 2：用 const auto& 改写 ───────────────────────────
// 下面的代码有什么问题？改写它以消除不必要的拷贝

void exercise2() {
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "Diana"};

    // TODO: 这段代码每次都拷贝了 name，修改它以避免拷贝
    // 提示：这里不需要修改 name，只是打印
    for (auto name : names) {
        std::cout << "Hello, " << name << "!\n";
    }
}

// ── 练习 3：实现智能类型名打印 ───────────────────────────
// 编写一个函数模板，接收任意类型的参数并打印它

// TODO: 用 auto 参数（C++20 缩写函数模板）或模板实现 print_type_name
// 提示：标准没有直接获取类型名的可移植方法，用 typeid(x).name()
// 扩展：检查变量是 const 吗？是引用吗？是 volatile 吗？

#include <typeinfo>

// TODO: 实现这个函数
// void print_info(/* ??? */) {
//     // 打印变量的类型信息和值
// }

// ── 练习 4：为 std::map 写遍历 ───────────────────────────
void exercise4() {
    std::map<std::string, int> scores = {
        {"math", 95}, {"english", 88}, {"cs", 100}
    };

    // TODO: 用 auto 和 range-based for 遍历 scores，
    // 打印每门课的名称和分数（避免任何不必要的拷贝）
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    exercise1();
    exercise2();
    // exercise3();
    exercise4();
    return 0;
}
