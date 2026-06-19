// phase2_classes_raii/02_raii/exercise.cpp
// 练习：RAII

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <cstdio>

// ── 练习 1：实现 ScopedConnection ────────────────────
// 模拟数据库连接：connect() 建立连接，disconnect() 断开
// 用 RAII 保证连接始终断开

// TODO: 实现 Connection 类
// class Connection {
// public:
//     Connection(const char* db_name);
//     ~Connection();
//     // 禁止拷贝，允许移动
//     void execute(const char* query);
// private:
//     // 模拟连接句柄
//     bool connected_ = false;
//     std::string db_name_;
// };

// ── 练习 2：实现 ScopedProfiler ─────────────────────
// 构造时记录开始时间，析构时打印耗时
// 提示：用 std::chrono::steady_clock

#include <chrono>

// class ScopedProfiler {
// public:
//     explicit ScopedProfiler(const char* name);
//     ~ScopedProfiler();
// private:
//     const char* name_;
//     std::chrono::steady_clock::time_point start_;
// };

// ── 练习 3：审查代码的异常安全 ────────────────────────
// 下面的代码在异常发生时会导致资源泄漏吗？为什么？

#include <mutex>

void potentially_leaky() {
    auto* data = new int[100];          // 资源 1
    std::mutex mtx;
    mtx.lock();                          // 资源 2

    // some_operation_that_may_throw();

    mtx.unlock();                        // 如果上面抛异常，这行不会执行
    delete[] data;                       // 这行也不会执行
}

// TODO: 用 RAII 重写上面的函数
// void safe_with_raii() {
//     // 你的代码
// }

// ── 练习 4：实现 finally 模拟 ──────────────────────────
// 实现一个 ScopeGuard 类，析构时执行用户指定的函数
// 类似 Golang 的 defer

// TODO: 实现 ScopeGuard
// template<typename F>
// class ScopeGuard {
// public:
//     explicit ScopeGuard(F&& f) : f_(std::move(f)) {}
//     ~ScopeGuard() { f_(); }
//     ScopeGuard(const ScopeGuard&) = delete;
//     ScopeGuard& operator=(const ScopeGuard&) = delete;
// private:
//     F f_;
// };

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // try {
    //     Connection conn("mydb");
    //     conn.execute("SELECT * FROM users");
    //     // 即使这里抛异常，conn 的析构函数也会断开连接
    // } catch (...) {
    //     std::cout << "Exception caught, but connection was closed\n";
    // }

    // 练习 2:
    // {
    //     ScopedProfiler prof("expensive_loop");
    //     for (volatile int i = 0; i < 100000000; ++i);
    // }

    // 练习 4:
    // {
    //     auto* data = new int[100];
    //     ScopeGuard guard([&] { delete[] data; });
    //     // 无论怎么退出，data 都会被释放
    // }

    return 0;
}
