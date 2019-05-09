#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template <typename T>
class BSTree; 

template <typename T>
class Iterator; 

template <typename T>
class Node {
    private:
        T data;
        Node<T> *left;
        Node<T> *right;

    template<class>
    friend class BSTree; 

    template<class>
    friend class Iterator;

public:
    Node(T data){
        left = right = nullptr;
        this->data = data;
    };

    void genocidio(){
        if (left) left->genocidio();
        if (right) right->genocidio();
        delete this;
    };





};

#endif