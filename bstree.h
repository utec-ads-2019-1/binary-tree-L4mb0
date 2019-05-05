#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"
#include <stack>


template<typename T>
class BSTree {
private:
    Node<T> *root;
    unsigned int nodes;

public:

    BSTree() : root(nullptr) {
        this->nodes = 0;
    }

    void swap(T a, T b){
        T temp;
        temp = b;
        b= a;
        a = temp;
    }

    bool find(T data) {
        if (!root) {
            return false;
        } else /**/{
            if (root->data == data) { return true; }
            auto iterador = root;
            while (iterador) {
                if (data > iterador->data) {
                    iterador = iterador->right;
                } else if (data < iterador->data) {
                    iterador = iterador->left;
                } else {
                    return true;
                }
            }
            return false;
        }
    }

    bool insert(T data) {
        if (!find(data)) {
            auto nuevoNodo = new Node<T>(data);
            auto iterador = root;
            if (root == nullptr) {
                root = nuevoNodo;
                nodes++;
                return true;
            }
            while (iterador) {
                if (data > iterador->data) {
                    if (iterador->right)
                        iterador = iterador->right;
                    else {
                        iterador->right = nuevoNodo;
                        nodes++;
                        return true;
                    }
                } else if (data < iterador->data) {
                    if (iterador->left)
                        iterador = iterador->left;
                    else {
                        iterador->left = nuevoNodo;
                        nodes++;
                        return true;
                    }
                }
            }
            return false;
        } else return false;
    }



    //trate de haerlo iterativamente pero esta bien feito, pero deberia funcar para arboles balanceados
    /*bool remove(T data) {
        if(find(data)){
            auto iterador = root;
            auto parent = new Node<T>(data);
            while(iterador) {
                if (data < iterador->data) {
                    parent = iterador;
                    iterador = iterador->left;
                }
                else if (data > iterador->data) {
                    parent = iterador;
                    iterador = iterador->right;
                }
                else{
                    if (!iterador->right && !iterador->left){
                        if (parent->left == iterador) {
                            parent->left = nullptr;
                        }
                        else {
                            parent->right = nullptr;
                        }

                        delete iterador;
                        nodes--;
                        return true;
                    }
                    else if (!iterador->right || !iterador->left){
                        if(iterador->left) parent->left = iterador->left; else parent->left = iterador->right;

                        if(iterador->right) parent->right = iterador->right; else parent->right = iterador->left;
                        delete iterador;
                        nodes--;
                        return true;
                    }
                    else{
                        auto sacrificio = iterador->left;
                        while(sacrificio->right){
                            parent = sacrificio;
                            sacrificio = sacrificio->right;
                        }
                        iterador->data = sacrificio->data;
                        parent->right = nullptr;
                        delete sacrificio;
                        nodes--;
                        return true;

                    }




                }


            }
        } else return false;
    }*/

    //trate de armarlo con doble puntero pero tengo mis limitaciones :,v
    bool remove(T data) {
        if(find(data)) {

            Node<T> **fatherptr;
            auto daLeft = (*fatherptr)->left;
            auto daRight = (*fatherptr)->right;

            if (daLeft && daRight) {
                *fatherptr = daLeft;
                while (daLeft->right) {
                    daLeft = daLeft->right;
                }
                daLeft->right = daRight;
            } else if (daLeft || daRight) {
                *fatherptr = daLeft ? daLeft : daRight;
            } else {
                delete *fatherptr;
            }
            nodes--;
            return true;
        }
    }

    unsigned int size() {
        return nodes;
    }

    void traversePreOrder(Node<T> node) {
        if (!node) return;
        printf("%d ", root->data);
        traversePreOrder(node.left);
        traversePreOrder(node.right);

    }

    void traverseInOrder(Node<T> node) {
        if (!node) return;
        printf("%d ", root->data);
        traversInOrder(node.left);
        traverseInOrder(node.right);
    }

    void traversePostOrder(Node<T> node) {
        if (!node) return;
        traversPostOrder(node.left);
        traversePostOrder(node.right);
        printf("%d ", root->data);
    }

    Node<T> goAllRight(){
        auto iterador = root;
        while (iterador){
            if (iterador->right){
                iterador = iterador->right;
            }
            else return iterador;
        }
    }

    Node<T> goAllLeft(){
        auto iterador = root;
        while (iterador){
            if (iterador->left){
                iterador = iterador->left;
            }
            else return iterador;
        }
    }

    Iterator<T> begin() {
        stack<Node<T>*> tempStack;
        auto sacrificio = root;
        while(sacrificio->left){
            tempStack.push(sacrificio);
            sacrificio=sacrificio->left;
        }

       // return Iterator<T>(sacrificio, tempStack);
    }

    Iterator<T> end() {
        stack<Node<T>*> tempStack;// return Iterator<T>(root, tempStack);

    }

    ~BSTree() {
        if (root) root->genocidio();
        root=nullptr;
    };
};

#endif
