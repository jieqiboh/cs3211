#include <iostream>
#include "threadsafe_stack.h"
#include "threadsafe_queue.h"

int main() {
    // Threadsafe Stack
    threadsafe_stack<int> threadsafe_st;
    threadsafe_st.push(1);
    threadsafe_st.push(2);
    threadsafe_st.push(3);

    std::cout << *threadsafe_st.pop() << "\n"; // 3
    std::cout << *threadsafe_st.pop() << "\n"; // 2
    std::cout << *threadsafe_st.pop() << "\n"; // 1

    threadsafe_queue_test();
}