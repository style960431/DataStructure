//
//  main.cpp
//  Queue_Linked
//
//  Created by 王宗祥 on 2020/11/27.
//

#include <iostream>
using namespace std;

class QueueNode {
private:
    int elt;
    QueueNode* next;
public:
    QueueNode() : elt(0), next(nullptr) {};
    QueueNode(int x) : elt(x), next(nullptr) {};
    QueueNode(int x, QueueNode* next) : elt(x), next(next) {};

    friend class QueueList;
};

class QueueList {
private:
    QueueNode* front;
    QueueNode* back;
    int num;
public:
    QueueList() :front(nullptr), back(nullptr), num(0) {};

    void push(int data);
    void pop();
    bool empty();
    int getFront();
    int getBack();
    int size();
};

void QueueList::push(int data) {
    if (empty()) {
        front = new QueueNode(data);
        back = front;
        num++;
        return;
    }
    QueueNode* newNode = new QueueNode(data);
    back->next = newNode;
    back = newNode;
    num++;
    return;
}

void QueueList::pop() {
    if (empty()) {
        cout << "Queue is empty." << endl;
        return;
    }
    QueueNode* temp = front;
    front = front->next;
    delete temp;
    temp = 0;
    num--;
    return;
}

bool QueueList::empty() {
    return front == nullptr;
}

int QueueList::getFront() {
    if (empty()) {
        std::cout << "Queue is empty.\n";
        return -1;
    }
    return front->elt;
}

int QueueList::getBack() {
    if (empty()) {
        std::cout << "Queue is empty.\n";
        return -1;
    }
    return back->elt;
}

int QueueList::size() {
    return num;
}
