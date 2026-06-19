# Sanitizers：运行时错误检测

## 四种 Sanitizer

| Sanitizer | 编译标志 | 检测内容 |
|-----------|---------|---------|
| **AddressSanitizer (ASan)** | `-fsanitize=address` | 堆/栈越界、use-after-free、double-free、内存泄漏 |
| **UndefinedBehaviorSanitizer (UBSan)** | `-fsanitize=undefined` | 整数溢出、空指针解引用、非法移位、除零 |
| **ThreadSanitizer (TSan)** | `-fsanitize=thread` | 数据竞争（data race） |
| **MemorySanitizer (MSan)** | `-fsanitize=memory` | 未初始化内存的读取 |

---

## 用法

```bash
# 编译时加上标志 + 调试信息
g++ -fsanitize=address,undefined -g -O0 main.cpp -o main

# 直接运行
./main
# 如果检测到问题，会打印详细的错误报告（文件名:行号 + 原因）

# 内存泄漏检测（程序结束时报告）
ASAN_OPTIONS=detect_leaks=1 ./main
```

---

## ASan 能检测到的错误示例

```cpp
// 1. 堆越界
int* p = new int[10];
p[10] = 42;  // ❌ ASan: heap-buffer-overflow

// 2. 栈越界
int arr[10];
arr[10] = 42; // ❌ ASan: stack-buffer-overflow

// 3. Use-after-free
delete p;
*p = 42;      // ❌ ASan: heap-use-after-free

// 4. 内存泄漏
int* leaked = new int[100];
// 忘记 delete → ASan: memory leak
```

---

## 学习阶段的建议

**始终用 ASan + UBSan 编译你的练习代码！**

项目 CMakeLists.txt 已配置为 Debug 模式自动开启：
```cmake
if(CMAKE_BUILD_TYPE MATCHES "Debug" OR NOT CMAKE_BUILD_TYPE)
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()
```

---

## 性能开销

| Sanitizer | 大约开销 |
|-----------|---------|
| ASan | ~2x 慢 |
| UBSan | ~1.2x 慢 |
| TSan | ~5-15x 慢 |
| MSan | ~3x 慢 |

开发/测试阶段可以承受。**永远不要在 Release 中开启。**

---

## 注意事项

- ASan 和 TSan **不能同时使用**（选一个）
- MSan 目前主要 Linux 可用
- 某些库（如 TBB）可能与 ASan 冲突
