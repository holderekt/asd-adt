/**
 * @file priority_queue.hpp
 * @author Ivan Diliso
 * Contact: diliso.ivan@gmail.com
 */


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

    void operator=(const PNode<T,P>& nodo){
        this->value = nodo.value;
        this->priority = nodo.priority;
    }

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
    PNode<T,P> read()const {return tree.get_root()->value; };
    bool empty(){return tree.isEmpty(); }
    void print(std::ostream& os){ os << tree; }

    template<class TT, class PP>
    friend std::ostream& operator<<(std::ostream& os, Priority_Queue<TT,PP>& prioque){
        if(!prioque.empty()){
            prioque.print(os);
        }
        return os;
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
    
    }else if (tree.get_root()->left == last){
        tree.remove(last);
        last = tree.get_root();

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


    /*
        Aggiustamento
    */

   std::cout << "mario" << std::endl;

    if(!empty()){
        Node* start = tree.get_root();
        bool flag = true;
        
        while(start != nullptr and !tree.leaf(start) && flag){

            if(start->right != nullptr && start->left != nullptr){
                if(start->right->value.priority > start->left->value.priority){
                    if(start->left->value.priority < dlvalue.priority){
                        start->value = start->left->value;
                        start = start->left;
                    }else{
                        flag = false;
                    }
                }else{
                    if(start->right->value.priority < dlvalue.priority){
                        start->value = start->right->value;
                        start = start->right;
                    }else{
                        flag = false;
                    }
                }
            }else if(start->left != nullptr){
                    if(start->left->value.priority < dlvalue.priority){
                        start->value = start->left->value;
                        start = start->left;
                    }else{
                        flag = false;
                    }
            }else if(start->right != nullptr){
                    if(start->right->value.priority < dlvalue.priority){
                        start->value = start->right->value;
                        start = start->right;
                    }else{
                        flag = false;
                    }
            }
        }

        if(start != nullptr)
            start->value = dlvalue;
    }
}
