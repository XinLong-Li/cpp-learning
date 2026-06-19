# 现代 C++ 控制流

## `if constexpr`（C++17）—— 编译期条件

普通 `if` 在**运行期**选择分支；`if constexpr` 在**编译期**选择，不满足条件的分支不会被编译。

```cpp
template<typename T>
auto get_value(T&& val) {
    if constexpr (std::is_pointer_v<T>) {
        return *val;      // T 不是指针时，这行不会编译
    } else {
        return val;       // T 是指针时，这行不会编译
    }
}
```

**核心价值**：同一份代码里可以写对不同类型"不合法的操作"，编译器不会报错。

---

## `if` 带初始化语句（C++17）

```cpp
// ❌ 旧式：lock_guard 的作用域是整个函数
{
    std::lock_guard<std::mutex> lk(mtx);
    if (map.find(key) != map.end()) {
        // lk 的生命周期到这个 }，但其实 if 后面不需要持锁了
    }
}

// ✅ C++17：初始化语句在 if 的作用域内
if (auto it = map.find(key); it != map.end()) {
    use(it->second);
}   // it 在这里销毁，干净！
```

这同样适用于 `switch`：

```cpp
switch (auto state = get_state(); state) {
    case State::Ready:    /* ... */ break;
    case State::Running:  /* ... */ break;
}
```

---

## Range-based `for` 循环

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};

// 只读（最佳默认）
for (const auto& item : v) { /* ... */ }

// 修改原值
for (auto& item : v) { item *= 2; }

// 拷贝（仅对小类型）
for (int item : v) { /* ... */ }
```

**永远默认 `const auto&`，需要修改再加 `&`。**

---

## Range-based `for` 的陷阱

### 1. 临时对象问题
```cpp
std::vector<int> get_vec() { return {1, 2, 3}; }

// ❌ 未定义行为！for 循环的生命周期规则复杂
for (auto x : get_vec()) { ... }  // C++17 起 OK（临时对象生命周期延长了）
```

### 2. 修改容器导致迭代器失效
```cpp
for (auto& x : v) {
    if (x == 0) v.push_back(1);  // ❌ 迭代器失效！UB！
}
```

### 3. 结构化绑定（C++17）
```cpp
std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
for (const auto& [key, value] : m) {
    std::cout << key << ": " << value << '\n';
}
```

---

## `switch`（谨慎使用）

C++ 的 `switch` 仍有用武之地（`enum` 匹配 + `default` 警告），但优先考虑：
1. `if constexpr` 处理编译期分支
2. `std::variant` + `std::visit` 处理运行期多态
3. `switch` 搭配 `[[fallthrough]];` 属性警告

```cpp
switch (cmd) {
    case Command::Save:
        save_file();
        [[fallthrough]];   // 明确"我是故意的"
    case Command::Close:
        close_window();
        break;
    default:
        throw std::runtime_error("unknown command");
}
```
