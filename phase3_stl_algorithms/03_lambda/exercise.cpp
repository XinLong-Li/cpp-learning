// phase3_stl_algorithms/03_lambda/exercise.cpp
// 练习：Lambda

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

// ── 练习 1：实现通用的 filter 函数 ──────────────────────
// 用一个 lambda + 算法过滤容器

// TODO: 实现
// template<typename Container, typename Predicate>
// auto filter(const Container& c, Predicate pred) {
//     Container result;
//     std::copy_if(c.begin(), c.end(), std::back_inserter(result), pred);
//     return result;
// }

// ── 练习 2：用 lambda 实现 make_adder ──────────────────
// 返回一个 lambda，它把参数加上固定的偏移量

// TODO: 实现
// auto make_adder(int offset) {
//     return [???](int x) { return ???; };
// }

// ── 练习 3：捕获 this ───────────────────────────────
// 实现一个类 Counter，有 increment 方法
// 它返回一个 lambda，每次调用 lambda 时 counter 增加

// TODO: 实现
// class Counter {
//     int value_ = 0;
// public:
//     auto make_incrementer() {
//         // lambda 需要捕获 this
//         return [???]() { return ???; };
//     }
//     int value() const { return value_; }
// };

// ── 练习 4：用 lambda 对 vector<Person> 排序 ──────────
struct Person {
    std::string name;
    int age;
};

// TODO: 用 sort + lambda 先按 age 降序，再按 name 升序

// ── 练习 5：实现 pipe ───────────────────────────────
// 实现一个简单的管道：依次应用多个函数
// pipe(f, g, h)(x) = h(g(f(x)))

// TODO: 实现
// template<typename F, typename G>
// auto compose(F f, G g) {
//     return [f = std::move(f), g = std::move(g)](auto x) {
//         return g(f(std::move(x)));
//     };
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // auto v = std::vector{1, 2, 3, 4, 5, 6};
    // auto evens = filter(v, [](int x) { return x % 2 == 0; });

    // 练习 2:
    // auto plus_10 = make_adder(10);
    // std::cout << plus_10(5) << '\n';  // 15

    // 练习 3:
    // Counter c;
    // auto inc = c.make_incrementer();
    // inc(); inc(); inc();
    // std::cout << c.value() << '\n';  // 3

    // 练习 5:
    // auto f = [](int x) { return x + 1; };
    // auto g = [](int x) { return x * 2; };
    // auto composed = compose(f, g);
    // std::cout << composed(5) << '\n';  // (5+1)*2 = 12

    return 0;
}
