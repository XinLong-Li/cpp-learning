// phase7_projects/02_thread_pool/ThreadPool.hpp
// 简单线程池骨架

#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <type_traits>

class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads) {
        // TODO: 创建 num_threads 个工作线程
        // 每个线程执行 worker_loop()
    }

    ~ThreadPool() {
        // TODO:
        // 1. 设置 stop_ = true
        // 2. notify_all()
        // 3. join 所有线程
    }

    // 提交任务并返回 future
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<F, Args...>>
    {
        using return_type = std::invoke_result_t<F, Args...>;

        // 用 packaged_task + shared_ptr 包装任务
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> result = task->get_future();

        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            if (stop_) {
                throw std::runtime_error("submit on stopped ThreadPool");
            }
            // 将 task 包装成 void() 放入队列
            tasks_.emplace([task]() { (*task)(); });
        }

        cv_.notify_one();
        return result;
    }

private:
    void worker_loop() {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                // TODO: 等待直到有任务或 stop_
                cv_.wait(lock, [this] {
                    return stop_ || !tasks_.empty();
                });

                if (stop_ && tasks_.empty()) return;

                task = std::move(tasks_.front());
                tasks_.pop();
            }

            task();  // 执行任务
        }
    }

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queue_mutex_;
    std::condition_variable cv_;
    bool stop_ = false;
};
