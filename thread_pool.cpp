module thread_pool;

ThreadPool::ThreadPool(int start) : count_(start) {}

void ThreadPool::increment() {
    ++count_;
}

int ThreadPool::value() const {
    return count_;
}
