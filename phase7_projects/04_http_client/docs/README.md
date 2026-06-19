# 项目 4：简单 HTTP 客户端

## 涉及知识点

- Socket 编程（POSIX/BSD Sockets）
- RAII（Socket 管理）
- `std::string_view`（响应解析）
- `std::optional`（超时处理）
- `std::variant`（响应结果或错误）
- 移动语义（大数据传输）

## 设计

```cpp
class HttpClient {
public:
    struct Response {
        int status_code;
        std::string status_message;
        std::unordered_map<std::string, std::string> headers;
        std::string body;
    };

    // 发送 GET 请求
    std::variant<Response, std::string> get(const std::string& url,
        std::chrono::milliseconds timeout = std::chrono::seconds(5));

    // 发送 POST 请求
    std::variant<Response, std::string> post(const std::string& url,
        const std::string& body,
        const std::string& content_type = "application/json",
        std::chrono::milliseconds timeout = std::chrono::seconds(5));
};
```

## 功能

- URL 解析（host, port, path）
- TCP 连接（`socket()`, `connect()`）
- HTTP 请求构造
- HTTP 响应解析（状态行、头部、body）
- 超时处理（`setsockopt(SO_RCVTIMEO)`）
- 支持 HTTP/1.1

## 简化方案

如果想简化，可以用 `libcurl`。但学习目的建议手工实现。

## 文件结构

```
phase7_projects/04_http_client/
├── docs/
│   └── README.md
├── http_client.hpp
├── main.cpp
└── CMakeLists.txt
```
