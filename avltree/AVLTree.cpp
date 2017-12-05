#include <iostream>
#include "AVLTree.h"

using namespace std;

AVLTree::Node::Node(const int v, Node *p) : key(v), balance(0), parent(p), left(nullptr), right(nullptr) {}

AVLTree::Node::~Node() {
    delete left;
    delete right;
}

AVLTree::~AVLTree() {
    delete root;
}

AVLTree::Node *AVLTree::rotateLeft(Node *) {

}
AVLTree::Node * AVLTree::rotateRight(Node *) {

}

AVLTree::Node * AVLTree::rotateLeftThenRight(Node *) {

}

AVLTree::Node * AVLTree::rotateRightThenLeft(Node *) {

}

void AVLTree::rebalance(Node *) {

}

int AVLTree::height(Node *) {

}

void AVLTree::setBalance(Node *) {

}

void AVLTree::clearNode(Node *) {

}

void AVLTree::printBalance(Node *) {

}

bool AVLTree::search(const int v) {
    return false;
}

bool AVLTree::remove(const int v) {
    return false;
}

bool AVLTree::insert(const int v) {
    return false;
}

void AVLTree::print() {

}