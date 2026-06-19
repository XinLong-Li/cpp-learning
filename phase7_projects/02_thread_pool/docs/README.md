# 项目 2：简单线程池

## 涉及知识点

- `std::thread`, `std::mutex`, `std::condition_variable`
- `std::future`, `std::packaged_task`, `std::promise`
- `std::queue`
- RAII（线程生命周期管理）
- 移动语义（任务传递）

## 核心设计

```cpp
class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads);
    ~ThreadPool();

    // 提交任务，返回 future
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<F, Args...>>;

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex queue_mutex_;
    std::condition_variable cv_;
    bool stop_ = false;
};
```

## 工作流程

1. 构造函数启动 N 个工作线程
2. 每个线程在循环中等待任务（`condition_variable::wait`）
3. `submit()` 将任务包装成 `std::function<void()>` 放入队列
4. 析构函数设置 `stop_` 标志，通知所有线程退出，然后 `join()`

## 文件结构

```
phase7_projects/02_thread_pool/
├── docs/
│   └── README.md
├── ThreadPool.hpp
├── main.cpp
└── CMakeLists.txt
```
