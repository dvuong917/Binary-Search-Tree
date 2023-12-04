#include "Node.h"

Node::Node() {
    data = "";
    intCount = 0;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 0;
};
Node::Node(string s, int c) {
    data = s;
    intCount = c;
    leftChild = nullptr;
    rightChild = nullptr;
    height = 0;
}
void Node::setData(string s) {
    this->data = s;
}
string Node::getData() const {
    return this->data;
};
int Node::getIntCount() const {
    return this->intCount;
};
void Node::setIntCount(int c) {
    this->intCount = c;
}
void Node::addIntCount() {
    this->intCount += 1;
};
void Node::subtractIntCount() {
    this->intCount -= 1;
}
Node* Node::getLeftChild() const {
    return this->leftChild;
};
Node* Node::getRightChild() const {
    return this->rightChild;
};
void Node::setLeftChild(Node* l) {
    this->leftChild = l;
};
void Node::setRightChild(Node* r) {
    this->rightChild = r;
};
int Node::getHeight() const {
    return this->height;
};
void Node::setHeight(int h) {
    this->height = h;
};
void Node::incHeight() {
    this->height += 1;
};
void Node::decHeight() {
    this->height -= 1;
};