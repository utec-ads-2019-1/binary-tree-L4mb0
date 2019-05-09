#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>

template<typename T>
class Iterator {
protected:
    Node<T> *current;
    stack<Node<T>*> *daStack;
    stack<Node<T>*> *oldStack;


public:
    Iterator() : current(nullptr) {
        this->daStack = new stack<Node<T>*>();
        this->oldStack = new stack<Node<T>*>();

    }

    Iterator(Node<T> *node) : current(node){

    }

    Iterator<T>& operator=(Iterator<T> other) {
        current = other.current;
        daStack = other.daStack;
        return *this;
    }

    bool operator!=(Iterator<T> other) {
        return current->data != other.current->data;
    }

    Iterator<T> operator++() {
        oldStack->push(daStack->top());
        daStack->pop();

        if (current->right){
            auto iterador= current->right;
            while(iterador){
                daStack->push(iterador);
                iterador=iterador->left;
            }
        }
        if (!daStack->empty()){
            current=daStack->top();
        } else current= nullptr;


        return *this;
    }

    Iterator<T> operator--() {
        daStack->push(oldStack->top());
        oldStack->pop();
        current = daStack->top();
        return *this;
    }

    T operator*() {
        return current->data;
    }

};

#endif
