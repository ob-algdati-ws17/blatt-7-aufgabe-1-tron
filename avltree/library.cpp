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
    cout << "SLR" << endl;
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
    cout << "SRR" << endl;
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
    cout << "DRR" << endl;
    n->left = singleLeftRotate(n->left);
    return singleRightRotate(n);
}

/// \param [n] Node for rotation
/// \return New rotated root node
AVLTree::Node *AVLTree::doubleLeftRotate(Node *n) {
    cout << "DLR" << endl;
    n->right = singleRightRotate(n->right);
    return singleLeftRotate(n);
}

/// Reblanaced the AVL Tree.
/// \param [n] Rebalanced Nodes
void AVLTree::reBalance(Node *n) {
    if (!n) {
        return;
    }
    setBalance(n);
        // Wenn rechter Teilbaum überwiegt (-> r)
    if (n->balance == 2) {
            // Wenn linker Teilbaum des Teilbaumes überwiegt (-> r -> l)
        if (height(n->right->left) >= height(n->right->right)) {
            n = doubleLeftRotate(n);
        }
            // Wenn rechter Teilbaum des Teilbaumes überwiegt (-> r -> r)
        else {
            n = singleLeftRotate(n);
        }
    }
        // Wenn linker Teilbaum überwiegt (-> l)
    else if (n->balance == -2) {
            // Wenn rechter Teilbaum des Teilbaumes überwiegt (-> l -> r)
        if (height(n->left->right) >= height(n->left->left)) { // Tree's left subtree is right heavy
            n = doubleRightRotate(n);
        }
            // Wenn linker Teilbaum des Teilbaumes überwiegt (-> l -> l)
        else {
            n = singleRightRotate(n);
        }
    }
    // Rekursiv nach oben zur Wurzel gehen
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

    Node *n = root;
    Node *deleteNode = nullptr;
    // Solange Knoten nicht gefunden oder nicht am Blatt angekommen
    function<void(const int)> treeRemove = [&n, &deleteNode, &treeRemove] (const int key) {
        if (!deleteNode && !n) {
            return;
        } else {
            if (n->key == key) {
                deleteNode = n;
                return;
            } else {
                n = key >= n->key ? n->right : n->left;
                treeRemove(key);
            }
        }
    };
    treeRemove(v);
//    while (!deleteNode && n) {
//
//        if (n->key == v) {
//            deleteNode = n;
//        }
//        else {
//            n = v >= n->key ? n->right : n->left;
//        }
//    }
    if (deleteNode) {
        Node *parent = deleteNode->parent;
        // Prüfen, ob Nachfolger Knoten oder Blätter sind
        if (deleteNode->left) {
                // Wenn beide Nachfolger Knoten
            if (deleteNode->right) {
                // Symmetrischen Nachfolger bestimmen
                Node *follower = deleteNode->right;
//                function<void(Node *)> searchFollower = [&] (Node *f) {
//                    if (!f->left) {
//                        return;
//                    } else {
//                        searchFollower(f->left);
//                    }
//                };
//                searchFollower(follower);
                while (follower->left) {
                    follower = follower->left;
                }
                // Den zu löschenden Knoten durch einen neuen ersetzen mit dem
                // Schlüssel vom Symmetrischen Nachfolger
                n = new Node(follower->key, parent);
                // Symmetrischen Nachfolger löschen
                remove(follower->key);
                n->left = deleteNode->left;
                n->right = deleteNode->right;

            }
                // Nur linker Nachfolger Knoten
            else {
                n = deleteNode->left;
            }
        }
            // Nur rechter Nachfolger Knoten
        else if (right) {
            n = deleteNode->right;
        }
            // Beide Nachfolger Blätter
        else {
            // Den zu löschenden Knoten durch Blatt ersetzen
            n = nullptr;
        }
        // Wenn parent nicht null, Nachfolger richtig festlegen
        if (parent) {
            if (parent->right == deleteNode) {
                parent->right = n;
            } else {
                parent->left = n;
            }
        }
        else {
            root = n;
        }
        // Knoten löschen
        deleteNode->right = nullptr;
        deleteNode->left = nullptr;
        delete deleteNode;
        reBalance(parent);
        return true;

    }
    return false;
}

/// \param [v] New Key for the new Node
/// \return true or false if a Node was inserted
bool AVLTree::insert(const int v) {
    // Wenn der Baum leer ist, neues Element für root
    if (!root) {
        root = new Node(v, nullptr);
        return true;
        // Wenn der Baum nicht leer ist
    } else {
        Node *n = root, *parent;
        // Solange n nicht nullpointer
        function<bool(const int, Node*, Node*)> treeInsert = [&] (const int key, Node *p, Node *node) {
            if (node->key == key) {
                return false;
            }
            p = node;
            bool left = key < node->key;
            node = left ? node->left : node->right;
            if (!node) {
                if (left) {
                    p->left = new Node(key, p);
                } else {
                    p->right = new Node(key, p);
                }
                reBalance(p);
                return true;
            } else {
                treeInsert(key, p, node);
            }
        };
        return treeInsert(v, parent, n);
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