#include "HW4-Todo-StackArray.hpp"

int main {
    TodoStackArray ss;
    ss.push(4);
    ss.push(5);
    ss.pop();
    std::cout << ss.peek()->todoItem << std::endl;
    return 0;
}