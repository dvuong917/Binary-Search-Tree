#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::string;

class Node {
    private:
        string data; // each node stores a string
        int intCount; // # of instances of stored string
        Node* leftChild;
        Node* rightChild;
        int height;
    public:
        Node();
        Node(string s, int c);
        string getData() const;
        void setData(string s);
        int getIntCount() const;
        void setIntCount(int c);
        void addIntCount();
        void subtractIntCount();
        Node* getLeftChild() const;
        Node* getRightChild() const;
        void setLeftChild(Node* l);
        void setRightChild(Node* r);
        int getHeight() const;
        void setHeight(int h);
        void incHeight();
        void decHeight();
};

#endif