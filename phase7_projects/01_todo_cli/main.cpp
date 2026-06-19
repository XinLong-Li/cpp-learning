// phase7_projects/01_todo_cli/main.cpp
// TODO CLI — 命令行 TODO 管理工具骨架

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <algorithm>
#include <fstream>
#include <filesystem>

// ═══════════════════════════════════════════════════════════
// Data Structures
// ═══════════════════════════════════════════════════════════
struct TodoItem {
    int id;
    std::string title;
    bool done = false;
    std::string priority = "medium";
    std::string tag;
};

class TodoApp {
public:
    // TODO: 实现 add
    void add(std::string_view title, std::string_view priority,
             std::string_view tag) {
        // items_.push_back({next_id_++, std::string(title), false,
        //                   std::string(priority), std::string(tag)});
        std::cout << "Added: #" << next_id_ << " " << title << '\n';
    }

    // TODO: 实现 list（支持按 tag 过滤）
    void list(std::optional<std::string_view> tag_filter = std::nullopt) const {
        for (const auto& item : items_) {
            if (tag_filter && item.tag != *tag_filter) continue;
            std::cout << (item.done ? "[x]" : "[ ]") << " #" << item.id
                      << " " << item.title << " | " << item.priority
                      << " | " << item.tag << '\n';
        }
    }

    // TODO: 实现 done
    void done(int id) {
        // 用 find_if 查找
        std::cout << "Done #" << id << '\n';
    }

    // TODO: 实现 remove (Erase-Remove idiom)
    void remove(int id) {
        // items_.erase(std::remove_if(...), items_.end());
        std::cout << "Removed #" << id << '\n';
    }

    // TODO: 实现 save (用 ofstream)
    void save(const std::string& path) const {
        // 将 items_ 写入文件
        std::cout << "Saved to " << path << '\n';
    }

    // TODO: 实现 load
    void load(const std::string& path) {
        // 从文件读取
        std::cout << "Loaded from " << path << '\n';
    }

private:
    std::vector<TodoItem> items_;
    int next_id_ = 1;
};

// ═══════════════════════════════════════════════════════════
// Command Parser (simplified)
// ═══════════════════════════════════════════════════════════
void print_usage() {
    std::cout << "Commands:\n"
              << "  add <title> [--priority=high|medium|low] [--tag=<tag>]\n"
              << "  list [--tag=<tag>]\n"
              << "  done <id>\n"
              << "  remove <id>\n"
              << "  save [path]\n"
              << "  load [path]\n"
              << "  help\n"
              << "  exit\n";
}

// ═══════════════════════════════════════════════════════════
int main() {
    TodoApp app;
    print_usage();

    std::string line;
    while (true) {
        std::cout << "\ntodo> ";
        if (!std::getline(std::cin, line) || line == "exit") break;

        if (line == "help") {
            print_usage();
        } else if (line == "list") {
            app.list();
        } else if (line.starts_with("add ")) {
            // TODO: 解析命令
            app.add("example task", "medium", "general");
        } else {
            std::cout << "Unknown command. Type 'help'.\n";
        }
    }

    return 0;
}
