//
//  main.cpp
//  Linked List
//
//  Created by 王宗祥 on 2020/11/27.
//

#include <iostream>
using namespace std;

class ListNode {
    int val;
    ListNode* next;
public:
    ListNode() :val(0), next(nullptr) {};
    ListNode(int val) :val(val), next(nullptr) {};
    ListNode(int val, ListNode* next) :val(val), next(next) {};

    friend class LinkedList;
};

class LinkedList {
    ListNode* head;
public:
    LinkedList() :head(0) {};
    void PrintList();
    void Push_front(int val);
    void Push_back(int val);
    void Delete(int val);
    void Clear();
    void Reverse();
};

void LinkedList::PrintList() {
    if (head == NULL) {
        cout << "The List is empty." << endl;
        return ;
    }
    ListNode* curr = head;
    while (curr != NULL) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
}

void LinkedList::Push_front(int val) {
    ListNode* newNode = new ListNode(val);
    newNode->next = head;
    head = newNode;
}

void LinkedList::Push_back(int val) {
    ListNode* newNode = new ListNode(val);
    if (head == NULL) {
        head = newNode;
        return;
    }
    ListNode* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
}

void LinkedList::Delete(int val) {
    ListNode* curr = head;
    ListNode* prev = nullptr;
    while (curr != NULL && curr->val != val) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        cout << "Not Found." << endl;
        return;
    }
    else if (curr == head) {
        head = curr->next;
        delete curr;
        curr = nullptr;
    }
    else {
        prev->next = curr->next;
        delete curr;
        curr = nullptr;
    }
}

void LinkedList::Clear() {
    while (head != NULL) {
        ListNode* curr = head;
        head = head->next;
        delete curr;
        curr = nullptr;
    }
}

void LinkedList::Reverse() {
    if (head == NULL || head->next == NULL) {
        return;
    };

    ListNode* prev = nullptr,
            * curr = head,
            * temp = head->next;
    while (temp != NULL) {
        curr->next = prev;
        prev = curr;
        curr = temp;
        temp = temp->next;
    }
    curr->next = prev;
    head = curr;
}

int main() {
    LinkedList list;
    list.PrintList();
    list.Push_back(5);
    list.Push_back(7);
    list.Push_back(9);
    list.Push_front(6);
    list.PrintList();
    list.Reverse();
    list.PrintList();
    list.Delete(7);
    list.PrintList();
    list.Clear();
    list.PrintList();
    return 0;
}
