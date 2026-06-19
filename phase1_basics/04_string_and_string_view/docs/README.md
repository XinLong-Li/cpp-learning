# `std::string` 与 `std::string_view`

## 核心区别

| | `std::string` | `std::string_view` |
|---|---------------|---------------------|
| 所有权 | **拥有**字符数据 | **不拥有**，只是一个视图 |
| 内存 | 堆分配 + 内部 buffer | 仅一个指针 + 长度（16 字节） |
| 修改 | ✅ 可修改 | ❌ 只读 |
| 拷贝 | 深拷贝（昂贵） | 浅拷贝（轻量） |
| 以 `\0` 结尾 | ✅ 保证（`c_str()` 可用） | ❌ 不保证 |

```cpp
std::string s = "hello";          // 拥有 "hello" 的副本
std::string_view sv = s;          // 只是一个"窗口"，指向 s 的数据
std::string_view sv2 = "world";   // 直接指向字符串字面量，零开销
```

---

## 为什么需要 `string_view`？

**消除不必要的 `std::string` 构造和拷贝。**

```cpp
// ❌ 坏：每次调用都构造一个 string（堆分配）
void process(const std::string& s);

process("literal");   // 构造临时 string
process(s.substr(0,5)); // substr 返回新 string，再构造临时 string

// ✅ 好：零开销，不分配内存
void process(std::string_view s);

process("literal");   // 直接指向字面量
process(sv.substr(0,5)); // 返回新的 view（还是指向原数据，无分配）
```

---

## 常见用法

### 1. 函数参数：优先用 `string_view`

```cpp
// 当你只需要"读取一段字符"时，用 string_view
int count_words(std::string_view text);
bool starts_with(std::string_view s, std::string_view prefix);
```

### 2. 解析：`string_view` + `substr` 零拷贝

```cpp
std::string_view line = "key=value";
auto eq = line.find('=');
auto key = line.substr(0, eq);    // 零拷贝
auto value = line.substr(eq + 1); // 零拷贝
```

### 3. 什么时候不能用 `string_view`？

- 需要 `\0` 结尾（C API）：用 `std::string`，然后 `.c_str()`
- 需要保存/拥有数据：用 `std::string`
- 需要修改内容：用 `std::string`

---

## `std::string` 的 SSO（小字符串优化）

绝大多数实现中，`std::string` 内部有一个小 buffer（通常 15 字符）。短字符串不堆分配。

```cpp
std::string small = "hi";    // 存放在对象内部，无堆分配
std::string large(1000, 'x'); // 超过内部 buffer，堆分配
```

---

## 常见陷阱

1. **`string_view` 悬垂（最重要！）**
   ```cpp
   std::string_view sv;
   {
       std::string s = "hello";
       sv = s;         // sv 指向 s 的数据
   }                   // s 销毁！sv 现在是悬垂引用！
   std::cout << sv;    // ❌ 未定义行为
   ```

2. **`string_view` 不一定以 `\0` 结尾**
   ```cpp
   std::string_view sv = "hello world";
   sv = sv.substr(0, 5);    // sv 是 "hello"
   printf("%s", sv.data()); // ❌ 可能输出 "hello world"（没有 \0！）
   ```

3. **临时 string 的 `string_view`**
   ```cpp
   std::string_view sv = std::string("temp"); // ❌ 临时对象立即销毁！
   std::string s = "temp";
   std::string_view sv2 = s;                  // ✅ OK，s 的生命周期覆盖 sv2
   ```
