#include <iostream>
#include <functional>
#include <search.h>
#include "AVLTree.h"

using namespace std;

/** Constructor for one Node.
 *
 * @param v Value of new Node
 * @param p Node pointer of parent Node
 */
AVLTree::Node::Node(const int v, Node *p) : key(v), balance(0), parent(p), left(nullptr), right(nullptr) {}

/** Deconstructor for one Node.
 *
 */
AVLTree::Node::~Node() {
    delete left;
    delete right;
}

/** Destructor for AVL Tree.
 *
 */
AVLTree::~AVLTree() {
    delete root;
}

/**
 *
 * @param n
 * @return
 */
AVLTree::Node *AVLTree::singleLeftRotate(Node *n) {
    Node *tmp = n->right;
    tmp->parent = n->parent;
    n->right = tmp->left;
    if (n->right) {
        n->right->parent = n;
    }
    tmp->left = n;
    n->parent = tmp;
    if (tmp->parent) {
        if (tmp->parent->right == n) {
            tmp->parent->right = tmp;
        } else {
            tmp->parent->left = tmp;
        }
    }
    setBalance(n);
    setBalance(tmp);
    return tmp;
}

/**
 *
 * @param n
 * @return
 */
AVLTree::Node *AVLTree::singleRightRotate(Node *n) {
    Node *tmp = n->left;
    tmp->parent = n->parent;
    n->left = tmp->right;
    if (n->left) {
        n->left->parent = n;
    }
    tmp->right = n;
    n->parent = tmp;
    if (tmp->parent) {
        if (tmp->parent->right == n) {
            tmp->parent->right = tmp;
        } else {
            tmp->parent->left = tmp;
        }
    }
    setBalance(n);
    setBalance(tmp);
    return tmp;
}

/**
 *
 * @param n
 * @return
 */
AVLTree::Node *AVLTree::doubleRightRotate(Node *n) {
    n->left = singleLeftRotate(n->left);
    return singleRightRotate(n);
}

/**
 *
 * @param n
 * @return
 */
AVLTree::Node *AVLTree::doubleLeftRotate(Node *n) {
    n->right = singleRightRotate(n->right);
    return singleLeftRotate(n);
}

/**
 *
 * @param n
 */
void AVLTree::reBalance(Node *n) {

}

/** Returns the height of the Node.
 *
 * @param n Start node
 * @return Height of Node
 */
int AVLTree::height(Node *n) {
    if (!n) {
        return -1;
    }
    return 1 + max(height(n->left), height(n->right));
}

/** Sets the balance of the Nodes.
 *
 * @param n Start node
 */
void AVLTree::setBalance(Node *n) {
    n->balance = height(n->right) - height(n->left);
}

/**
 * Prints the balance of the Nodes.
 * @param n Start node
 */
void AVLTree::printBalance(Node *n) {
    if (n) {
        printBalance(n->left);
        cout << n->balance << " ";
        printBalance(n->right);
    }
}

/** Searches for a value in AVL Tree.
 *
 * @param v Value of Node
 * @return true or false if Node was found
 */
bool AVLTree::search(const int v) {
    function<bool(const int, Node *)> treeSearch = [&](const int k, Node *n) {
        if (n) {
            if (k == n->key) {
                return true;
            }
            if (k < n->key) {
                return treeSearch(k, n->left);
            } else {
                return treeSearch(k, n->right);
            }
        } else {
            return false;
        }
    };
    return treeSearch(v, root);
}

/** Removes a Node by value.
 *
 * @param v Value of Node
 * @return true or false if Node was deleted
 */
bool AVLTree::remove(const int v) {

    return false;
}

/** Inserts a Node.
 *
 * @param v New Key for the new Node
 * @return true or false if a Node was inserted
 */
bool AVLTree::insert(const int v) {
    if (!root) {
        root = new Node(v, nullptr);
        return true;
    } else {
        Node *n = root, *parent;
        while (true) {
            if (n->key == v) {
                return false;
            }
            parent = n;
            bool left = v < n->key;
            n = left ? n->left : n->right;
            if (!n) {
                if (left) {
                    parent->left = new Node(v, parent);
                } else {
                    parent->right = new Node(v, parent);
                }
                reBalance(parent);
                break;
            }
        }
        return true;
    }
}

/** Prints the balance of the AVL Tree from root.
 *
 */
void AVLTree::print() {
    printBalance(root);
}

/*
// DEBUGGING
int main() {
    AVLTree t;

    cout << "Inserting integer values 1 to 10" << endl;
    for (int i = 1; i <= 10; ++i) {
        t.insert(i);
    }
    t.print();
    t.remove(5);
    cout << "Printing balance: ";
    t.print();
}*/