//
//  main.cpp
//  Queue Array
//
//  Created by 王宗祥 on 2020/11/27.
//

#include <iostream>
using namespace std;

class QueueArray {
private:
    int front, back, capacity;
    int* queue;
public:
    QueueArray() :front(0), back(0), capacity(5), queue(new int[capacity]) {};

    void DoubleCapacity();
    void push(int x);
    void pop();
    bool empty();
    bool full();
    int getFront();
    int getBack();
    int size();
    int getCapacity();
};

void QueueArray::DoubleCapacity() {
    int* newQueue = new int[capacity * 2];
    int j = front;
    for (int i = 1; i <= size(); i++) {
        j++;
        newQueue[i] = queue[(j % capacity)];
    }
    back = size();
    front = 0;
    capacity *= 2;
    delete[]queue;
    queue = newQueue;
    return;
}

void QueueArray::push(int x) {
    if (full()) {
        DoubleCapacity();
    }
    back = (back + 1) % capacity;
    queue[back] = x;
    return;
}

void QueueArray::pop() {
    if (empty()) {
        cout << "Queue is empty." << endl;
        return;
    }
    front = (front + 1) % capacity;
    cout << front << endl;
}

bool QueueArray::empty() {
    return front == back;
}

bool QueueArray::full() {
    return (back + 1) % capacity == front;
}

int QueueArray::getFront() {
    if (empty()) {
        std::cout << "Queue is empty." << endl;
        return -1;
    }
    return queue[(front + 1) % capacity];
}

int QueueArray::getBack() {
    if (empty()) {
        std::cout << "Queue is empty." << endl;
        return -1;
    }
    return queue[back];
}

int QueueArray::size() {
    if (front < back) {
        return back - front;
    }
    else {
        return capacity - (front - back) ;
    }
}

int QueueArray::getCapacity() {
    return capacity;
}

