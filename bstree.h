#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"
#include <stack>


template<typename T>
class BSTree {
protected:
    Node<T> *root;
    unsigned int nodes;

public:

    BSTree() : root(nullptr) {
        this->nodes = 0;
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

    /*bool remove(T data) {
        auto iterador = root;
        auto parent = root;
        while (iterador) {
            if (data < iterador->data) {
                parent = iterador;
                iterador = iterador->left;
            } else if (data > iterador->data) {
                parent = iterador;
                iterador = iterador->right;
            } else if (data == iterador->data) {

                ///NO CHILD
                if (!iterador->right && !iterador->left) {
                    if (parent->left == iterador) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }

                    delete iterador;
                    nodes--;
                    return true;

                ///ONE CHILD
                } else if (!iterador->right || !iterador->left) {
                    if (parent->left == iterador) {
                        if (iterador->left) { parent->left = iterador->left; }
                        else parent->left = iterador->right;
                    }

                    if (parent->right == iterador) {
                        if (iterador->right) parent->right = iterador->right;
                        else parent->right = iterador->left;
                    }
                    if (iterador == root) {
                        if (iterador->right) root = iterador->right;
                        else iterador->left;
                    }
                    delete iterador;
                    nodes--;
                    return true;

                ///TWO CHILD
                } else {
                    auto sacrificio = iterador->left;
                    parent = iterador;
                    while (sacrificio->right) {
                        parent = sacrificio;
                        sacrificio = sacrificio->right;
                    }
                    iterador->data = sacrificio->data;

                    if (parent != iterador) {
                        if (!sacrificio->left) {
                            parent->right = nullptr;
                            nodes--;
                            return true;
                        } else {
                            parent->right = sacrificio->left;
                            nodes--;
                            return true;

                        }
                    } else {
                        if (!sacrificio->left) {
                            parent->left = nullptr;
                            nodes--;
                            return true;
                        } else {
                            parent->left = sacrificio->left;
                            delete sacrificio;
                            nodes--;
                            return true;

                        }
                    }
                }
            } else return false;
        }
        return false;
    }*/

//profesito bonito, lo intente con todito mi corazoncito, porfa dame los puntitos :,v
    bool remove(T data) {
        auto iterador = root;
        Node<T> **parent = &iterador;
        while (iterador) {
            if (data < iterador->data) {
                parent = &(iterador->left);
                iterador = iterador->left;
            } else if (data > iterador->data) {
                parent = &(iterador->right);
                iterador = iterador->right;
            } else if (data == iterador->data) {

                ///NO CHILD
                if (!iterador->right && !iterador->left) {
                    *parent = nullptr;
                    delete iterador;
                    nodes--;
                    return true;
                }

                ///ONE CHILD
                else if (iterador->right || iterador->left) {
                    if (iterador->right) {
                        *parent = iterador->right;
                        delete iterador;
                    } else if (iterador->left) {
                        *parent = iterador->left;
                        delete iterador;
                        nodes--;
                        return true;

                    }
                }

                ///TWO CHILD
                else{
                    auto rightest = iterador->left;
                    while (rightest->right != nullptr) {
                        rightest = rightest->right;
                    }
                    T temp = rightest->data;
                    remove(rightest->data);
                    iterador->data = temp;
                    delete iterador;
                    nodes--;
                    return true;
                }

            } else return false;
        }
        return false;
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
        traversInOrder(node.left);
        printf("%d ", root->data);
        traverseInOrder(node.right);
    }

    void traversePostOrder(Node<T> node) {
        if (!node) return;
        traversPostOrder(node.left);
        traversePostOrder(node.right);
        printf("%d ", root->data);
    }

    Node<T> goAllRight() {
        auto iterador = root;
        while (iterador) {
            if (iterador->right) {
                iterador = iterador->right;
            } else return iterador;
        }
    }

    Node<T> goAllLeft() {
        auto iterador = root;
        while (iterador) {
            if (iterador->left) {
                iterador = iterador->left;
            } else return iterador;
        }
    }

    Iterator<T> begin() {
        stack < Node<T> * > tempStack;
        auto sacrificio = root;
        while (sacrificio->left) {
            tempStack.push(sacrificio);
            sacrificio = sacrificio->left;
        }

        return Iterator<T>(root);
    }

    Iterator<T> end() {
        stack < Node<T> * > tempStack;
        return Iterator<T>(root);

    }

    ~

    BSTree() {
        if (root) root->genocidio();
        root = nullptr;
    };
};

#endif
