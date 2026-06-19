// phase5_cpp17_library/04_filesystem/exercise.cpp
// 练习：std::filesystem

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>

namespace fs = std::filesystem;

// ── 练习 1：查找所有特定扩展名的文件 ─────────────────

// TODO: 实现 find_by_extension
// std::vector<fs::path> find_by_extension(const fs::path& dir,
//                                          const std::string& ext,
//                                          bool recursive = true) {
//     // 你的代码
// }

// ── 练习 2：计算目录总大小 ──────────────────────────
// 递归计算一个目录下所有文件的大小之和

// TODO: 实现
// uintmax_t dir_size(const fs::path& dir) {
//     // 你的代码
// }

// ── 练习 3：实现磁盘使用统计 ──────────────────────────
// 列出当前目录下每个子目录的大小（降序排列）
// 提示：用 filesystem + map + sort

// TODO: 实现
// void disk_usage_report(const fs::path& dir) {
//     // 你的代码
// }

// ── 练习 4：安全文件写入 ────────────────────────────
// 先写临时文件，然后重命名（原子操作）
// 避免写入过程中断导致文件损坏

// TODO: 实现
// void safe_write(const fs::path& path, const std::string& content) {
//     auto tmp = path;
//     tmp += ".tmp";
//     std::ofstream(tmp) << content;
//     fs::rename(tmp, path);
// }

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // 练习 1:
    // auto cpp_files = find_by_extension(".", ".cpp");
    // for (const auto& f : cpp_files) std::cout << f << '\n';

    // 练习 2:
    // std::cout << "Current dir size: " << dir_size(".") << " bytes\n";

    // 练习 3:
    // disk_usage_report(".");

    return 0;
}
