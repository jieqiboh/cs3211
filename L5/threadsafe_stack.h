//
// Created by Jie Qi Boh on 18/2/25.
//

#ifndef L5_THREADSAFE_STACK_H
#define L5_THREADSAFE_STACK_H
#include <stack>

// Custom exception for empty stack
struct empty_stack: std::exception {
    const char* what() const throw() override {
        return "Stack is empty!";
    }
};

// Template class definition for threadsafe_stack
template<typename T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex m;
public:
    threadsafe_stack(); // Constructor

    threadsafe_stack(const threadsafe_stack<T>& other); // Copy constructor

    threadsafe_stack& operator=(const threadsafe_stack<T>&) = delete; // Assignment operator

    void push(T new_value); // Push method

    std::shared_ptr<T> pop(); // Pop method returning shared pointer

    void pop(T& value); // Pop method storing in reference

    bool empty() const; // Empty check method
};

#endif //L5_THREADSAFE_STACK_H
