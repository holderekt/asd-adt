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

        while(!tree.leaf(curr)){
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
    value_type dlvalue = last->value;

    if(last == tree.get_root()){
        tree.remove(tree.get_root());
        last = nullptr;

    }else if( tree.dx(last->parent) == last){
        Node* app = last;
        last = last->parent->left;
        tree.remove(app);
   
    }else{
        Node* curr = last;

        while((curr != tree.get_root()) && (tree.sx(curr->parent) == curr)){
            curr = curr->parent;
        }

        if(curr == tree.get_root()){
            curr = tree.dx(tree.get_root());
        }else{
            curr = tree.sx(curr->parent);
        }

        while(!tree.leaf(curr)){
            curr = curr->right;
        }
        tree.remove(last);
        last = curr;
    }

    Node* n = tree.get_root();

    while(!tree.leaf(n)){
        if(n->left != nullptr and n->right != nullptr){
            if( n->left->value < n->right->value){
                // Sinistro
                if(n->left->value < dlvalue){
                    value_type app = n->left->value;
                    n->left->value = n->value;
                    n->value = app;
                    n = n->left;
                }
            }else{
                    // Destro
                    if(n->right->value < dlvalue){
                    value_type app = n->right->value;
                    n->right->value = n->value;
                    n->value = app;
                    n = n->right;
                }
            }
        }else{
            if(n->left->value < dlvalue){
                // Sinistro
                            // Sinistro
                if(n->left->value < dlvalue){
                    value_type app = n->left->value;
                    n->left->value = n->value;
                    n->value = app;
                    n = n->left;
                }
            }
        }
    }
    n->value = dlvalue;
}

