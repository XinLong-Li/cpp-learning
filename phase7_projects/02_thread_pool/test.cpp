// phase7_projects/02_thread_pool/test.cpp
// ThreadPool 编译验证和基本功能测试

#include "ThreadPool.hpp"
#include <iostream>
#include <cassert>

int main() {
    // 1. 创建线程池
    ThreadPool pool(4);
    std::cout << "[PASS] ThreadPool created with 4 threads\n";

    // 2. 提交简单任务
    auto future = pool.submit([](int a, int b) {
        return a + b;
    }, 2, 3);

    int result = future.get();
    assert(result == 5);
    std::cout << "[PASS] submit(2+3) = " << result << '\n';

    // 3. 提交多个任务
    auto f1 = pool.submit([] { return 10; });
    auto f2 = pool.submit([] { return 20; });
    auto f3 = pool.submit([] { return 30; });

    assert(f1.get() == 10);
    assert(f2.get() == 20);
    assert(f3.get() == 30);
    std::cout << "[PASS] Multiple tasks completed\n";

    std::cout << "\nAll tests passed!\n";
    return 0;
}
