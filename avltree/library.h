#ifndef BLATT_7_AUFGABE_1_TRON_LIBRARY_H
#define BLATT_7_AUFGABE_1_TRON_LIBRARY_H

#include <iostream>

using namespace std;

/// Header class for an AVL Tree.
/// \authors Maximilian Schmitz, Salman
/// \date 7.12.2017
///
/// \version 0.9
/// Toten Code entfernt.
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
    bool isBalanced(Node *);

public:

    ~AVLTree();

    bool insert(const int);
    bool remove(const int);
    bool search(const int);
    bool balanced();

    friend ostream &operator<<(ostream &, const AVLTree &);

};

#endif