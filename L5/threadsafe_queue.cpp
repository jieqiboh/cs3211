#include <exception>
#include <queue>
#include <mutex>
#include <memory>
#include <iostream>
#include <assert.h>
#include "threadsafe_queue.h"

// Constructor
template<typename T>
threadsafe_queue<T>::threadsafe_queue() {}

// Push method
template<typename T>
void threadsafe_queue<T>::push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data_queue.push(std::move(new_value));
    data_cond.notify_one();
}

template<typename T>
void threadsafe_queue<T>::wait_and_pop(T& value) {
    std::unique_lock<std::mutex> lock(m);
    data_cond.wait(lock, [this]{
        return !data_queue.empty();
    });
    value = std::move(data_queue.front());
    data_queue.pop();
}

template<typename T>
std::shared_ptr<T> threadsafe_queue<T>::wait_and_pop() {
    std::unique_lock<std::mutex> lock(m);
    data_cond.wait(lock, [this]{
        return !data_queue.empty();
    });
    std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
    data_queue.pop();
    return res;
}

template<typename T>
bool threadsafe_queue<T>::try_pop(T& value) {
    std::lock_guard<std::mutex> lock(m);
    if (data_queue.empty()) {
        return false;
    }
    value = std::move(data_queue.front());
    data_queue.pop();
    return true;
};

template<typename T>
std::shared_ptr<T> threadsafe_queue<T>::try_pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data_queue.empty()) {
        return std::shared_ptr<T>();
    }
    std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
    data_queue.pop();
    return res;
}

template<typename T>
bool threadsafe_queue<T>::empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data_queue.empty();
}

template class threadsafe_queue<int>;  // This instantiates the template for `int`

void test_basic_operations() {
    threadsafe_queue<int> q;

    // Test empty queue
    assert(q.empty() == true);

    // Push elements
    q.push(1);
    q.push(2);
    q.push(3);

    assert(q.empty() == false);

    // Pop elements using try_pop
    int value;
    assert(q.try_pop(value) == true && value == 1);
    assert(q.try_pop(value) == true && value == 2);
    assert(q.try_pop(value) == true && value == 3);
    assert(q.try_pop(value) == false); // Should be empty now

    std::cout << "test_basic_operations passed!" << std::endl;
}

void test_shared_ptr_pop() {
    threadsafe_queue<int> q;
    q.push(100);

    std::shared_ptr<int> ptr = q.wait_and_pop();
    assert(ptr && *ptr == 100);

    assert(q.empty() == true);

    std::cout << "test_shared_ptr_pop passed!" << std::endl;
}

void threadsafe_queue_test() {
    test_basic_operations();
    test_shared_ptr_pop();

    std::cout << "All threadsafe_queue tests passed successfully!" << std::endl;
}

