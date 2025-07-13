# 🧵   Thread Pool, Thread Utilities and Synced Stream in C++20

This project provides C++20 utilities for multithreaded programming, including:

- A **thread-safe synchronized stream** class for logging to multiple `std::ostream` targets
- A skeleton for a **thread pool** supporting task submission and timed waiting
- A **multi_future** class to manage and operate over multiple `std::future<T>` objects
- Use of **C++20 concepts** to constrain templates with type safety (e.g., chrono durations)

---

## 📦 Components

### 1. `synced_stream`

A class that enables thread-safe logging to multiple output streams simultaneously.

#### Features:

- Print to `std::cout`, file streams, or custom `std::ostream*`s
- Thread-safe via `std::mutex`
- Supports `print(...)` and `println(...)` methods with variadic arguments
- Custom `endl()` and `flush()` methods for safe flushing

#### Example:

```cpp
synced_stream out;
out.print("Hello, world!");
out.println("Thread-safe log line #", 1);
out.endl();

