#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Node {
private:
    Node* parent;
    Node* leftchild;
    Node* rightchild;
    int key;
    string data;
public:
    Node() :parent(0), leftchild(0), rightchild(0), key(0), data("") {};
    Node(int k,string s) :parent(0), leftchild(0), rightchild(0), key(k), data(s) {};
    
    int GetKey() { return key; }
    string GetData() { return data; }

    friend class BST;
};

class BST {
private:
    Node* root;
public:
    BST() :root(0) {};
    BST(Node* node) :root(node) {};

    Node* leftmost(Node* curr);
    Node* rightmost(Node* curr);
    Node* Inoder_next(Node* curr);
    Node* Inoder_prev(Node* curr);
    Node* Search(int key);
    void Insert(int key, string str);
    void Delete(int key);
    void Inoder_traversal();
    void Inoder_reverse();
    void Levelorder_traversal();
};

Node* BST::leftmost(Node* curr) {
    while (curr->leftchild != NULL) {
        curr = curr->leftchild;
    }
    return curr;
}

Node* BST::rightmost(Node* curr) {
    while (curr->rightchild != NULL) {
        curr = curr->rightchild;
    }
    return curr;
}

Node* BST::Inoder_next(Node* curr) {
    if (curr->rightchild != NULL) {
        return leftmost(curr->rightchild);
    }
    Node* next = curr->parent;
    while (next != NULL && curr == next->rightchild) {
        curr = next;
        next = curr->parent;
    }
    return next;
}

Node* BST::Inoder_prev(Node* curr) {
    if (curr->leftchild != NULL) {
        return rightmost(curr->leftchild);
    }
    Node* next = curr->parent;
    while (next != NULL && curr == next->leftchild) {
        curr = next;
        next = curr->parent;
    }
    return next;
}

Node* BST::Search(int key) {
    Node* curr = root;
    while (curr != NULL && key != curr->key) {
        if (key < curr->key) {
            curr = curr->leftchild;
        }
        else {
            curr = curr->rightchild;
        }
    }
    return curr;
}

void BST::Insert(int key, string str) {
    Node* x = root;
    Node* y = 0;
    Node* newNode = new Node(key, str);
    
    while (x != NULL) {
        y = x;
        if (newNode->key < x->key) {
            x = x->leftchild;
        }
        else {
            x = x->rightchild;
        }
    }
    newNode->parent = y;
    if (y == NULL) {
        root = newNode;
    }
    else if (newNode->key < y->key) {
        y->leftchild = newNode;
    }
    else {
        y->rightchild = newNode;
    }
}

void BST::Delete(int key) {
    Node* delete_node = Search(key);
    if (delete_node == NULL) {
        cout << "data not found." << endl;
        return;
    }
    Node *y = 0;      // 真正要被刪除並釋放記憶體的node
    Node *x = 0;      // 要被刪除的node的"child"

    if (delete_node->leftchild == NULL || delete_node->rightchild == NULL){
        y = delete_node;
    }
    else{
        y = Inoder_next(delete_node);
    }
    
    if (y->leftchild != NULL){
        x = y->leftchild;
    }
    else{
        x = y->rightchild;
    }
    
    if (x != NULL){
        x->parent = y->parent;
    }
                                          
    if (y->parent == NULL){
        this->root = x;
    }
    else if (y == y->parent->leftchild){
        y->parent->leftchild = x;
    }
    else{
        y->parent->rightchild = x;
    }
                                            
    if (y != delete_node) {
        delete_node->key = y->key;
        delete_node->data = y->data;
    }

    delete y;
    y = 0;
}

void BST::Inoder_traversal() {
    Node* curr = leftmost(root);
    while (curr != NULL) {
        cout << curr->data << "(" << curr->key << ")" << " ";
        curr = Inoder_next(curr);
    }
    cout << endl;
}

void BST::Inoder_reverse() {
    Node* curr = rightmost(root);
    while (curr != NULL) {
        cout << curr->data << "(" << curr->key << ")" << " ";
        curr = Inoder_prev(curr);
    }
    cout << endl;
}

void BST::Levelorder_traversal() {
    queue<Node*> temp;
    temp.push(root);
    while (!temp.empty()) {
        Node* curr = temp.front();
        temp.pop();
        cout << curr->data << "(" << curr->key << ")" << " ";
        if (curr->leftchild != NULL)
            temp.push(curr->leftchild);
        if (curr->rightchild != NULL)
            temp.push(curr->rightchild);
    }
    cout << endl;
}

int main() {
    BST T;
    T.Insert(8, "龜仙人");
    T.Insert(1000, "悟空");
    T.Insert(2, "克林");
    T.Insert(513, "比克");
    T.Insert(53, "副夫");
    T.Insert(643, "凹屋");
    T.Insert(888, "16號");
    T.Insert(891, "撒旦");

    T.Inoder_traversal();
    T.Levelorder_traversal();

    T.Delete(8);
    T.Inoder_traversal();
    T.Levelorder_traversal();

    return 0;
}
