//
//  main.cpp
//  Binary Tree
//
//  Created by 王宗祥 on 2020/11/27.
//

#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

class TreeNode {
private:
    TreeNode* parent;
    TreeNode* L_child;
    TreeNode* R_child;
    char data;
public:
    TreeNode() :parent(0), L_child(0), R_child(0), data('x') {};
    TreeNode(char c) :parent(0), L_child(0), R_child(0), data(c) {};

    friend class BinaryTree;
};

class BinaryTree {
private:
    TreeNode* root;
    const char* str;
public:
    BinaryTree() :root(0) {};
    BinaryTree(const char* str) {
        stringstream ss;
        ss << str;
        root = new TreeNode;
        ss >> root->data;
        LevelorderConstruct(ss);
    };

    void Preorder(TreeNode* curr);
    void Inorder(TreeNode* curr);
    void Postorder(TreeNode* curr);
    void Levelorder();
    void LevelorderConstruct(stringstream &ss);

    TreeNode* L_most(TreeNode* curr);
    TreeNode* R_most(TreeNode* curr);
    TreeNode* Inorder_next(TreeNode* curr);
    TreeNode* Inorder_prev(TreeNode* curr);

    void Inorder_traversal();
    void Inorder_reverse();
};

void BinaryTree::Preorder(TreeNode* curr) {
    if (curr != NULL) {
        cout << curr->data << " ";
        Preorder(curr->L_child);
        Preorder(curr->R_child);
    }
}

void BinaryTree::Inorder(TreeNode* curr) {
    if (curr != NULL) {
        Inorder(curr->L_child);
        cout << curr->data << " ";
        Inorder(curr->R_child);            
    }
}

void BinaryTree::Postorder(TreeNode* curr) {
    if (curr != NULL) {
        Postorder(curr->L_child);
        Postorder(curr->R_child);
        cout << curr->data << " ";
    }
}

void BinaryTree::Levelorder() {
    queue<TreeNode*> temp;
    temp.push(this->root);
    while (!temp.empty()) {
        TreeNode* curr = temp.front();
        temp.pop();
        cout << curr->data << " ";

        if (curr->L_child != NULL)
            temp.push(curr->L_child);
        if (curr->R_child != NULL)
            temp.push(curr->R_child);
    }
}

void BinaryTree::LevelorderConstruct(stringstream &ss) {
    queue<TreeNode*> temp;
    TreeNode* curr = root;
    char data = 'x';
    while (ss >> data) {
        if (data >= 65 && data <= 90) {
            TreeNode* newNode = new TreeNode(data);
            newNode->parent = curr;
            curr->L_child = newNode;
            temp.push(newNode);
        }
        if (!(ss >> data)) {
            break;
        }
        if (data >= 65 && data <= 90) {
            TreeNode* newNode = new TreeNode(data);
            newNode->parent = curr;
            curr->R_child = newNode;
            temp.push(newNode);
        }
        curr = temp.front();
        temp.pop();
    }
}


TreeNode* BinaryTree::L_most(TreeNode* curr) {
    while (curr->L_child != NULL) {
        curr = curr->L_child;
    }
    return curr;
}

TreeNode* BinaryTree::R_most(TreeNode* curr) {
    while (curr->R_child != NULL) {
        curr = curr->R_child;
    }
    return curr;
}

TreeNode* BinaryTree::Inorder_next(TreeNode* curr) {
    if (curr->R_child != NULL) {
        return L_most(curr->R_child);
    }
    TreeNode* next = curr->parent;
    while (next != NULL && curr == next->R_child) {
        curr = next;
        next = curr->parent;
    }
    return next;
}

TreeNode* BinaryTree::Inorder_prev(TreeNode* curr) {
    if (curr->L_child != NULL) {
        return R_most(curr->L_child);
    }
    TreeNode* prev = curr->parent;
    while (prev != NULL && curr == prev->L_child) {
        curr = prev;
        prev = curr->parent;
    }
    return prev;
}

void BinaryTree::Inorder_traversal() {
    TreeNode* curr = L_most(root);
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = Inorder_next(curr);
    }
}

void BinaryTree::Inorder_reverse() {
    TreeNode* curr = R_most(root);
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = Inorder_prev(curr);
    }
}

int main() {
    const char* str = "A B C D E F x x x G H x I";
    BinaryTree T(str);
    T.Inorder_traversal();
    return 0;
}
