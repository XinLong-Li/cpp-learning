# 类基础：构造函数、析构函数、成员初始化列表

## 类的核心原则

1. **构造即初始化** —— 对象在诞生那一刻就处于可用状态
2. **析构即释放** —— 对象死亡时自动释放所有资源
3. **Rule of Zero** —— 尽量不定义析构/拷贝/移动，让编译器自动生成

---

## 基本语法

```cpp
class Person {
public:
    // 构造函数：初始化对象
    Person(std::string name, int age)
        : name_(std::move(name)), age_(age) {}  // 成员初始化列表

    // getter：const 成员函数
    const std::string& name() const { return name_; }
    int age() const { return age_; }

    // setter：非 const 成员函数
    void set_age(int age) { age_ = age; }

private:
    std::string name_;
    int age_;
};
```

---

## 成员初始化列表

**总是用初始化列表，不要写在构造函数体内！**

```cpp
// ❌ 坏：先默认初始化，再赋值
Person(std::string name, int age) {
    name_ = name;  // name_ 先被默认初始化（空 string），再赋值
    age_ = age;
}

// ✅ 好：直接初始化
Person(std::string name, int age)
    : name_(std::move(name)), age_(age) {}  // 直接构造，零开销
```

原因：
- 对于非内置类型，初始化列表避免了"默认构造 + 赋值"
- 对于 `const` 成员和引用成员，**必须**用初始化列表

---

## 默认生成的特殊成员函数

编译器会自动生成（在需要时）：

| 函数 | 签名 | 何时自动生成 |
|------|------|-------------|
| 默认构造 | `Foo()` | 没有其他构造函数时 |
| 析构函数 | `~Foo()` | 总是 |
| 拷贝构造 | `Foo(const Foo&)` | 无移动操作时 |
| 拷贝赋值 | `Foo& operator=(const Foo&)` | 无移动操作时 |
| 移动构造 | `Foo(Foo&&)` | 无拷贝/析构/移动赋值时 |
| 移动赋值 | `Foo& operator=(Foo&&)` | 无拷贝/析构/移动构造时 |

---

## `= default` / `= delete`

```cpp
class NoCopy {
public:
    NoCopy() = default;                   // 显式要求默认构造
    NoCopy(const NoCopy&) = delete;       // 禁止拷贝
    NoCopy& operator=(const NoCopy&) = delete;
};
```

---

## `explicit` 构造函数

防止隐式类型转换：

```cpp
class Fraction {
public:
    explicit Fraction(int num) : num_(num) {}  // 禁止隐式转换
private:
    int num_;
};

Fraction f1 = 5;     // ❌ 编译错误（explicit 禁止）
Fraction f2(5);      // ✅ OK
Fraction f3{5};      // ✅ OK
```

**默认给单参数构造函数加 `explicit`。**

---

## `struct` vs `class`

唯一区别：`struct` 默认公开，`class` 默认私有。

```cpp
struct Point { int x; int y; };  // x,y 是 public
class Person { int age_; };       // age_ 是 private
```

约定：**简单的数据聚合用 `struct`，有逻辑的类用 `class`。**
