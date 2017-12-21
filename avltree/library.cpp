#include <iostream>
#include <functional>
#include "library.h"

using namespace std;

/// \param [v] Value of new Node
/// \param [p] Node pointer of parent Node
AVLTree::Node::Node(const int v, Node *p) : key(v), balance(0), parent(p), left(nullptr), right(nullptr) {}

AVLTree::Node::~Node() {
    delete left;
    delete right;
}

AVLTree::~AVLTree() {
    delete root;
}

/// \param [n] Node for rotation
/// \return New rotated root node
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

/// \param [n] Node for rotation
/// \return New rotated root node
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

/// \param [n] Node for rotation
/// \return New rotated root node
AVLTree::Node *AVLTree::doubleRightRotate(Node *n) {
    n->left = singleLeftRotate(n->left);
    return singleRightRotate(n);
}

/// \param [n] Node for rotation
/// \return New rotated root node
AVLTree::Node *AVLTree::doubleLeftRotate(Node *n) {
    n->right = singleRightRotate(n->right);
    return singleLeftRotate(n);
}

/// Reblanaced the AVL Tree.
/// \param [n] Rebalanced Nodes
void AVLTree::reBalance(Node *n) {
    setBalance(n);
    if (n->balance == 2) { // Tree is right heavy
        if (height(n->right->left) >= height(n->right->right)) { // Tree's right subtree is left heavy
            n = doubleLeftRotate(n);
        } else {
            n = singleLeftRotate(n);
        }
    } else if (n->balance == -2) { // Tree is left heavy
        if (height(n->left->right) >= height(n->left->left)) { // Tree's left subtree is right heavy
            n = doubleRightRotate(n);
        } else {
            n = singleRightRotate(n);
        }
    }

    if (n->parent) {
        reBalance(n->parent);
    } else {
        root = n;
    }
}

/// \param [n] Start node
/// \return Height of Node
int AVLTree::height(Node *n) {
    return (!n) ? -1 : 1 + max(height(n->left), height(n->right));
}

/// The AVL-Criterion from wikipedia.de
/// \param [n] Start node
void AVLTree::setBalance(Node *n) {
    n->balance = height(n->right) - height(n->left);
}

/// \param [n] Node to check
/// \return true or false if tree is balanced
bool AVLTree::isBalanced(Node *n) {
    if(!n){
        return true;
    }
    else{
        int lh = height(n->left);
        int rh = height(n->right);
        if (lh - rh > 1 || rh - lh > 1) {
            return false;
        }
    }
    return true;
}

/// \param [v] Value of Node
/// \return true or false if Node was found
bool AVLTree::search(const int v) {
    function<bool(const int, Node *)> treeSearch = [&] (const int k, Node *n) {
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

/// \param [v] Value of Node
/// \return true or false if Node was deleted
bool AVLTree::remove(const int v) {
    if (!root) {
        return false;
    }

    Node *n = root;
    Node *parent = root;
    Node *deleteNode = nullptr;
    Node *child = root;

    while (child) {
        parent = n;
        n = child;
        child = v >= n->key ? n->right : n->left;
        if (v == n->key) {
            deleteNode = n;
            break;
        }
    }

    if (deleteNode) {
        deleteNode = n;
        child = n->left ? n->left : n->right;
        if (root->key == v) {
            root = child;
        } else {
            if (parent->left == n) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            reBalance(parent);
            delete deleteNode;
        }
        return true;
    }
    return false;
}

/// \param [v] New Key for the new Node
/// \return true or false if a Node was inserted
bool AVLTree::insert(const int v) {
    if (!root) {
        root = new Node(v, nullptr);
        return true;
    } else {
        Node *n = root, *parent;
        /// \todo while raus und gegen rekursion tauschen, wenn moeglich
        while (n) {
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

/// \return true or false if AVL Tree is balanced
bool AVLTree::balanced() {
   return isBalanced(root);
}

ostream &operator<<(ostream &os, const AVLTree &tree) {
    function<void(ostream &, const int, const int, const AVLTree::Node *, const string)> printToOs
            = [&](ostream &ost, const int value, const int balance, const AVLTree::Node *node, const string l) {

                static int nullcount = 0;

                if (!node) {
                    ost << "    null" << nullcount << "[shape=point];" << endl;
                    ost << "    " << value << "([Label=\"" << balance << "\"])" << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    ost << "    " << value << "([Label=\"" << balance << "\"])" << " -> " << node->key
                       << "([Label=\"" << node->balance << "\"])" << " [label=\"" << l << "\"];" << endl;

                    printToOs(ost, node->key, node->balance, node->left, "l");
                    printToOs(ost, node->key, node->balance, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (!tree.root) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->balance, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->balance, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}