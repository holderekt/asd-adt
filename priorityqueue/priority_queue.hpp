#pragma once

#include <iostream>
#include "../bintree/bintree.hpp"

template <class T, class P>
class Priority_Queue;


template <class T, class P>
struct PNode{
    friend class Priority_Queue<T,P>;

    template <class TT, class PP>
    friend std::ostream& operator<<(std::ostream& os, PNode<TT,PP> n){
        os << n.value << " : " << n.priority;
        return os;
    }

    PNode(){};
    PNode(T value, P priority):value(value), priority(priority){}

    T value;
    P priority;
};

template <class T, class P>
class Priority_Queue{
public:
    
    typedef typename Binary_Tree<PNode<T,P>>::Node Node;
    typedef T value_type;
    typedef P priority_value;

    Priority_Queue();
    void insert(value_type, priority_value);
    void remove();

    void print(){
        std::cout << tree << std::endl;
    }

private:
    Binary_Tree<PNode<T,P>> tree;
    Node* last;

    void _reorder();
};

template <class T, class P>
Priority_Queue<T,P>::Priority_Queue(){
    tree.create();
    last = nullptr;
}

template <class T, class P>
void Priority_Queue<T,P>::insert(value_type value, priority_value priority){
    PNode<T,P> nodo(value, priority);

    if(tree.isEmpty()){
        tree.insert_root(nodo);
        last = tree.get_root();
        
    }else if( last == tree.get_root()){
        last = tree.insertsx(last, nodo);
        
    }else if(tree.sx(last->parent) == last){
        last = tree.insertdx(last->parent, nodo);
        
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

        last = tree.insertsx(curr, nodo);
    }

    _reorder();
}

template <class T, class P>
void Priority_Queue<T,P>::_reorder(){
    Node* curr = last;
    while((curr != tree.get_root()) && (curr->parent->value.priority > curr->value.priority)){
        PNode<T,P> app;
        app.priority = curr->parent->value.priority;
        app.value = curr->parent->value.value;
        curr->parent->value.priority = curr->value.priority;
        curr->parent->value.value = curr->value.value;
        curr->value.value = app.value;
        curr->value.priority = app.priority;

        curr = curr->parent;
    }
}

template <class T, class P>
void Priority_Queue<T,P>::remove(){
    
    PNode<T,P> dlvalue = last->value;

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
            if( n->left->value.priority < n->right->value.priority){
                //Sinistro
                if(n->left->value.priority < dlvalue.priority){
                    PNode<T,P> app;
                    app.value = n->left->value.value;
                    app.priority = n->left->value.priority;

                    n->left->value.value = n->value.value;
                    n->left->value.priority = n->value.priority;
                    n->value.value = app.value;
                    n->value.priority = app.priority;
                    n = n->left;
                }
            }else{
                    //Destro
                    PNode<T,P> app;
                    app.value = n->right->value.value;
                    app.priority = n->right->value.priority;

                    n->right->value.value = n->value.value;
                    n->right->value.priority = n->value.priority;
                    n->value.value = app.value;
                    n->value.priority = app.priority;
                    n = n->right;
                }
        }else{
            if(n->left->value.priority < dlvalue.priority){
                //Sinistro
                  //          Sinistro
         
                    PNode<T,P> app;
                    app.value = n->left->value.value;
                    app.priority = n->left->value.priority;

                    n->left->value.value = n->value.value;
                    n->left->value.priority = n->value.priority;
                    n->value.value = app.value;
                    n->value.priority = app.priority;
                    n = n->left;
                
            }
        }
    }
    n->value.priority = dlvalue.priority;
    n->value.value = dlvalue.value;
}

