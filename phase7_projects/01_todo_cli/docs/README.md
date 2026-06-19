# 项目 1：命令行 TODO 工具

## 目标

实现一个命令行 TODO 管理工具，巩固阶段 1-5 的知识。

## 涉及知识点

- `std::string`, `std::string_view`
- `std::vector`, `std::map`
- `std::optional`
- 结构化绑定
- `std::filesystem`（数据持久化）
- Lambda + STL 算法
- 类与 RAII

## 功能需求

```bash
$ ./todo add "Learn C++" --priority=high --tag=coding
# Added: [1] Learn C++ (priority: high, tag: coding)

$ ./todo list
#  1. [ ] Learn C++          | high   | coding
#  2. [x] Buy groceries        | medium | life

$ ./todo done 1
# Marked #1 as done: Learn C++

$ ./todo list --tag=coding
#  1. [ ] Learn C++          | high   | coding

$ ./todo remove 1
# Removed #1: Learn C++

$ ./todo save    # 保存到 ~/.todo.json
$ ./todo load    # 从 ~/.todo.json 加载
```

## 数据结构建议

```cpp
struct TodoItem {
    int id;
    std::string title;
    bool done = false;
    std::string priority;  // "low", "medium", "high"
    std::string tag;
};

class TodoApp {
    std::vector<TodoItem> items_;
    int next_id_ = 1;

    void add(std::string_view title, std::string_view priority, std::string_view tag);
    void list(std::optional<std::string_view> tag_filter = std::nullopt);
    void done(int id);
    void remove(int id);
    void save(const std::string& path);
    void load(const std::string& path);
};
```

## 文件结构

```
phase7_projects/01_todo_cli/
├── docs/
│   └── README.md
├── main.cpp
└── CMakeLists.txt
```

## 扩展方向

- 用 `nlohmann/json` 库做 JSON 序列化
- 支持截止日期
- 支持多个 TODO 列表
