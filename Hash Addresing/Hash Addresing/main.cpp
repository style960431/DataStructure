//
//  main.cpp
//  Hash Addresing
//
//  Created by 王宗祥 on 2020/11/27.
//

#include <iostream>
using namespace std;

class Node {
private:
    int key;
    string data;
public:
    Node() :key(0), data("") {};
    Node(int key, string str) :key(0), data(str) {};

    friend class HashAddresing;
};

class HashAddresing {
private:
    int size;
    int count;
    Node* table;

    int QuadraticProbing(int key, int i);
    void TableDoubling();
    void TableShrinking();
    void Rehashing(int size_orig);
public:
    HashAddresing():size(0),count(0),table(0) {};
    HashAddresing(int s) :size(s), count(0), table(new Node[size]) {};

    void Insert(int key,string data);
    void Delete(int key);
    string Search(int key);
    void HashPrint();
};

int HashAddresing::QuadraticProbing(int key, int i) {
    // c1,c2 = 0.5
    return ((int)((key % size) + 0.5 * i + 0.5 * i * i) % size);
}

void HashAddresing::TableDoubling() {
    int size_orig = size;
    size *= 2;
    Rehashing(size_orig);
}

void HashAddresing::TableShrinking() {
    int size_orig = size;
    size /= 2;
    Rehashing(size_orig);
}

void HashAddresing::Rehashing(int size_orig) {
    // ∑s´ÿ§@≠” table ®√™Ï©l§∆
    Node* newTable = new Node[size]{ Node(0,"") };

    for (int j = 0; j < size_orig; j++) {
        int i = 0;
        Node curr = table[j];
        while (i != size) {
            int index = QuadraticProbing(curr.key, i);
            if (newTable[index].data == "") {
                newTable[index].key = curr.key;
                newTable[index].data = curr.data;
                break;
            }
            else {
                i++;
            }
        }
    }
    delete[] table;
    table = newTable;
}

void HashAddresing::Insert(int key, string data) {
    int i = 0;
    while (i != size) {
        int index = QuadraticProbing(key, i);
        if (table[index].data == "") {
            table[index].key = key;
            table[index].data = data;
            count++;
            if (count > size / 2) {
                TableDoubling();
            }
            return;
        }
        else {
            i++;
        }
    }
}

void HashAddresing::Delete(int key) {
    int i = 0;
    while (i != size) {
        int index = QuadraticProbing(key, i);
        if (table[index].key == key) {
            table[index].key = 0;
            table[index].data = "";
            count--;
            if (count < size / 4) {
                TableDoubling();
            }
            return;
        }
        else {
            i++;
        }
    }
    cout << "No data is found." << endl;
}

string HashAddresing::Search(int key) {
    int i = 0;
    while (i != size) {
        int index = QuadraticProbing(key, i);
        if (table[index].key == key) {
            return table[index].data;
        }
        else {
            i++;
        }
    }
    return "...data not found\n";
}

void HashAddresing::HashPrint() {
    for (int i = 0; i < size; i++) {
        cout << "#slot#" << i << ": (" << table[i].key
            << "," << table[i].data << ")" << endl;
    }
    cout << endl;
}

int main() {

    HashAddresing hash(8);          // probing sequence:
    hash.Insert(33, "blue");          // 1,2,4,7,3,0,6,5 -> 1
    hash.Insert(10, "yellow");        // 2,3,5,0,4,1,7,6 -> 2
    hash.Insert(77, "red");           // 5,6,0,3,7,4,2,1 -> 5
    hash.Insert(2, "white");          // 2,3,5,0,4,1,7,6 -> 3
    hash.HashPrint();

    hash.Insert(8, "black");          // 0,1,3,6,2,7,5,4 -> 0
    hash.Insert(47, "gray");          // 7,0,2,5,1,6,4,3 -> 7
    hash.Insert(90, "purple");        // 2,3,5,0,4,1,7,6 -> 4
    hash.Insert(1, "deep purple");    // 4,5,7,2,6,3,1,0 -> 6
    hash.HashPrint();
    
    hash.Insert(15, "green");         // hash table overflow

    cout << "number#90 is " << hash.Search(90) << "\n\n";

    hash.Delete(90);
    cout << "after deleting (90,purple):\n";
    cout << "number#90 is " << hash.Search(90) << "\n";

    hash.Insert(12, "orange");        // 4,5,7,2,6,3,1,0 -> 4
    hash.HashPrint();
    
    return 0;
}
