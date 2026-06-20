// phase7_projects/03_csv_parser/test.cpp
// CSV Parser 编译验证和基本功能测试

#include "csv_parser.hpp"
#include <iostream>
#include <cassert>
#include <sstream>

int main() {
    // 1. split_line 测试
    {
        auto parts = split_line("a,b,c,d", ',');
        assert(parts.size() == 4);
        assert(parts[0] == "a");
        assert(parts[1] == "b");
        assert(parts[2] == "c");
        assert(parts[3] == "d");
        std::cout << "[PASS] split_line works\n";
    }

    // 2. 手动构造 SimpleCsvTable<int>
    {
        // 用字符串流模拟 CSV 文件
        std::string csv_data = "col1,col2,col3\n1,2,3\n4,5,6\n10,20,30\n";
        std::stringstream ss(csv_data);

        // 写临时文件（因为 load 需要路径）
        std::ofstream tmp("/tmp/test_csv.csv");
        tmp << csv_data;
        tmp.close();

        auto table = SimpleCsvTable<int>::load("/tmp/test_csv.csv");
        assert(table.row_count() == 3);
        assert(table.col_count() == 3);
        std::cout << "[PASS] SimpleCsvTable<int> loaded: "
                  << table.row_count() << " rows, "
                  << table.col_count() << " cols\n";
    }

    // 3. where 过滤测试
    {
        std::string csv_data = "value\n1\n2\n3\n4\n5\n";
        std::ofstream tmp("/tmp/test_filter.csv");
        tmp << csv_data;
        tmp.close();

        auto table = SimpleCsvTable<int>::load("/tmp/test_filter.csv");
        auto filtered = table.where([](const std::vector<int>& row) {
            return row[0] > 3;
        });
        assert(filtered.row_count() == 2);
        std::cout << "[PASS] where() filter: " << filtered.row_count() << " rows\n";
    }

    std::cout << "\nAll tests passed!\n";
    return 0;
}
