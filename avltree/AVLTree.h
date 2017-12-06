#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

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

};

#endif //AVLTREE_AVLTREE_H
