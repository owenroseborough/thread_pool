#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <stdexcept>
#include <ostream>
#include <iostream>

template<typename Time>
concept IsChronoTime = std::is_same<std::chrono::nanoseconds, Time>::value ||
                        std::is_same<std::chrono::microseconds, Time>::value ||
                        std::is_same<std::chrono::milliseconds, Time>::value ||
                        std::is_same<std::chrono::seconds, Time>::value ||
                        std::is_same<std::chrono::minutes, Time>::value ||
                        std::is_same<std::chrono::hours, Time>::value;

class ThreadPool {
private:
    int count_;
    std::function<void(std::optional<size_t>)> initFunction_;
    std::function<void(std::optional<size_t>)> cleanupFunction_;
public:
    ThreadPool(std::function<void(std::optional<size_t>)> initFunc) : count_(0), initFunction_(initFunc) {};

    ThreadPool(int num, std::function<void(std::optional<size_t>)> initFunc) : count_(num), initFunction_(initFunc) {};

    size_t get_thread_count() {
        return count_;
    }

    void reset(int numThreads) {

    }

    std::vector<std::thread::id> get_thread_ids() {

    }

    void detach_task(std::function<void()> task) {

    }

    void wait() {

    }

    size_t get_tasks_queued() {

    }

    size_t get_tasks_running() {

    }

    size_t get_tasks_total() {

    }

    void set_cleanup_func(std::function<void(std::optional<size_t>)> cleanupFunc) {
        cleanupFunction_ = cleanupFunc;
    }

    //Once purge() is called, any tasks still waiting in the queue will be discarded
    void purge() {

    }

    template<typename T>
    [[nodiscard]] std::future<T> submit_task(std::function<T()> task) {
        //TODO: template method has to be implemented in interface file
    }

    void detach_task(std::function<void()> task);

    void wait(); //wait for all the tasks in the queue to complete
                 //other tasks may be submitted while we are waiting

    template<IsChronoTime T>
    std::future_status wait_for(std::chrono::duration<T> duration) {
        //TODO: template method has to be implemented in interface file
        //TODO: have to put template constraints on template parameter,
        //      must be sub type of std::chrono
    }

    template<IsChronoTime T>
    std::future_status wait_until(std::chrono::time_point<T> timePoint) {
        //TODO: template method has to be implemented in interface file
        //TODO: have to put template constraints on template parameter,
        //      must be sub type of std::chrono
    }

    template<IsChronoTime T>
    bool wait_for(std::chrono::duration<T> duration) { //waits on all tasks, submitted and detached
        //TODO: template method has to be implemented in interface file
        //TODO: have to put template constraints on template parameter,
        //      must be sub type of std::chrono
    }

    template<IsChronoTime T>
    bool wait_until(std::chrono::time_point<T> timePoint) { //waits on all tasks, submitted and detached
        //TODO: template method has to be implemented in interface file
        //TODO: have to put template constraints on template parameter,
        //      must be sub type of std::chrono
    }

    //use concepts to verify start and end types coalesce into correct W type
    template<typename T, typename U, typename V, typename W>
    multi_future<void> submit_loop(U start, V end, std::function<void()> loop, size_t num_blocks = 10){
        //TODO: template method has to be implemented in interface file
        for (W i = start; i < end; ++i)
            loop(i);
    }

    //use concepts to verify start and end
    template<typename T, typename U, typename V, typename W>
    void detach_loop(U start, V end, std::function<void()> loop, size_t num_blocks = 10) {
        //TODO: template method has to be implemented in interface file
        for (W i = start; i < end; ++i)
            loop(i);
    }

    //use concepts to verify start and end types coalesce into correct W type
    template<typename T, typename U, typename V, typename W>
    multi_future<T> submit_blocks(U start, V end, std::function<void()> loop, size_t num_blocks = 10) {
        //TODO: template method has to be implemented in interface file
        loop(i);
    }

    //use concepts to verify start and end types coalesce into correct W type
    template<typename T, typename U, typename V, typename W>
    void detach_blocks(U start, V end, std::function<void()> loop, size_t num_blocks = 10) {
        //TODO: template method has to be implemented in interface file
        loop(i);
    }

    template<typename T, typename U, typename V, typename W>
    multi_future<T> submit_sequence(U start, V end, std::function<void()> callable) {
        //TODO: template method has to be implemented in interface file
    }

    template<typename T, typename U, typename V, typename W>
    void detach_sequence(U start, V end, std::function<void()> callable) {
        //TODO: template method has to be implemented in interface file
    }
};

template<typename T>
class multi_future {
private:
    std::vector<std::future<T>> futures;
public:
    multi_future() {};

    multi_future(size_t num_futures) : futures(num_futures, std::future<T> future) {}
    
    std::future<T>& operator[](size_t index) {
        return futures.at(index);
    }

    void push_back(std::future<T> future) {
        futures.push_back(future);
    }

    void reserve(size_t size) {
        futures.reserve(size);
    }

    size_t size() {
        return futures.size();
    }

    //wait for all futures to be completed
    void wait() {
        for (auto future: futures) {
            future.wait();
        }
    }

    //get results for all futures
    std::vector<T> get() {
        std::vector<T> results;
        for (auto future : futures) {
            if (!future.valid())
                throw std::future_error(std::make_error_code(std::future_errc::no_state));
            results.push_back(future.get());
        }
        return results;
    }

    //check how many futures are ready
    size_t ready_count() {
        size_t num_ready{};
        for (auto future: futures) {
            if (future.valid())
                num_ready++;
        }
        return num_ready;
    }

    //check if all the stored futures are valid
    bool valid() {
        for (auto future : futures) {
            if (!future.valid())
                return false;
        }
        return true;
    }

    //wait for all the stored futures for a specific duration
    template<IsChronoTime U>
    bool wait_for(std::chrono::duration<U> duration) {
        const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
        for (auto future : futures) {
            future.wait_for(duration);
        }
        const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        if (end - start < duration)
            return true;
        return false;
    }

    //wait until a specific time
    template<IsChronoTime U>
    bool wait_until(std::chrono::time_point<U> timePoint) {
        for (auto future : futures) {
            future.wait_until(timePoint);
        }
        const std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        if (end < timePoint)
            return true;
        return false;
    }
};

class synced_stream {
private:
    std::vector<std::ostream*> streams;
    std::mutex stream_mutex;
public:
    synced_stream() {};

    synced_stream(std::ostream* stream) : streams(1, stream) {};

    void add_stream(std::ostream* stream) {
        streams.push_back(stream);
    }

    void remove_stream(std::ostream* stream) {
        size_t pos = 0;
        for (auto& streamIt: streams) {
            if (streamIt == stream) {
                streams.erase(streams.begin() + pos);
                break;
            }
            pos++;
        }
    }

    //takes an arbitrary number of arguments, which are inserted 
    // into the stream one by one, in the order they were given
    template<typename... Args>
    void print(Args... args) {
        std::lock_guard<std::mutex> lock(stream_mutex);
        for (auto& stream : streams) {
            stream << ... << args;
        }
    }
    //same as print() above, but also inserts newline between arguments
    template<typename... Args>
    void println(Args... args) {
        std::lock_guard<std::mutex> lock(stream_mutex);
        for (auto& stream: streams) {
            (void)std::initializer_list<int>{
                ((stream << args << '\n'), 0)...
            };
        }
    }
};

class this_thread {
private:
    thread_local static std::optional<size_t> thread_index_;
    thread_local static std::optional<void*> poolPointer_;
public:
    friend class ThreadPool;
    std::optional<std::size_t> get_index() {
        if (thread_index_)
            return *thread_index_;
        return std::nullopt;
    }
    std::optional<void*> get_pool() {
        if (poolPointer_)
            return *poolPointer_;
        return std::nullopt;
    }
};

