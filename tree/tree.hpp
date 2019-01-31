#pragma once
#include "../linked_list/linked_list.hpp"
#include <string>
#include <iostream>

template <class T>
class Tree;

template <class T>
struct TNode{
    friend class Tree<T>;

    template<class Z>
    friend std::ostream& operator<<(std::ostream& os, const Linked_list<TNode<Z>*>& lista){
        os << "[";
        for(typename Linked_list<TNode<Z>*>::position p = lista.begin(); !(lista.end(p)); p = lista.next(p)){
            os << lista.read(p)->value;
            if(lista.next(p) != lista.previous(lista.begin()))
                os << ",";
        }
        os << "]\n";
        return os;
    }

    TNode(typename Tree<T>::value_type value){
        this->value = value;
        this->parent = nullptr;
    }

    size_t size(){
        return childs->size();
    }

    typename Tree<T>::value_type value;
    Linked_list<TNode<T>*> childs; 
    TNode* parent;
};

template <class T>
class Tree{
public:
    typedef T value_type;
    typedef TNode<T> Node;

    Tree();
    Tree(const Tree<T>&);
    //~Tree();

    void create();
    void insert_root(value_type value);
    Node* insert_child(Node*, value_type value);
    Node* get_root() const;
    Node* parent(Node*) const;
    bool leaf(Node*) const;


private:
    Node* root;
    size_t dsize;
};

template <class T>
void Tree<T>::create(){
    root = nullptr;
    dsize = 0;
}

template <class T>
Tree<T>::Tree(){
    create();
}

template <class T>
void Tree<T>::insert_root(value_type value){
    root = new Node(value);
    dsize++;
}

template <class T>
typename Tree<T>::Node* Tree<T>::insert_child(Node* n, value_type value){
    if(n == nullptr)
        throw "Nodo nullo";
 
    Node* new_node = new Node(value);
    new_node->parent = n;
    n->childs.push_back(new_node);
    return new_node;
}

template <class T>
typename Tree<T>::Node* Tree<T>::get_root() const{
    return root;
}

template <class T>
typename Tree<T>::Node* Tree<T>::parent(Node* n) const{
    if(n!= nullptr)
        throw "Nodo nullo";

    return n->parent;
}

template <class T>
bool Tree<T>::leaf(Node* n) const{
    return (n->childs.empty());
}
