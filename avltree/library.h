#ifndef TRON_ALGDAT_LIBRARY_H
#define TRON_ALGDAT_LIBRARY_H

#include <iostream>

using namespace std;

/**
 *
 */
class AVLTree {
private:
    struct Node {
        const int key;
        int balance;
        Node *left, *right, *parent;

        ~Node();
        Node(const int, Node *);
    };

    Node *root = nullptr;

    Node* singleLeftRotate(Node*);
    Node* singleRightRotate(Node *);
    Node* doubleRightRotate(Node *);
    Node* doubleLeftRotate(Node *);

    void reBalance(Node *);
    int height(Node *);
    void setBalance(Node *);
    void printBalance(Node *);

public:

    ~AVLTree();

    bool insert(const int);
    bool remove(const int);
    bool search(const int);
    void print();

    friend ostream &operator<<(ostream &, const AVLTree &);

};

#endif