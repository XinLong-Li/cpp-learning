// phase5_cpp17_library/04_filesystem/demo.cpp
// 演示：std::filesystem 文件操作

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem;

// ── 辅助：创建测试文件 ──────────────────────────────────
void setup_test_files(const fs::path& dir) {
    fs::create_directories(dir / "subdir");
    std::ofstream(dir / "file1.txt") << "Hello";
    std::ofstream(dir / "file2.txt") << "World";
    std::ofstream(dir / "subdir" / "nested.txt") << "Nested";
}

// ── 清理测试文件 ──────────────────────────────────────
void cleanup(const fs::path& dir) {
    std::error_code ec;
    fs::remove_all(dir, ec);
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. 路径操作
    // ═══════════════════════════════════════════════════════
    fs::path original = "/home/user/docs/report.txt";

    std::cout << "Original: " << original << '\n';
    std::cout << "  filename:  " << original.filename() << '\n';
    std::cout << "  stem:      " << original.stem() << '\n';
    std::cout << "  extension: " << original.extension() << '\n';
    std::cout << "  parent:    " << original.parent_path() << '\n';

    // 修改扩展名
    auto modified = original;
    modified.replace_extension(".pdf");
    std::cout << "  as pdf:    " << modified << '\n';

    // 路径拼接
    auto joined = fs::path("/tmp") / "learning-cpp" / "test.txt";
    std::cout << "  joined:    " << joined << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. 目录和文件操作
    // ═══════════════════════════════════════════════════════
    fs::path test_dir = fs::temp_directory_path() / "cpp_learning_fs_demo";
    setup_test_files(test_dir);

    std::cout << "Test directory: " << test_dir << '\n';
    std::cout << "Exists: " << fs::exists(test_dir) << '\n';
    std::cout << "Is directory: " << fs::is_directory(test_dir) << '\n';
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 3. 遍历目录
    // ═══════════════════════════════════════════════════════
    std::cout << "Directory listing (non-recursive):\n";
    for (const auto& entry : fs::directory_iterator(test_dir)) {
        std::cout << "  " << entry.path().filename()
                  << (entry.is_directory() ? "/" : "")
                  << " (" << (entry.is_regular_file() ?
                      std::to_string(entry.file_size()) + " bytes" : "") << ")\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. 递归遍历
    // ═══════════════════════════════════════════════════════
    std::cout << "Recursive listing:\n";
    for (const auto& entry : fs::recursive_directory_iterator(test_dir)) {
        auto rel = fs::relative(entry.path(), test_dir);
        std::cout << "  " << rel;
        if (entry.is_regular_file()) {
            std::cout << " (" << entry.file_size() << " bytes)";
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 5. 错误处理（用 error_code 不抛异常）
    // ═══════════════════════════════════════════════════════
    std::error_code ec;
    auto exists = fs::exists("/this/does/not/exist", ec);
    std::cout << "/this/does/not/exist exists: " << exists
              << " (ec: " << ec.value() << ")\n";

    // 清理
    cleanup(test_dir);
    std::cout << "Cleaned up test directory\n";

    return 0;
}
