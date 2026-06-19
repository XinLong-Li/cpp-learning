// phase4_templates/02_class_templates/exercise.cpp
// 练习：类模板

#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <array>

// ── 练习 1：实现 Pair 类模板 ──────────────────────────
// 存储两个任意类型的值，有 first() 和 second() getter

// TODO: 实现
// template<typename T1, typename T2>
// class Pair {
// public:
//     Pair(const T1& first, const T2& second)
//         : first_(first), second_(second) {}
//
//     const T1& first() const { return first_; }
//     const T2& second() const { return second_; }
// private:
//     T1 first_;
//     T2 second_;
// };

// ── 练习 2：实现 LRU Cache ────────────────────────────
// 固定容量，最近最少使用淘汰
// 提示：用 vector<pair<K,V>> 或 list + unordered_map

// template<typename K, typename V, size_t Capacity>
// class LRUCache {
// public:
//     std::optional<V> get(const K& key);
//     void put(const K& key, const V& value);
//     size_t size() const;
// private:
//     // 你的实现
// };

// ── 练习 3：模板的模板参数 ──────────────────────────
// 实现一个 Adapter 类模板，它包装一个容器类型
// 例如 Adapter<std::vector, int> 包装一个 vector<int>

// TODO: 实现
// template<template<typename...> class Container, typename T>
// class Adapter {
// public:
//     void add(const T& val) { data_.push_back(val); }
//     // ...
// private:
//     Container<T> data_;
// };

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // Pair<std::string, int> p("age", 30);
    // std::cout << p.first() << ": " << p.second() << '\n';

    // 练习 2:
    // LRUCache<std::string, int, 3> cache;
    // cache.put("a", 1); cache.put("b", 2); cache.put("c", 3);
    // cache.put("d", 4);  // 淘汰 "a"
    // std::cout << cache.get("a").value_or(-1) << '\n'; // -1 (evicted)

    return 0;
}
