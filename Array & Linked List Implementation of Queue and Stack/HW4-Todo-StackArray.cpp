#include "HW4-Todo-StackArray.hpp"
#include <iostream>

TodoStackArray::TodoStackArray() {
    stackTop = -1;
    
    for(int i = 0; i < MAX_STACK_SIZE; i++) {
        TodoItem* tt = new TodoItem;
        stack[i] = tt;
    }
}

bool TodoStackArray::isEmpty() {
    if(stackTop == -1) {
        return true;
    }
    else {
        return false;
    }
}

bool TodoStackArray::isFull() {
    if(stackTop == (MAX_STACK_SIZE - 1)) {
        return true;
    }
    else {
        return false;
    }
}

void TodoStackArray::push(std::string todoItem) {
    if(isFull()) {
        std::cout << "Stack full, cannot add new todo item." << std::endl;
    }
    else {
        stackTop++;
        stack[stackTop]->todo = todoItem;
    }
}

void TodoStackArray::pop() {
    if(isEmpty()) {
        std::cout << "Stack empty, cannot pop an item." << std::endl;
    }
    else {
        stack[stackTop]->todo = "";
        stackTop--;
    }
}

TodoItem* TodoStackArray::peek() {
    if(isEmpty()) {
        std::cout << "Stack empty, cannot peek." << std::endl;
    }
    return stack[stackTop];
}