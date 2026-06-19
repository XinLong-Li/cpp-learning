# 项目 3：CSV 解析器

## 涉及知识点

- 模板（泛型列类型支持）
- `std::string_view`（零拷贝解析）
- STL 算法（过滤、排序、聚合）
- `std::variant`（混合类型列）
- `std::optional`
- 类模板 + 成员函数模板

## 设计

```cpp
// CSV 表
template<typename... ColumnTypes>
class CsvTable {
public:
    // 从文件加载
    static CsvTable load(std::string_view path);

    // 查询操作
    CsvTable where(std::function<bool(ColumnTypes...)> predicate) const;
    CsvTable order_by(size_t column_index) const;
    CsvTable select(size_t... columns) const;

    // 聚合
    double sum(size_t column) const;
    double avg(size_t column) const;
    size_t count() const;

    // 输出
    void print() const;
    void save(std::string_view path) const;
};
```

## 使用示例

```cpp
// 加载 CSV：name, age, salary
auto table = CsvTable<std::string, int, double>::load("data.csv");

// 过滤 + 排序
auto result = table
    .where([](const std::string& name, int age, double salary) {
        return age > 30 && salary > 50000;
    })
    .order_by(1);  // 按 age 排

result.print();
```

## 文件结构

```
phase7_projects/03_csv_parser/
├── docs/
│   └── README.md
├── csv_parser.hpp
├── main.cpp
└── CMakeLists.txt
```
