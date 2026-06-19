// phase7_projects/03_csv_parser/csv_parser.hpp
// CSV Parser 骨架

#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <tuple>
#include <functional>
#include <algorithm>
#include <fstream>

// ═══════════════════════════════════════════════════════════
// Helper: 字符串分割（零拷贝）
// ═══════════════════════════════════════════════════════════
inline std::vector<std::string_view> split_line(std::string_view line, char delim = ',') {
    std::vector<std::string_view> parts;
    size_t start = 0;
    while (start <= line.size()) {
        auto end = line.find(delim, start);
        if (end == std::string_view::npos) end = line.size();
        parts.push_back(line.substr(start, end - start));
        start = end + 1;
    }
    return parts;
}

// ═══════════════════════════════════════════════════════════
// CSV Table 模板（简化版，仅支持相同类型列）
// ═══════════════════════════════════════════════════════════
template<typename T>
class SimpleCsvTable {
public:
    using Row = std::vector<T>;

    // 加载 CSV
    static SimpleCsvTable load(const std::string& path, char delim = ',') {
        SimpleCsvTable table;
        std::ifstream file(path);
        std::string line;

        // 读取表头
        if (std::getline(file, line)) {
            table.headers_ = split_line(line, delim);
        }

        // 读取数据
        while (std::getline(file, line)) {
            auto parts = split_line(line, delim);
            Row row;
            for (auto part : parts) {
                T value{};
                std::string s(part);
                std::istringstream iss(s);
                iss >> value;
                row.push_back(value);
            }
            if (!row.empty()) table.rows_.push_back(std::move(row));
        }
        return table;
    }

    // 过滤
    SimpleCsvTable where(std::function<bool(const Row&)> pred) const {
        SimpleCsvTable result;
        result.headers_ = headers_;
        std::copy_if(rows_.begin(), rows_.end(),
            std::back_inserter(result.rows_), pred);
        return result;
    }

    // 排序（按某列）
    void sort_by(size_t col) {
        std::sort(rows_.begin(), rows_.end(),
            [col](const Row& a, const Row& b) {
                return a[col] < b[col];
            });
    }

    // 打印
    void print() const {
        for (size_t i = 0; i < headers_.size(); ++i) {
            std::cout << headers_[i];
            if (i < headers_.size() - 1) std::cout << "\t";
        }
        std::cout << '\n';
        std::cout << std::string(80, '-') << '\n';

        for (const auto& row : rows_) {
            for (size_t i = 0; i < row.size(); ++i) {
                std::cout << row[i];
                if (i < row.size() - 1) std::cout << "\t";
            }
            std::cout << '\n';
        }
    }

    size_t row_count() const { return rows_.size(); }
    size_t col_count() const { return headers_.size(); }

private:
    std::vector<std::string_view> headers_;
    std::vector<Row> rows_;
};
