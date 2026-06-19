// phase2_classes_raii/01_class_basics/demo.cpp
// 演示：类的构造、析构、初始化列表、explicit、default/delete

#include <iostream>
#include <string>
#include <utility>  // std::move

// ── 1. 基础类：构造函数 + 成员初始化列表 ─────────────────
class Person {
public:
    // 构造函数 —— 用初始化列表，不用函数体赋值
    Person(std::string name, int age)
        : name_(std::move(name)), age_(age) {
        std::cout << "  [ctor] Person(" << name_ << ", " << age_ << ")\n";
    }

    ~Person() {
        std::cout << "  [dtor] ~Person(" << name_ << ")\n";
    }

    // const getter
    const std::string& name() const { return name_; }
    int age() const { return age_; }

    // non-const setter
    void set_age(int age) { age_ = age; }

private:
    std::string name_;
    int age_;
};

// ── 2. explicit 构造函数 ────────────────────────────────
class Fraction {
public:
    explicit Fraction(int numerator, int denominator = 1)
        : num_(numerator), den_(denominator) {}

    double value() const { return static_cast<double>(num_) / den_; }

private:
    int num_, den_;
};

// void f(Fraction frac) {}  // 这样可以测试隐式转换被阻止

// ── 3. Rule of Zero 示例 ────────────────────────────────
// 所有成员都有正确的拷贝/移动/析构，所以无需自定义任何特殊函数
class Config {
public:
    Config(std::string name, int value)
        : name_(std::move(name)), value_(value) {}

    const std::string& name() const { return name_; }
    int value() const { return value_; }

private:
    std::string name_;  // 有正确的拷贝/移动/析构
    int value_;         // 平凡的
};

// ── 4. = delete 禁止拷贝 ─────────────────────────────────
class UniqueId {
    int id_;
public:
    explicit UniqueId(int id) : id_(id) {}

    // 禁止拷贝
    UniqueId(const UniqueId&) = delete;
    UniqueId& operator=(const UniqueId&) = delete;

    // 但允许移动
    UniqueId(UniqueId&&) = default;
    UniqueId& operator=(UniqueId&&) = default;

    int value() const { return id_; }
};

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 构造与析构
    // ═══════════════════════════════════════════════════════
    {
        std::cout << "Creating p1:\n";
        Person p1("Alice", 30);
        std::cout << "p1: " << p1.name() << ", " << p1.age() << '\n';
        std::cout << "p1 leaving scope...\n";
    }  // p1 在此析构
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 2. explicit 的作用
    // ═══════════════════════════════════════════════════════
    Fraction f1(3, 4);        // ✅ OK
    Fraction f2{1, 2};        // ✅ OK
    // Fraction f3 = 5;        // ❌ 编译错误（explicit 阻止了隐式转换）
    std::cout << "f1 = " << f1.value() << '\n';
    std::cout << "f2 = " << f2.value() << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. Rule of Zero
    // ═══════════════════════════════════════════════════════
    Config c1("timeout", 30);
    Config c2 = c1;              // ✅ 自动生成的拷贝构造
    Config c3 = std::move(c1);  // ✅ 自动生成的移动构造
    std::cout << "c2: " << c2.name() << "=" << c2.value() << '\n';
    std::cout << "c3: " << c3.name() << "=" << c3.value() << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 4. = delete 禁止拷贝
    // ═══════════════════════════════════════════════════════
    UniqueId id1(100);
    // UniqueId id2 = id1;       // ❌ 编译错误：拷贝被 delete
    UniqueId id2 = std::move(id1); // ✅ 移动 OK
    std::cout << "id1: " << id1.value() << ", id2: " << id2.value() << '\n';

    return 0;
}
