#ifndef BLATT_7_AUFGABE_1_TRON_LIBRARY_H
#define BLATT_7_AUFGABE_1_TRON_LIBRARY_H

#include <iostream>

using namespace std;

/// Header class for an AVL Tree.
/// \authors Maximilian Schmitz, Salman
/// \date 20.12.2017/
/// \version 1.0
class AVLTree {
private:

    /// Struct for one Node.
    struct Node {

        /// Key of node.
        const int key;

        /// Balance of node.
        int balance;

        /// Nodes left right and parent.
        Node *left, *right, *parent;

        /// Deconstructor for one node.
        ~Node();

        /// Constructor for one node.
        Node(const int, Node *);
    };

    /// Pointer for root node.
    Node *root = nullptr;

    /// Rotates the tree
    /// \return the new root node
    Node* singleLeftRotate(Node*);

    ///
    /// \retrun the new root node
    Node* singleRightRotate(Node *);

    ///
    /// \return the new root node
    Node* doubleRightRotate(Node *);

    ///
    /// \return the new root node
    Node* doubleLeftRotate(Node *);

    /// Rebalancing the tree.
    void reBalance(Node *);

    /// Checks the height of the node.
    /// \return the height of the parameter node.
    int height(Node *);

    /// Set the balance of the parameter node.
    void setBalance(Node *);

    /// Checks if the tree at the parameter is balanced.
    /// \return true or false if the tree is balanced
    bool isBalanced(Node *);

public:

    /// Deconstructor for the complete tree.
    ~AVLTree();

    /// Adds a node with the parameter to the tree.
    /// \return true or false if a node with the value was created and inserted.
    bool insert(const int);

    /// Delete a node with the parameter.
    /// \return true or false if the value was deleted
    bool remove(const int);

    /// Searches for the parameter in the tree.
    /// \return true or false if the value is in the tree
    bool search(const int);

    /// Checks if the tree is balanced or not.
    /// \return troue or false if tree is balanced
    bool balanced();

    /// Returns the tree as format graphviz tree.
    /// \return treea as format: graphviz tree
    friend ostream &operator<<(ostream &, const AVLTree &);

};

#endif