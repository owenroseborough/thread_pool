# Thread Utilities and Synced Stream in C++20

This project provides C++20 utilities for multithreaded programming, including:

- A **thread-safe synchronized stream** class for logging to multiple `std::ostream` targets
- A skeleton for a **thread pool** supporting task submission and timed waiting
- A **multi_future** class to manage and operate over multiple `std::future<T>` objects
- Use of **C++20 concepts** to constrain templates with type safety (e.g., chrono durations)

---

## Components

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
```

---

### 2. `multi_future<T>` *(commented out in current version)*

A wrapper around a `std::vector<std::future<T>>`, offering:

- Waiting on all futures
- Getting all results as a `std::vector<T>`
- Checking readiness and validity
- Time-bound waits using `wait_for()` and `wait_until()`

---

### 3. `ThreadPool` *(commented out in current version)*

A planned thread pool implementation with support for:

- Task submission via `submit_task()`
- Detaching background tasks
- Waiting on task completion with or without timeouts
- Functional initialization and cleanup hooks per thread
- Loop-based bulk submission interfaces with customizable block counts
- Future-based sequence task submission with `multi_future<T>`

---

### 4. `IsChronoTime` Concept

A reusable **C++20 concept** to restrict template parameters to valid `std::chrono::duration` types like `seconds`, `milliseconds`, etc.

```cpp
template<typename Time>
concept IsChronoTime = std::is_same_v<Time, std::chrono::nanoseconds> ||
                       std::is_same_v<Time, std::chrono::microseconds> ||
                       std::is_same_v<Time, std::chrono::milliseconds> ||
                       std::is_same_v<Time, std::chrono::seconds> ||
                       std::is_same_v<Time, std::chrono::minutes> ||
                       std::is_same_v<Time, std::chrono::hours>;
```

---

## Requirements

- **C++20 compiler**
- Recommended: Visual Studio 2022 or g++/clang++ with `-std=c++20`
- Use `/std:c++20` or `-std=c++20` flag when compiling

---

## Notes

- `ThreadPool` and `multi_future` are currently **scaf**_
