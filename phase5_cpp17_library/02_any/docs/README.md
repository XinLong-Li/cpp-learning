# `std::any`：类型擦除的万能容器

## 能存任何类型的单个值

```cpp
std::any a = 42;
a = 3.14;
a = std::string("hello");
a = std::vector<int>{1, 2, 3};
```

## 与 `variant` 的区别

| | `std::variant<Ts...>` | `std::any` |
|---|----------------------|------------|
| 可存类型 | 编译期限定（`Ts...` 中列出的） | 任意类型 |
| 类型安全 | ✅ 编译期检查 | ⚠️ 运行期检查 |
| 存储方式 | 栈（无堆分配） | 可能堆分配 |
| 访问 | `std::get<T>` / `std::visit` | `std::any_cast<T>` |
| 使用场景 | 已知所有可能类型 | 类型在编译期无法确定 |

---

## 基本用法

```cpp
std::any a;

// 赋值
a = 42;
a = std::string("hello");

// 读取（必须指定正确类型！）
auto s = std::any_cast<std::string>(a);   // OK
// auto i = std::any_cast<int>(a);         // ❌ 抛 bad_any_cast

// 安全读取
if (auto* p = std::any_cast<std::string>(&a)) {
    std::cout << *p << '\n';
}

// 检查是否有值
a.has_value();           // true
a.type();                // 返回 type_info

// 清空
a.reset();
```

---

## 典型场景

```cpp
// 1. 通用配置存储
std::map<std::string, std::any> config;
config["timeout"] = 30;
config["host"] = std::string("localhost");
config["retries"] = std::vector<int>{1, 2, 5};

// 2. 消息传递系统（不知道消息类型）
class MessageBus {
    std::unordered_map<std::string, std::any> messages;
};
```

---

## 什么时候用 `any`？

- ✅ 确实不知道所有可能的类型（如插件系统、脚本绑定）
- ✅ 第三方类型你无法列举
- ❌ 如果类型的集合是已知的，用 `variant`
- ❌ 如果只是"可空"语义，用 `optional`
