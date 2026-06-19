// phase6_error_handling/02_sanitizers/demo.cpp
// 演示：常见的内存错误（开启 ASan/UBSan 编译运行观察）

#include <iostream>
#include <vector>

// 取消注释每个函数来观察 sanitizer 如何报告错误

// ── 1. 堆缓冲区越界 ───────────────────────────────────
void heap_buffer_overflow() {
    int* p = new int[5];
    p[5] = 42;  // ❌ heap-buffer-overflow (0 bytes to the right)
    std::cout << "p[5] = " << p[5] << '\n';
    delete[] p;
}

// ── 2. 栈缓冲区越界 ──────────────────────────────────
void stack_buffer_overflow() {
    int arr[5] = {1, 2, 3, 4, 5};
    int x = arr[10];  // ❌ stack-buffer-overflow
    std::cout << "arr[10] = " << x << '\n';
}

// ── 3. Use-after-free ────────────────────────────────
void use_after_free() {
    int* p = new int(42);
    delete p;
    *p = 100;  // ❌ heap-use-after-free
    std::cout << "*p = " << *p << '\n';
}

// ── 4. Use-after-return ──────────────────────────────
int* use_after_return() {
    int local = 42;
    return &local;  // ❌ 返回局部变量地址
}

// ── 5. 未定义行为：整数溢出 ─────────────────────────
void integer_overflow() {
    int max = 2147483647;  // INT_MAX
    max += 1;               // ❌ signed integer overflow
    std::cout << "max+1 = " << max << '\n';
}

// ── 6. 未初始化内存读取 ─────────────────────────────
void uninitialized_read() {
    int x;            // 未初始化
    if (x > 0) {      // ❌ 读取未初始化变量 (UB detected by -fsanitize=memory)
        std::cout << "positive\n";
    }
}

// ── 7. vector 的 out-of-bounds（用 [] 不检查） ────────
void vector_oob() {
    std::vector<int> v = {1, 2, 3};
    std::cout << v[10];  // ❌ [] 不检查边界（UB）
    // std::cout << v.at(10);  // ✅ .at() 抛异常（安全）
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    std::cout << "This program demonstrates memory bugs.\n";
    std::cout << "Build with: cmake -DCMAKE_BUILD_TYPE=Debug ..\n";
    std::cout << "Then run to see ASan/UBSan reports.\n\n";

    // 取消注释下面的行来观察 sanitizer 报告
    std::cout << "Testing with sanitizers disabled — uncomment bugs to test:\n";
    // heap_buffer_overflow();
    // stack_buffer_overflow();
    // use_after_free();
    // integer_overflow();
    // vector_oob();

    std::cout << "\nAll tests commented out — no bugs triggered.\n";
    return 0;
}
