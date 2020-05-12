#ifndef BOOST_ASIO_TEST_THREADSAFEQUEUE_H
#define BOOST_ASIO_TEST_THREADSAFEQUEUE_H

#include <queue>
#include <vector>
#include <mutex>

template <typename T>
class ThreadSafeQueue {
private:
    std::mutex _mutex;
    std::queue<T> buffer;
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(_mutex);
        buffer.push(value);
    }
    std::vector<T> popAll() {
        std::lock_guard<std::mutex> lock(_mutex);
        std::vector<T> temp;
        while (!buffer.empty()) {
            temp.push_back(buffer.front());
            buffer.pop();
        }
        return temp;
    }
};



#endif //BOOST_ASIO_TEST_THREADSAFEQUEUE_H
