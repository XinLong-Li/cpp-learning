# RAII：资源获取即初始化

## 这是 C++ 最重要的设计哲学

> **在构造函数中获取资源，在析构函数中释放资源。永不手动管理资源的生命周期。**

RAII = **R**esource **A**cquisition **I**s **I**nitialization

---

## 为什么 RAII 如此重要？

### 没有 RAII 的世界（C 风格）—— 地狱

```cpp
void process_file(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) return;

    char* buffer = malloc(1024);
    if (!buffer) {
        fclose(f);  // 别忘清理！
        return;
    }

    Mutex* mtx = mutex_create();
    if (!mtx) {
        free(buffer);
        fclose(f);  // 又一遍！
        return;
    }

    // ... 使用资源 ...
    // 如果这里抛异常怎么办？三层资源都泄漏了！

    mutex_destroy(mtx);
    free(buffer);
    fclose(f);
}
```

### RAII 的世界 —— 天堂

```cpp
void process_file(const char* path) {
    FileHandle file(path, "r");   // 构造函数打开文件
    Buffer buffer(1024);          // 构造函数分配内存
    ScopedLock lock(mtx);         // 构造函数获取锁

    // ... 使用资源 ...
    // 即使抛异常，析构函数也会自动释放所有资源
}   // ← 自动关闭文件、释放内存、释放锁（按构造反序）
```

---

## RAII 的经典例子

### 1. 文件管理
```cpp
class FileHandle {
    FILE* file_;
public:
    explicit FileHandle(const char* path, const char* mode)
        : file_(fopen(path, mode)) {
        if (!file_) throw std::runtime_error("Cannot open file");
    }
    ~FileHandle() { if (file_) fclose(file_); }
    // 禁止拷贝，允许移动
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
    FileHandle(FileHandle&& other) noexcept : file_(other.file_) {
        other.file_ = nullptr;
    }
};
```

### 2. 互斥锁
```cpp
template<typename Mutex>
class ScopedLock {
    Mutex& mtx_;
public:
    explicit ScopedLock(Mutex& mtx) : mtx_(mtx) { mtx_.lock(); }
    ~ScopedLock() { mtx_.unlock(); }
    ScopedLock(const ScopedLock&) = delete;
    ScopedLock& operator=(const ScopedLock&) = delete;
};
```

### 3. 标准库已经帮你做了
- `std::lock_guard` / `std::unique_lock` — 锁管理
- `std::unique_ptr` / `std::shared_ptr` — 内存管理
- `std::ifstream` / `std::ofstream` — 文件管理
- `std::vector` / `std::string` — 动态内存管理

---

## RAII 与异常安全

RAII 是 C++ 异常安全的基石。因为析构函数在栈展开时**保证被调用**，所以：

```cpp
void dangerous() {
    auto data = std::make_unique<BigData>();  // RAII 管理内存
    risky_operation();                         // 即使这里抛异常
    // data 的析构函数仍然会被调用 —— 安全！
}
```

这也是 C++ 没有 `finally` 块的原因——析构函数就是你的 `finally`。

---

## 黄金法则

1. **永远不写裸 `new` 和 `delete`** —— 用智能指针和容器
2. **永远不写裸 `fopen`/`fclose`** —— 用 `fstream`
3. **永远不写裸 `lock`/`unlock`** —— 用 `lock_guard`
4. **析构函数永远不抛异常** —— 如果析构抛异常，栈展开时程序 abort
