#pragma once

#include <iostream>
#include "../bintree/bintree.hpp"

template <class T>
class Priority_Queue{
public:
   
    typedef typename Binary_Tree<T>::Node Node;
    typedef typename Binary_Tree<T>::value_type value_type;

    Priority_Queue();
    void insert(value_type value);
    void remove();

    void print(){
        std::cout << tree << std::endl;
    }

private:
    Binary_Tree<T> tree;
    Node* last;

    void _reorder();
};

template <class T>
Priority_Queue<T>::Priority_Queue(){
    tree.create();
    last = nullptr;
}

template <class T>
void Priority_Queue<T>::insert(value_type value){
    if(tree.isEmpty()){
        tree.insert_root(value);
        last = tree.get_root();
        
    }else if( last == tree.get_root()){
        last = tree.insertsx(last,value);
        
    }else if(tree.sx(last->parent) == last){
        last = tree.insertdx(last->parent,value);
        
    }else{
        Node* curr = last;

        while((curr != tree.get_root()) && (tree.dx(curr->parent) == curr)){
            curr = curr->parent;
        }

        if(curr == tree.get_root()){
            curr = tree.sx(tree.get_root());
        }else{
            curr = tree.dx(curr->parent);
        }

        while(!tree.isEmpty_sx(curr) && !tree.isEmpty_dx(curr)){
            curr = curr->left;
        }

        last = tree.insertsx(curr, value);
    }

    _reorder();
}

template <class T>
void Priority_Queue<T>::_reorder(){
    Node* curr = last;
    while((curr != tree.get_root()) && (curr->parent->value > curr->value)){
        value_type app = curr->parent->value;
        curr->parent->value = curr->value;
        curr->value = app;

        curr = curr->parent;
    }
}

template <class T>
void Priority_Queue<T>::remove(){
    if(last == tree.get_root()){
        tree.remove(tree.get_root());
    }else if( tree.dx(last->parent) == last){
        Node* app = last;
        last = last->parent->left;
        tree.remove(app);
    }
}