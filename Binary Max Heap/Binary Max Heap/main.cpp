//
//  main.cpp
//  Binary Max Heap
//
//  Created by 王宗祥 on 2020/11/27.
//

#include <iostream>
#include <vector>
using namespace std;

class HeapNode {
private:
    int key;
    string data;
public:
    HeapNode() :key(0), data(0) {};
    HeapNode(int key, string data) :key(key), data(data) {};

    friend class MaxHeap;
};

class MaxHeap {
private:
    vector<HeapNode> heap;
public:
    MaxHeap() {};
    bool empty();
    void swap(HeapNode* a, HeapNode* b);
    int parent(int i) { return (i - 1) / 2; };
    int left(int i) { return 2 * i + 1; };
    int right(int i) { return 2 * i + 2; };
    string Maximum() { return heap[0].data; };
    void ExtractMax();
    void HeapifyUp(int i);
    void HeapifyDown(int i, int length);
    void insert(HeapNode node);
    void showHeap();
};

bool MaxHeap::empty() {
    return heap.size() < 1;
}

void MaxHeap::ExtractMax() {
    if (empty()) {
        cout << "The Heap is empty." << endl;
        return -1;
    }
    string max = Maximum();
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    HeapifyDown(0, heap.size());
}

void MaxHeap::swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void MaxHeap::HeapifyUp(int i) {
    int par = parent(i);
    if (i >= 0 && par >= 0 && heap[i].key > heap[par].key) {
        swap(&heap[i], &heap[par]);
        HeapifyUp(par);
    }
}

void MaxHeap::HeapifyDown(int i, int length) {
    int L = left(i);
    int R = right(i);
    int largest = i;
    if (L <= length && heap[L].key > heap[i].key) {
        largest = L;
    }
    if (R <= length && heap[R].key > heap[largest].key) {
        largest = R;
    }
    if (largest != i) {
        swap(&heap[largest], &heap[i]);
        HeapifyDown(largest, length);
    }
}

void MaxHeap::insert(HeapNode node) {
    heap.push_back(node);
    HeapifyUp(heap.size() - 1);
}

void MaxHeap::showHeap() {
    //vector<HeapNode>::iterator it = heap.begin();
    int it = 0;
    cout << "Heap --> " << endl;
    while (it != heap.size()) {
        cout << heap[it].key << " " << heap[it].data << " " << endl;
        it++;
    }
}

int main() {
    MaxHeap B;
    HeapNode n1(5, "a");
    HeapNode n2(1, "b");
    HeapNode n3(3, "c");
    HeapNode n4(10, "f");
    HeapNode n5(12, "d");
    HeapNode n6(33, "g");
    HeapNode n7(8, "h");
    HeapNode n8(9, "i");
    B.insert(n1);    B.insert(n2);    B.insert(n3);    B.insert(n4);
    B.insert(n5);    B.insert(n6);    B.insert(n7);    B.insert(n8);
    B.showHeap();
    B.ExtractMax();
    B.showHeap();
    return 0;
}
