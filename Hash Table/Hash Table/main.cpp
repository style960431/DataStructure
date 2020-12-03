#include <iostream>
using namespace std;

class Node {
private:
    int key;
    string data;
    Node* next;
public:
    Node() :key(0), data(""), next(nullptr) {};
    Node(int key, string str) :key(key), data(str), next(nullptr) {};
    Node(const Node &data) :key(data.key), data(data.data), next(data.next) {};
    friend class HashChaining;
};

class HashChaining {
private:
    int size;
    int count;
    Node** table;

    int HashFunction(int key);
    void TableDoubling();
    void TableShrinking();
    void Rehashing(int size_orig);
public:
    HashChaining():size(5),count(0), table(new Node* [size] {nullptr}) {};
    HashChaining(int m) : size(m), count(0), table(new Node* [size] {nullptr}) {};

    void Insert(Node data);
    void Delete(int key);
    string Search(int key);
    void DisplayTable();
};

int HashChaining::HashFunction(int key) {
    //取 (( ket * A - ((key * A)的整數) ) * size) 的整數
    double A = (sqrt(5) - 1) / 2; // 選擇黃金比例
    double frac = key * A - floor(key * A);
    return floor(size * frac);
}

void HashChaining::TableDoubling() {
    int size_orig = size;
    size *= 2;
    Rehashing(size_orig);
}

void HashChaining::TableShrinking() {
    int size_orig = size;
    size /= 2;
    Rehashing(size_orig);
}

void HashChaining::Rehashing(int size_orig) {
    Node** newTable = new Node * [size] {nullptr};

    for (int i = 0; i < size_orig; i++) {
        Node* curr = table[i];
        Node* prev = nullptr;

        while (curr != NULL) {
            prev = curr->next;
            int index = HashFunction(curr->key);
            if (newTable[index] == NULL) {
                newTable[index] = curr;
                curr->next = nullptr;
            }
            else {
                Node* next = newTable[index]->next;
                newTable[index]->next = curr;
                curr->next = next;
            }
            curr = prev;
        }
    }

    delete[] table;
    table = newTable;
}

void HashChaining::Insert(Node data) {
    count++;
    if (count > size) {
        TableDoubling();
    }
    int index = HashFunction(data.key);
    Node* newNode = new Node(data);
    if (table[index] == NULL) {
        table[index] = newNode;
    }
    else {
        Node* next = table[index]->next;
        table[index]->next = newNode;
        newNode->next = next;
    }
}

void HashChaining::Delete(int key) {
    int index = HashFunction(key);
    Node* curr = table[index];
    Node* prev = nullptr;

    while (curr != NULL && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }
    // 無此資料
    if (curr == NULL) {
        cout << "Data is not found." << endl;
        return;
    }
    else {
        // 刪除的資料為 table[index] 之首
        if (prev == NULL) {
            table[index] = curr->next;
        }
        // 刪除的資料為 table[index] 之其餘位置
        else {
            prev->next = curr->next;
        }
        delete curr;
        curr = 0;
    }
    
    count--;
    // 節省空間
    if (count < size / 4)
        TableShrinking();
}

string HashChaining::Search(int key) {
    int index = HashFunction(key);
    Node* curr = table[index];
    while (curr != NULL) {
        if (curr->key == key) {
            return curr->data;
        }
        curr = curr->next;
    }
    return "The Data is not found.";
}

void HashChaining::DisplayTable() {
    for (int i = 0; i < size; i++) {
        cout << "#slot#" << i << ": ";
        Node* curr = table[i];
        while (curr != NULL) {
            cout << "(" << curr->key << "," << curr->data << ") ";
            curr = curr->next;
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    HashChaining hash(2);
    hash.Insert(Node(12, "post rock"));

    hash.Insert(Node(592, "shoegaze"));
    cout << "After inserting key(12),key(592):\n";
    hash.DisplayTable();
    hash.Insert(Node(6594, "blues"));
    cout << "After inserting key(6594), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(7, "folk"));
    cout << "After inserting key(7):\n";
    hash.DisplayTable();
    
    hash.Insert(Node(123596, "hiphop"));
    cout << "After inserting key(123596), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(93, "soul"));
    hash.Insert(Node(2288, "indie"));
    hash.Insert(Node(793, "jazz"));
    cout << "After inserting key(93),key(2288),key(793):\n";
    hash.DisplayTable();
    hash.Insert(Node(8491, "electro"));
    cout << "After inserting key(8491), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(323359, "pop"));
    cout << "After inserting key(323359):\n";
    hash.DisplayTable();

    cout << "Searching: genre(8491) is " << hash.Search(8491) << ".\n\n";
    cout << "Searching: genre(7) is " << hash.Search(7) << ".\n\n";

    hash.Delete(7);
    cout << "After deleting key(7):\n";
    cout << "Searching: genre(7) is " << hash.Search(7) << ".\n\n";

    hash.Delete(592);
    cout << "After deleting key(592):\n";
    hash.DisplayTable();

    cout << "Want to  delete key(592) again:\n";
    hash.Delete(592);

    hash.Delete(123596);
    hash.Delete(323359);
    hash.Delete(793);
    hash.Delete(93);
    cout << "After deleting key(123596),key(323359),key(793),key(93):\n";
    hash.DisplayTable();

    hash.Delete(6594);     
    cout << "After deleting key(6594), evoke TableShrinking():\n";
    hash.DisplayTable();
    
    return 0;
}
