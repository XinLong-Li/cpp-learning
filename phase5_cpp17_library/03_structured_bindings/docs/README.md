# 结构化绑定（Structured Bindings，C++17）

## 核心语法

```cpp
// pair / tuple
auto [x, y] = std::pair{1, 2.5};

// map 遍历
for (const auto& [key, value] : my_map) { ... }

// 自定义 struct
struct Point { int x; int y; };
auto [px, py] = Point{3, 4};

// 数组
int arr[] = {1, 2, 3};
auto [a, b, c] = arr;
```

---

## 三种绑定方式

```cpp
auto [a, b] = get_pair();       // 值绑定：拷贝
auto& [a, b] = get_pair();      // 引用绑定：可修改原值
const auto& [a, b] = get_pair(); // const 引用：只读
```

---

## 适用类型

结构化绑定可工作于：
1. 原生数组
2. `std::tuple`、`std::pair`、`std::array`
3. 所有非静态成员都是 public 的 struct/class

```cpp
struct Person {
    std::string name;
    int age;
    // 全部 public → 支持结构化绑定！
};

Person p{"Alice", 30};
auto& [name, age] = p;
name = "Bob";   // 修改了 p.name
```

---

## 常见用法

### 1. map 遍历（最常用）
```cpp
std::map<std::string, int> scores = {{"alice", 95}, {"bob", 88}};
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << '\n';
}
```

### 2. insert 返回值
```cpp
auto [it, inserted] = my_map.insert({"key", value});
if (inserted) {
    std::cout << "new element inserted\n";
}
```

### 3. 多返回值
```cpp
auto [min_val, max_val] = std::minmax({3, 1, 4, 1, 5});
// 比 std::pair 的 .first / .second 语义清晰多了
```

---

## 注意事项

1. **不能嵌套**：`auto [a, [b, c]] = ...` 不行
2. **必须在同一作用域**：绑定在整个语句所在作用域内有效
3. **bindings 不是变量**：`a` 和 `b` 不能被 lambda 捕获（需要 C++20）
