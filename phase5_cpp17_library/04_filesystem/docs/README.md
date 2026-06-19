# `std::filesystem`：跨平台文件操作

## 告别 POSIX API

```cpp
// ❌ 旧式：POSIX 平台特定 API
#include <dirent.h>
#include <sys/stat.h>

// ✅ 现代 C++：跨平台标准库
#include <filesystem>
namespace fs = std::filesystem;
```

---

## 常见操作

```cpp
#include <filesystem>
namespace fs = std::filesystem;

// 路径操作
fs::path p = "/home/user/docs/file.txt";
p.filename();        // "file.txt"
p.stem();            // "file"
p.extension();       // ".txt"
p.parent_path();     // "/home/user/docs"
p.root_path();       // "/"
p.replace_extension(".md");  // /home/user/docs/file.md

// 路径拼接
auto full = fs::path("/home") / "user" / "docs" / "file.txt";

// 检查文件状态
fs::exists(p);               // 存在？
fs::is_regular_file(p);      // 是普通文件？
fs::is_directory(p);         // 是目录？
fs::file_size(p);            // 文件大小
fs::last_write_time(p);      // 最后修改时间

// 目录操作
fs::create_directory("new_dir");
fs::create_directories("a/b/c");     // 递归创建
fs::remove("file.txt");              // 删除文件
fs::remove_all("directory");         // 递归删除

// 遍历目录
for (const auto& entry : fs::directory_iterator("path")) {
    std::cout << entry.path().filename() << '\n';
}

// 递归遍历
for (const auto& entry : fs::recursive_directory_iterator("path")) {
    std::cout << entry.path() << '\n';
}
```

---

## 操作汇总

| 操作 | 函数 |
|------|------|
| 是否存在 | `fs::exists(p)` |
| 是否文件 | `fs::is_regular_file(p)` |
| 是否目录 | `fs::is_directory(p)` |
| 创建目录 | `fs::create_directory(p)` / `fs::create_directories(p)` |
| 删除文件 | `fs::remove(p)` |
| 删除目录（递归） | `fs::remove_all(p)` |
| 复制 | `fs::copy(src, dst)` |
| 重命名 | `fs::rename(old, new)` |
| 当前路径 | `fs::current_path()` |
| 临时目录 | `fs::temp_directory_path()` |
| 遍历目录 | `fs::directory_iterator(p)` |
| 递归遍历 | `fs::recursive_directory_iterator(p)` |

---

## 错误处理

文件系统操作可能失败。两种处理方式：

```cpp
// 方式 1：异常
try {
    fs::remove("nonexistent.txt");
} catch (const fs::filesystem_error& e) {
    std::cerr << e.what() << '\n';
}

// 方式 2：错误码
std::error_code ec;
fs::remove("nonexistent.txt", ec);
if (ec) {
    std::cerr << ec.message() << '\n';
}
```
