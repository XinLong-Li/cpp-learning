// phase2_classes_raii/02_raii/demo.cpp
// 演示：RAII 的核心概念

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <mutex>
#include <stdexcept>

// ── 1. 自定义 RAII 文件句柄 ──────────────────────────────
class FileHandle {
public:
    explicit FileHandle(const char* path, const char* mode) {
        file_ = fopen(path, mode);
        if (!file_) {
            throw std::runtime_error(std::string("Cannot open: ") + path);
        }
        std::cout << "  [RAII] File opened: " << path << '\n';
    }

    ~FileHandle() {
        if (file_) {
            fclose(file_);
            std::cout << "  [RAII] File closed\n";
        }
    }

    // 禁止拷贝
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    // 允许移动
    FileHandle(FileHandle&& other) noexcept : file_(other.file_) {
        other.file_ = nullptr;
        std::cout << "  [RAII] File moved\n";
    }

    FILE* get() const { return file_; }

private:
    FILE* file_ = nullptr;
};

// ── 2. 自定义 RAII 互斥锁包装 ────────────────────────────
class ScopedMutex {
public:
    explicit ScopedMutex(std::mutex& mtx, const char* name = "")
        : mtx_(mtx), name_(name) {
        mtx_.lock();
        std::cout << "  [RAII] Lock acquired";
        if (name_[0]) std::cout << " (" << name_ << ")";
        std::cout << '\n';
    }

    ~ScopedMutex() {
        mtx_.unlock();
        std::cout << "  [RAII] Lock released";
        if (name_[0]) std::cout << " (" << name_ << ")";
        std::cout << '\n';
    }

    ScopedMutex(const ScopedMutex&) = delete;
    ScopedMutex& operator=(const ScopedMutex&) = delete;

private:
    std::mutex& mtx_;
    const char* name_;
};

// ── 3. RAII 日志作用域追踪 ──────────────────────────────
class ScopedTrace {
public:
    explicit ScopedTrace(const char* name) : name_(name) {
        std::cout << ">>> Enter " << name_ << '\n';
    }
    ~ScopedTrace() {
        std::cout << "<<< Exit " << name_ << '\n';
    }

private:
    const char* name_;
};

// ── 4. 演示异常安全 ─────────────────────────────────────
void might_throw() {
    ScopedTrace trace("might_throw");

    // 这些资源会被正确清理，即使抛出异常
    auto data = std::make_unique<int[]>(100);  // RAII 内存
    FileHandle tmp("/tmp/test_raii.txt", "w"); // RAII 文件

    throw std::runtime_error("Something went wrong!");
    // data 和 tmp 的析构函数仍会被调用！
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 最基本的 RAII：作用域退出自动清理
    // ═══════════════════════════════════════════════════════
    {
        ScopedTrace t1("basic_scope");
        std::cout << "  Doing work...\n";
    }  // t1 析构
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 2. 文件 RAII
    // ═══════════════════════════════════════════════════════
    {
        std::cout << "File RAII demo:\n";
        FileHandle fh("/tmp/test_raii.txt", "w");

        // 写点内容
        fprintf(fh.get(), "Hello from RAII!\n");
    }  // 文件自动关闭（即使中途出异常）
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. 锁 RAII
    // ═══════════════════════════════════════════════════════
    std::mutex mtx;
    {
        std::cout << "Lock RAII demo:\n";
        ScopedMutex lock(mtx, "my_lock");
        std::cout << "  Inside critical section\n";
    }  // 锁自动释放
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. 异常安全：RAII 即使在异常中也清理资源
    // ═══════════════════════════════════════════════════════
    std::cout << "Exception safety demo:\n";
    try {
        might_throw();
    } catch (const std::exception& e) {
        std::cout << "  Caught: " << e.what() << '\n';
        std::cout << "  (But all RAII objects were cleaned up!)\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. 标准库中的 RAII
    // ═══════════════════════════════════════════════════════
    std::cout << "Standard library RAII:\n";
    {
        std::lock_guard<std::mutex> lg(mtx);  // std::lock_guard = RAII
        std::unique_ptr<int> ptr = std::make_unique<int>(42);  // RAII
        std::vector<int> v(1000);  // RAII
        std::ifstream file("/tmp/test_raii.txt");  // RAII
        std::cout << "  All RAII-managed resources active\n";
    }  // 全部自动清理
    std::cout << "  All cleaned up\n";

    return 0;
}
