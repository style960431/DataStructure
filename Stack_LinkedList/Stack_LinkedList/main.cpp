//
//  main.cpp
//  Stack_LinkedList
//
//  Created by 王宗祥 on 2020/11/27.
//

#include <iostream>
using namespace std;

class StackNode {
private:
    int data;
    StackNode* next;
public:
    StackNode() :data(0), next(nullptr) {};
    StackNode(int data) :data(data), next(nullptr) {};
    StackNode(int data, StackNode* next) :data(data), next(next) {};

    friend class StackList;
};

class StackList {
private:
    StackNode* Top;
    int num;
public:
    StackList() :Top(nullptr), num(0) {};

    void push(int elt);
    void pop();
    bool empty();
    int top();
    int size();
};

void StackList::push(int elt) {
    StackNode* newNode = new StackNode(elt, Top);
    Top = newNode;
    num++;
    return;
};

void StackList::pop() {
    if (empty()) {
        cout << "Stack is empty.\n";
        return;
    }
    StackNode* temp = Top;
    Top = Top->next;
    delete temp;
    temp = 0;
    num--;
    return;
};

bool StackList::empty() {
    return num == 0;
};

int StackList::top() {
    if (empty()) {
        cout << "Stack is empty.\n";
        return -1;
    }
    return Top->data;
};

int StackList::size() {
    return num;
};
