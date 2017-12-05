#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

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

    Node* rotateLeft(Node*);
    Node* rotateRight(Node *);
    Node* rotateLeftThenRight(Node *);
    Node* rotateRightThenLeft(Node *);

    void rebalance(Node *);
    int height(Node *);
    void setBalance(Node *);
    void printBalance(Node *);
    void clearNode(Node *);

public:

    ~AVLTree();

    bool insert(const int);
    bool remove(const int);
    bool search(const int);
    void print();

};

#endif //AVLTREE_AVLTREE_H
