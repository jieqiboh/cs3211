#include <exception>
#include <stack>
#include <mutex>
#include <memory>
#include "threadsafe_stack.h"

// Constructor
template<typename T>
threadsafe_stack<T>::threadsafe_stack() {}

// Copy constructor
template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack<T>& other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
}

// Push method
template<typename T>
void threadsafe_stack<T>::push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
}

// Pop method returning shared pointer
template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();
    std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));
    data.pop();
    return res;
}

// Pop method storing in reference
template<typename T>
void threadsafe_stack<T>::pop(T& value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();
    value = std::move(data.top());
    data.pop();
}

// Empty check method
template<typename T>
bool threadsafe_stack<T>::empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
}

// Explicit template instantiation
template class threadsafe_stack<int>;  // This instantiates the template for `int`
