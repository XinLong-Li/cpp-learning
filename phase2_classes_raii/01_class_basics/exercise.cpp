// phase2_classes_raii/01_class_basics/exercise.cpp
// 练习：类基础

#include <iostream>
#include <string>

// ── 练习 1：实现 Rectangle 类 ─────────────────────────
// 有 width, height 两个成员，构造函数接收这两个参数
// 实现 area(), perimeter(), is_square() 方法
// 提示：所有公共方法应该是 const 的

// TODO: class Rectangle { ... };

// ── 练习 2：实现不可拷贝的 Timer 类 ────────────────────
// Timer 记录开始时间，析构时打印经过的时间
// Timer 不应被拷贝（= delete）
// 提示：用 std::chrono

#include <chrono>

// TODO: class Timer { ... };

// ── 练习 3：Temperature 类 ─────────────────────────
// 实现一个温度类，构造函数接收开尔文值
// 有 celsius() 和 fahrenheit() 两个 getter
// 有 static 工厂函数 from_celsius(double) 和 from_fahrenheit(double)
// 构造函数用 explicit

// TODO: class Temperature { ... };

// ── 练习 4：找出下面代码的问题 ──────────────────────────

class BadClass {
public:
    std::string& name() { return name_; }  // 有什么问题？
    const std::string& name() const { return name_; }

    // 有什么问题？
    BadClass() {
        name_ = "default";
        age_ = 0;
    }

private:
    std::string name_;
    int age_;
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // Rectangle r(5, 3);
    // std::cout << "area: " << r.area() << '\n';
    // std::cout << "perimeter: " << r.perimeter() << '\n';
    // std::cout << "is square: " << r.is_square() << '\n';

    // 练习 2:
    // {
    //     Timer t("slow operation");
    //     // 模拟耗时操作
    //     for (volatile int i = 0; i < 100000000; ++i);
    // }  // t 在这里析构，打印耗时

    // 练习 3:
    // auto t = Temperature::from_celsius(100);
    // std::cout << "K: " << t.kelvin() << " C: " << t.celsius() << '\n';

    return 0;
}
