//
// Created by Jie Qi Boh on 18/2/25.
//

#ifndef L5_THREADSAFE_QUEUE_H
#define L5_THREADSAFE_QUEUE_H
#include <memory>
#include <mutex>
#include <queue>

// Template class definition for threadsafe_queue
template<typename T>
class threadsafe_queue {
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;
public:
    threadsafe_queue(); // Constructor
    
    void push(T new_value);

    void wait_and_pop(T& value);

    std::shared_ptr<T> wait_and_pop();

    bool try_pop(T& value);

    std::shared_ptr<T> try_pop();

    bool empty() const; // Empty check method
};

#endif //L5_THREADSAFE_QUEUE_H
