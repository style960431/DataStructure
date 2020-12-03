//
//  main.cpp
//  Stack_Array
//
//  Created by 王宗祥 on 2020/11/27.
//

#include <iostream>
using namespace std;

class StackArray {
private:
    int Top;
    int capacity;
    int* stack;

public:
    StackArray() :Top(-1), capacity(1), stack(new int[capacity]) {};

    void DoubleCapacity();
    void push(int x);
    void pop();
    bool empty();
    int top();
    int size();
};

void StackArray::DoubleCapacity() {
    capacity *= 2;
    int* newstack = new int[capacity];
    for (int i = 0; i < capacity / 2; i++) {
        newstack[i] = stack[i];
    }
    delete[] stack;
    stack = newstack;
    return;
}

void StackArray::push(int x) {
    if (Top == capacity - 2) {
        DoubleCapacity();
    }
    stack[++Top] = x;
    return;
}

void StackArray::pop() {
    if (empty()) {
        cout << "Stack is empty.\n";
        return;
    }
    Top--;
}

bool StackArray::empty() {
    return Top == -1;
}

int StackArray::top() {
    if (empty()) {
        cout << "Stack is empty." << endl;
        return -1;
    }
    return stack[Top];
}

int StackArray::size() {
    return Top + 1;
}
