#include <iostream>
#include <functional>
#include "library.h"

using namespace std;

/// Constructor for one Node.
/// \param [v] Value of new Node
/// \param [p] Node pointer of parent Node
AVLTree::Node::Node(const int v, Node *p) : key(v), balance(0), parent(p), left(nullptr), right(nullptr) {}

////Deconstructor for one Node.
AVLTree::Node::~Node() {
    delete left;
    delete right;
}

///Destructor for AVL Tree.
AVLTree::~AVLTree() {
    delete root;
}

/// A singel left rotation.
/// \param [n] Node for rotation
/// \return Rotated Nodes
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

/// A single right rotation.
/// \param [n] Node for rotation
/// \return Rotated Nodes
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

/// A double right rotation.
/// \param [n] Node for rotation
/// \return Rotated Nodes
AVLTree::Node *AVLTree::doubleRightRotate(Node *n) {
    n->left = singleLeftRotate(n->left);
    return singleRightRotate(n);
}

/// A double left rotation.
/// \param [n] Node for rotation
/// \return Rotated Nodes
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

/// Returns the height of the Node.
/// \param [n] Start node
/// \return Height of Node
int AVLTree::height(Node *n) {
    return (!n) ? -1 : 1 + max(height(n->left), height(n->right));
}

/// Sets the balance of the Nodes.
/// The AVL-Criterion from wikipedia.de
/// \param [n] Start node
void AVLTree::setBalance(Node *n) {
    n->balance = height(n->right) - height(n->left);
}

/// Returns if is the tree balanced.
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

/// Searches for a value in AVL Tree.
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

/// Removes a Node by value.
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

/// Inserts a Node.
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

/// Returns if AVL Tree is balanced.
/// \return true or false if AVL Tree is balanced
bool AVLTree::balanced() {
   return isBalanced(root);
}

/// Ausgabe als digtree (graphvizz) mit innere/äußere Nodebeschriftung und Kanten.
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
/*
/// DEBUGGING ONLY
int main() {
    AVLTree t;
    cout << "Inserting integer values 1 to 10" << endl;
    for (int i = 1; i <= 10; ++i) {
        t.insert(i);
    }
    cout << "AVL Tree nach insert: \n" << t.balanced() << endl;
    t.remove(5);
    cout << "AVLTree nach remove(): \n" << t << endl;
    cout << "AVLTree search for 5: " << (t.search(5) ? "was " : "not ") << "found" << endl;
    cout << "AVLTree search for 6: " << (t.search(6) ?  "" : "not ") << "found" << endl;
    cout << "AVL Tree is balanced: " << (t.balanced() ? "" : "not") << "balanced" << endl;

}
*/