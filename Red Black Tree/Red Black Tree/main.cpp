#include <iostream>
using namespace std;

class Node {
private:
    Node* parent;
    Node* leftchild;
    Node* rightchild;
    string data;
    int key;
    int color;        // 0：Red , 1：Black
public:
    Node() :parent(0), leftchild(0), rightchild(0), data(""), key(0), color(0) {};
    Node(int key,string str) :parent(0), leftchild(0), rightchild(0), data(str), key(key), color(0) {};
    friend class RBT;
};

class RBT {
private:
    Node* root;
    Node* neel;
    Node* leftmost(Node* curr);
    Node* next(Node* curr);
    void LeftRotation(Node* curr);
    void RightRotation(Node* curr);
    void insert_fix(Node* curr);
    void delete_fix(Node* curr);
public:
    RBT() : neel(new Node),root(neel) {
        neel->color = 1; // 一定為黑色
        root->parent = neel;
    };
    void insertRBT(int key, string str);
    void deleteRBT(int key);
    Node* searchRBT(int key);
};

Node* RBT::leftmost(Node* curr) {
    while (curr->leftchild != NULL) {
        curr = curr->leftchild;
    }
    return curr;
}

Node* RBT::next(Node* curr) {
    if (curr->rightchild != NULL) {
        return leftmost(curr);
    }
    
    Node* newNode = curr->parent;
    while (newNode != NULL && curr == newNode->rightchild) {
        curr = newNode;
        newNode = curr->parent;
    }
    return newNode;
}

void RBT::LeftRotation(Node* curr) {
    Node* temp = curr->rightchild;
    curr->rightchild = temp->leftchild;
    if (temp->leftchild != neel) {
        temp->leftchild->parent = curr;
    }
    temp->parent = curr->parent;

    if (curr->parent == neel) {
        root = temp;
    }
    else if (curr == curr->parent->leftchild) {
        curr->parent->leftchild = temp;
    }
    else {
        curr->parent->rightchild = temp;
    }
    temp->leftchild = curr;
    curr->parent = temp;
}

void RBT::RightRotation(Node* curr) {
    Node* temp = curr->leftchild;
    curr->leftchild = temp->rightchild;
    if (temp->rightchild != neel) {
        temp->rightchild->parent = curr;
    }
    temp->parent = curr->parent;

    if (curr->parent == neel) {
        root = temp;
    }
    else if (curr == curr->parent->rightchild) {
        curr->parent->rightchild = temp;
    }
    else {
        curr->parent->leftchild = temp;
    }
    temp->rightchild = curr;
    curr->parent = temp;
}

void RBT::insertRBT(int key, string str) {
    Node* newNode = new Node(key, str);
    Node* y = neel;
    Node* x = root;

    while (x != neel) {
        y = x;
        if (newNode->key < x->key) {
            x = x->leftchild;
        }
        else {
            x = x->rightchild;
        }
    }
    newNode->parent = y;
    if (y == neel) {
        root = newNode;
    }
    else if (newNode->key < y->key) {
        y->leftchild = newNode;
    }
    else {
        y->rightchild = newNode;
    }
    newNode->leftchild = neel;
    newNode->rightchild = neel;
    newNode->color = 0;         // 新生先為紅
    insert_fix(newNode);        // 檢查：紅父不能容
}

void RBT::insert_fix(Node* curr) {
    // 紅父不能容
    while (curr->parent->color == 0) {
        // parent 為 grandparent 的leftchild
        if (curr->parent == curr->parent->parent->leftchild) {
            Node* uncle = curr->parent->parent->rightchild;
            // case 1 : 紅叔變色龍
            if (uncle->color == 0) {
                curr->parent->color = 1;
                uncle->color = 1;
                curr->parent->parent->color = 0;
                curr = curr->parent->parent;
            }
            // case 2 : 黑叔逼爺退
            else {
                if (curr == curr->parent->rightchild) {
                    curr = curr->parent;
                    LeftRotation(curr);
                }
                curr->parent->color = 1;
                curr->parent->parent->color = 0;
                RightRotation(curr->parent->parent);
            }
        }
        // parent 為 grandparent 的leftchild
        else {
            Node* uncle = curr->parent->parent->leftchild;
            // case 1 : 紅叔變色龍
            if (uncle->color == 0) {
                curr->parent->color = 1;
                uncle->color = 1;
                curr->parent->parent->color = 0;
                curr = curr->parent->parent;
            }
            // case 2 : 黑叔逼爺退
            else {
                if (curr == curr->parent->leftchild) {
                    curr = curr->parent;
                    RightRotation(curr);
                }
                curr->parent->color = 1;
                curr->parent->parent->color = 0;
                LeftRotation(curr->parent->parent);
            }
        }
    }
    root->color = 1;    // 確保 root 必為黑色
}

void RBT::deleteRBT(int key) {
    Node* deNode = searchRBT(key);
    if (deNode == NULL) {
        cout << "data not found." << endl;
        return;
    }
    Node* dn = 0;      // 真正要被刪除並釋放記憶體的 node
    Node* dc = 0;      // 要被刪除的 node 的 "child"

    // 先調整成最多只有一個 child 的情況
    if (deNode->leftchild == neel || deNode->rightchild == neel) {
        dn = deNode;
    }
    else {
        dn = next(deNode);
    }
    // 根據左右 child 並指定到 dc，沒有的話就不指定
    if (dn->leftchild != neel) {
        dc = dn->leftchild;
    }
    else {
        dc = dn->rightchild;
    }
    // 即使 dc 是 NIL 也要把 dc 的 parent 指向有效的記憶體位置
    // 因為在 deletefix 時需要藉由 dc->parent 判斷 dc 為 leftchild 或 rightchild
    dc->parent = dn->parent;

    if (dn->parent == neel) {
        root = dc;
    }
    else if (dn == dn->parent->leftchild) {
        dn->parent->leftchild = dc;
    }
    else {
        dn->parent->rightchild = dc;
    }

    if (dn != deNode) {
        deNode->key = dn->key;
        deNode->data = dn->data;
    }

    if (dn->color == 1) {
        delete_fix(dc);
    }
    delete dn;
    dn = 0;
}

void RBT::delete_fix(Node* curr) {
    while (curr != root && curr->color == 1) {
        // 先看 curr 為 leftchild 時的情形
        if (curr == curr->parent->leftchild) {
            Node* sibling = curr->parent->rightchild;
            if (sibling->color == 0) {
                sibling->color = 1;
                curr->parent->color = 0;
                LeftRotation(curr->parent);
                sibling = curr->parent->rightchild;
            }
            if (sibling->leftchild->color == 1 && sibling->rightchild->color == 1) {
                sibling->color = 0;
                curr = curr->parent;
            }
            else {
                if (sibling->rightchild->color == 1) {
                    sibling->leftchild->color = 1;
                    sibling->color = 0;
                    RightRotation(sibling);
                    sibling = curr->parent->rightchild;
                }
                sibling->color = curr->parent->color;
                curr->parent->color = 1;
                sibling->rightchild->color = 1;
                LeftRotation(curr->parent);
                curr = root;
            }
        }
        // 再看 curr 為 rightchild 時的情形
        else {
            Node* sibling = curr->parent->leftchild;
            if (sibling->color == 0) {
                sibling->color = 1;
                curr->parent->color = 0;
                RightRotation(curr->parent);
                sibling = curr->parent->leftchild;
            }
            if (sibling->leftchild->color == 1 && sibling->rightchild->color == 1) {
                sibling->color = 0;
                curr = curr->parent;
            }
            else {
                if (sibling->leftchild->color == 1) {
                    sibling->rightchild->color = 1;
                    sibling->color = 0;
                    RightRotation(sibling);
                    sibling = curr->parent->leftchild;
                }
                sibling->color = curr->parent->color;
                curr->parent->color = 1;
                sibling->leftchild->color = 1;
                RightRotation(curr->parent);
                curr = root;
            }
        }
    }
    curr->color = 1;
}

Node* RBT::searchRBT(int key) {
    Node* curr = root;
    while (curr != NULL && key == curr->key) {
        if (key < curr->key) {
            curr = curr->leftchild;
        }
        else {
            curr = curr->rightchild;
        }
    }
    return curr;
}


