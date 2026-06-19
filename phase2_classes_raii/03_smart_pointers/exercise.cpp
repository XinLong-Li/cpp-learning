// phase2_classes_raii/03_smart_pointers/exercise.cpp
// 练习：智能指针

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ── 练习 1：用 unique_ptr 管理资源 ────────────────────
// 创建一个 TreeNode 类，它有一个 unique_ptr<TreeNode> left 和 right
// 实现 insert 方法在左/右子树插入

// TODO: 实现
// struct TreeNode {
//     int value;
//     std::unique_ptr<TreeNode> left;
//     std::unique_ptr<TreeNode> right;
//
//     explicit TreeNode(int v) : value(v) {}
//
//     void insert(int v) {
//         // 小于当前值 → 左子树，大于 → 右子树
//     }
// };

// ── 练习 2：观察者指针模式 ──────────────────────────
// 有一个 Game 对象（由 unique_ptr 拥有），多个 Player 观察它
// Player 不拥有 Game，只是引用

// TODO: 实现
// class Game {
// public:
//     Game(std::string name) : name_(std::move(name)) {}
//     std::string name() const { return name_; }
// private:
//     std::string name_;
// };
//
// class Player {
//     std::string name_;
//     Game* game_;  // 原始指针表示"不拥有"
// public:
//     Player(std::string name, Game* game)
//         : name_(std::move(name)), game_(game) {}
//     void info() const {
//         std::cout << name_ << " playing " << game_->name() << '\n';
//     }
// };

// ── 练习 3：找出内存问题 ────────────────────────────
// 下面的代码有内存泄漏吗？

void exercise3() {
    // Case A:
    {
        auto sp = std::make_shared<int>(42);
        auto* raw = sp.get();  // 有内存泄漏吗？
    }

    // Case B:
    {
        std::shared_ptr<int> sp1 = std::make_shared<int>(10);
        std::shared_ptr<int> sp2 = std::make_shared<int>(20);
        sp1 = sp2;  // 原来的 sp1 指向的对象会被 delete 吗？
    }

    // Case C:
    {
        auto up = std::make_unique<int>(99);
        // 忘记写 std::move 会怎样？
        // auto up2 = up;  // 能编译吗？
    }
}

// ── 练习 4：实现双向链表（无泄漏） ─────────────────────

// TODO: 实现一个双向链表节点
// next 用 shared_ptr, prev 用 weak_ptr
// struct DoublyNode {
//     int value;
//     std::shared_ptr<DoublyNode> next;
//     std::weak_ptr<DoublyNode> prev;
//
//     DoublyNode(int v) : value(v) {}
// };

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // auto root = std::make_unique<TreeNode>(50);
    // root->insert(30);
    // root->insert(70);
    // root->insert(20);

    // 练习 2:
    // auto game = std::make_unique<Game>("C++ Quest");
    // Player p1("alice", game.get());
    // Player p2("bob", game.get());
    // p1.info(); p2.info();

    exercise3();
    return 0;
}
