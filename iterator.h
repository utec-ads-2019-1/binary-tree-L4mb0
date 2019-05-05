#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>

template<typename T>
class Iterator {
protected:
    Node<T> *current;
    stack<Node<T>*> daStack;

public:
    Iterator() : current(nullptr) {}

    Iterator(Node<T> *node) : current(node){
        //meto todos los valores al stack
        daStack.push(current);
        while(current->left){
            current = current->left;
            daStack.push(current);
        }
    }

    Iterator<T> operator=(Iterator<T> other) {
        current = other.current;
        daStack = other.daStack;
        return *this;
    }

    bool operator!=(Iterator<T> other) {
        return current->data != other.current->data;
    }

    Iterator<T> operator++() {
        if (current->right) {
            daStack.push(current);
            current = current->right;

            while (current->left) {
                daStack.push(current);
                current = current->left;
            }
        } else {
            while (!daStack.empty() && current == daStack.top()->right) {
                current = daStack.top();
                daStack.pop();
            }

            if (!daStack.empty()) {
                current = daStack.top();
                daStack.pop();
            }
        }

        return *this;
    }

    Iterator<T> operator--() {
        if (current->left) {
            daStack.push(current);
            current = current->left;

            while (current->right) {
                daStack.push(current);
                current = current->right;
            }
        } else {
            while (!daStack.empty() && current == daStack.top()->left) {
                current = daStack.top();
                daStack.pop();
            }

            if (!daStack.empty()) {
                current = daStack.top();
                daStack.pop();
            }
        }

        return *this;
    }

    T operator*() {
        return current->data;
    }

};

#endif
