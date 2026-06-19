// phase5_cpp17_library/03_structured_bindings/demo.cpp
// 演示：C++17 结构化绑定

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>
#include <array>

// ── 支持结构化绑定的 struct ───────────────────────────
struct Rectangle {
    double width;
    double height;
};

// ── 返回多值的函数 ──────────────────────────────────
std::tuple<std::string, int, double> get_student_info() {
    return {"Alice", 2021001, 3.8};
}

// ── 主函数 ───────────────────────────────────────────────
int main() {
    // ═══════════════════════════════════════════════════════
    // 1. pair / tuple 解构
    // ═══════════════════════════════════════════════════════
    std::pair<std::string, int> p{"age", 30};
    auto [label, value] = p;
    std::cout << label << ": " << value << '\n';

    auto [id, score] = std::make_pair(42, 95.5);
    std::cout << id << " scored " << score << "\n\n";

    // ═══════════════════════════════════════════════════════
    // 2. 自定义 struct
    // ═══════════════════════════════════════════════════════
    Rectangle rect{3.0, 4.0};
    auto [w, h] = rect;  // 按声明顺序绑定到字段
    std::cout << "Rectangle: " << w << " x " << h
              << " (area=" << w * h << ")\n\n";

    // ═══════════════════════════════════════════════════════
    // 3. map 遍历（这是最有用的场景）
    // ═══════════════════════════════════════════════════════
    std::map<std::string, int> ages = {
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}
    };

    for (const auto& [name, age] : ages) {
        std::cout << name << " is " << age << " years old\n";
    }
    std::cout << '\n';

    // ═══════════════════════════════════════════════════════
    // 4. insert 返回值
    // ═══════════════════════════════════════════════════════
    auto [it, inserted] = ages.insert({"David", 40});
    if (inserted) {
        std::cout << "Inserted David\n";
    } else {
        std::cout << "David already exists with age " << it->second << '\n';
    }

    // 重复插入
    auto [it2, inserted2] = ages.insert({"Alice", 99});
    if (!inserted2) {
        std::cout << "Alice already exists with age " << it2->second << "\n\n";
    }

    // ═══════════════════════════════════════════════════════
    // 5. 多返回值
    // ═══════════════════════════════════════════════════════
    auto [name, student_id, gpa] = get_student_info();
    std::cout << "Student: " << name << " (ID:" << student_id
              << ", GPA:" << gpa << ")\n\n";

    // ═══════════════════════════════════════════════════════
    // 6. 数组解构
    // ═══════════════════════════════════════════════════════
    int arr[] = {10, 20, 30};
    auto& [a, b, c] = arr;
    a = 100;  // 修改了 arr[0]
    std::cout << "arr after modification: "
              << arr[0] << ", " << arr[1] << ", " << arr[2] << '\n';

    return 0;
}
