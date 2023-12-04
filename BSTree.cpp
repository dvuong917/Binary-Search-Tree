#include "BSTree.h"

BSTree::BSTree() {
    this->root = nullptr;
    numOfNodes = 0;
};
BSTree::~BSTree() {
    clear(this->root);
};
void BSTree::clear(Node *node) { // recursively delete every node
    if (node) {
        clear(node->getLeftChild());
        clear(node->getRightChild());
        delete node;
    }
};
void BSTree::insert(const string &newString) {
    Node* newNode = new Node(newString, 1);
    ++numOfNodes;
    if (findNode(newString) != nullptr) { // string already in an existing node
        findNode(newString)->addIntCount();
        delete newNode;
        newNode = nullptr;
    }
    else if (root == nullptr) { // inserting into empty tree
        root = newNode;
    }
    else { // inserting into non empty tree
        Node* curr = root;
        while (curr != nullptr) {
            if (newNode->getData() < curr->getData()) { // inserting as left child
                if (curr->getLeftChild() == nullptr) {
                    curr->setLeftChild(newNode);
                    curr = nullptr;
                }
                else {
                    curr = curr->getLeftChild();
                }
            }
            else { // inserting as right child
                if (curr->getRightChild() == nullptr) {
                    curr->setRightChild(newNode);
                    curr = nullptr;
                }
                else {
                    curr = curr->getRightChild();
                }
            }
        }
    }
};
void BSTree::remove(const string &key) { 
    Node* nodeToRemove = findNode(key);
    if (nodeToRemove != nullptr) {
        --numOfNodes;
        if (nodeToRemove->getIntCount() > 1) { // remove from node with > 1 of the string
            nodeToRemove->subtractIntCount();
            return;
        }
        // removing leaf node
        if (isLeaf(nodeToRemove) && nodeToRemove == root) {
            nodeToRemove = nullptr;
            root = nullptr;
        }
        else if (isLeaf(nodeToRemove) && nodeToRemove != root) {
            Node* parent = findParent(nodeToRemove);
            if (nodeToRemove == parent->getLeftChild()) {
                parent->setLeftChild(nullptr);
            }
            else if (nodeToRemove == parent->getRightChild()) {
                parent->setRightChild(nullptr);
            }
        }
        // removing an internal node
        else {
            Node* successor = findSuccessor(nodeToRemove);
            int successorCount = successor->getIntCount();
            string successorString = successor->getData();
            successor->setIntCount(0);
            remove(successor->getData());
            nodeToRemove->setIntCount(successorCount);
            nodeToRemove->setData(successorString);
        }
    }
};
bool BSTree::search(Node* root, const string &key) const { // recursively searches
    if (root == nullptr) {
        return false;
    }
    if (key == root->getData()) {
        return true;
    }
    else {
        if (key < root->getData()) {
            return search(root->getLeftChild(), key);
        }
        else {
            return search(root->getRightChild(), key);
        }
    }
}
bool BSTree::search(const string &key) const { // calls on recursive helper function
    return search(this->getRoot(), key);
};
Node* BSTree::findNode(const string &key) const { // does same as search but returns node containing the key (non-recursive)
    Node* curr = root;
    while (curr != nullptr) {
        if (key == curr->getData()) {
            return curr;
        }
        else if (key < curr->getData()) {
            curr = curr->getLeftChild();
        }
        else {
            curr = curr->getRightChild();
        }
    }
    return nullptr;
};
int BSTree::getNodeCount() const {
    return this->numOfNodes;
};
Node* BSTree::getRoot() const {
    return this->root;
};
Node* BSTree::findSuccessor(Node* node) const { // helps with remove function
    // node has single child
    Node* successor = node;
    if (node->getLeftChild() != nullptr && node->getRightChild() == nullptr) {
        successor = node->getLeftChild();
        while (successor->getRightChild() != nullptr) {
            successor = successor->getRightChild();
        }
        return successor;
    }
    else if (node->getLeftChild() == nullptr && node->getRightChild() != nullptr) {
        successor = node->getRightChild();
        while (successor->getLeftChild() != nullptr) {
            successor = successor->getLeftChild();
        }
        return successor;
    }
    // node has two children, successor will be left subtree's rightmost node
    else {
        successor = node->getLeftChild();
        while (successor->getRightChild() != nullptr) {
            successor = successor->getRightChild();
        }
        return successor;
    }
    return nullptr;
};
Node* BSTree::findParent(const Node* node) const {
    Node* parent = nullptr;
    Node* curr = root;
    while (curr != nullptr && node != root) {
        if (curr->getLeftChild() == node) {
            parent = curr;
            return parent;
        }
        else if (curr->getRightChild() == node) {
            parent = curr;
            return parent;
        }
        else {
            if (node->getData() < curr->getData()) {
                curr = curr->getLeftChild();
            }
            else if (node->getData() > curr->getData()) {
                curr = curr->getRightChild();
            }
        }
    }
    return nullptr;
};
bool BSTree::isLeaf(const Node* node) const {
    if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) {
        return true;
    }
    else { 
        return false;
    }
};
string BSTree::largest() const {
    Node* curr = root;
    if (curr != nullptr) {
        while (curr->getRightChild() != nullptr) {
            curr = curr->getRightChild();
        }
        return curr->getData();
    }
    else {
        return "";
    }
};
string BSTree::smallest() const {
    Node* curr = root;
    if (curr != nullptr) {
        while (curr->getLeftChild() != nullptr) {
            curr = curr->getLeftChild();
        }
        return curr->getData();
    }
    else {
        return "";
    }
};
int BSTree::height(Node* node) const { // private helper function
    if (node == nullptr) {
        return -1;
    }
    else {
        return max(height(node->getLeftChild()), height(node->getRightChild())) + 1;
    }
};
int BSTree::height(const string& key) const {
    Node* nodeForHeight = findNode(key);
    return height(nodeForHeight);
};
void BSTree::preOrder(Node *root) const { // private recursive helper function for preOrder
    if (root != nullptr) {
        cout << root->getData() << "(" << root->getIntCount() << "), ";
        preOrder(root->getLeftChild());
        preOrder(root->getRightChild());
    }
};
void BSTree::postOrder(Node *root) const { // private recursive helper function for postOrder
    if (root != nullptr) {
        postOrder(root->getLeftChild());
        postOrder(root->getRightChild());
        cout << root->getData() << "(" << root->getIntCount() << "), ";
    }
};
void BSTree::inOrder(Node *root) const { // private recursive helper function for inOrder
    if (root != nullptr) {
        inOrder(root->getLeftChild());
        cout << root->getData() << "(" << root->getIntCount() << "), ";
        inOrder(root->getRightChild());
    }
};
void BSTree::preOrder() const {
    preOrder(this->root);
};
void BSTree::postOrder() const {
    postOrder(this->root);
};
void BSTree::inOrder() const {
    inOrder(this->root);
};