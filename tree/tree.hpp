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
        if(!lista.empty()){
            for(typename Linked_list<TNode<Z>*>::position p = lista.begin(); !(lista.end(p)); p = lista.next(p)){
                os << lista.read(p)->value;
                if(lista.next(p) != lista.previous(lista.begin()))
                    os << ",";
            }
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
    typedef typename Linked_list<TNode<T>*>::position List_Node;

    Tree();
    Tree(const Tree<T>&);
    ~Tree();

    void create();
    void insert_root(value_type value);
    Node* insert_child(Node*, value_type value);
    Node* get_root() const;
    Node* parent(Node*) const;
    bool leaf(Node*) const;
    void remove(Node*);

    size_t depth() const;
    size_t distance(Node*) const;
    void _print(std::ostream&, Node*);
    Node* _copy(Node*, Node*);

    Node* insert_first_subtree(Node*, Tree<T>&);
    Node* insert_subtree(Node*, Tree<T>&);

    template<class Z>
    friend std::ostream& operator<<(std::ostream&, Tree<Z>&);
    void operator=(const Tree<T>&);

private:
    Node* root;
    size_t dsize;

    void _remove(Node*);
   
    size_t _depth(Node*) const;
};

template <class T>
Tree<T>::Tree(const Tree<T>& tree){
    root = this->_copy(tree.get_root(), nullptr);
}

template <class T>
void Tree<T>::operator=(const Tree<T>& tree){
    this->_remove(root);
    root = this->_copy(tree.get_root(), nullptr);
}


template <class T>
Tree<T>::~Tree(){
    _remove(root);
}

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

template <class T>
void Tree<T>::remove(Node* n){
    if(n == nullptr)
        throw "Nodo nullo";

    if(n->parent != nullptr){
        List_Node nodo_t = n->parent->childs.find(n);
        n->parent->childs.erase(nodo_t);
        _remove(n);
    }else{
        _remove(n);
        root = nullptr;
    }   
}

template <class T>
void Tree<T>::_remove(Node* n){
    if(n != nullptr){
        if(!n->childs.empty()){
            for(List_Node el = n->childs.begin(); !n->childs.end(el); el = n->childs.next(el)){
                _remove(n->childs.read(el));
                n->childs.erase(el);
            }
        }
        delete n;
    }
}

template <class T>
size_t Tree<T>::depth() const{
    return _depth(root);
}

template <class T>
size_t Tree<T>::_depth(Node* n) const{
    int max = 0;
    for(List_Node el = n->childs.begin(); !n->childs.end(el); el = n->childs.next(el)){
        int new_max = _depth(n->childs.read(el));
        if(new_max > max){
            max = new_max;
        }
    }
    return max+1;
}

template <class T>
size_t Tree<T>::distance(Node* n) const{
    size_t result = 0;
    Node* test = n;
    while(test->parent != nullptr){
        test = test->parent;
        result++;
    }
    return result;
}


template <class T>
void Tree<T>::_print(std::ostream& os, Node* n){
    os << "[";
    os << n->value;
    for(List_Node el = n->childs.begin(); !n->childs.end(el); el = n->childs.next(el)){
        _print(os, n->childs.read(el));
    }
    os << "]";
}


template <class T>
std::ostream& operator<<(std::ostream& os, Tree<T>& tree){
    tree._print(os, tree.root);
    return os;
}


template <class T>
typename Tree<T>::Node* Tree<T>::_copy(Node* n, Node* parent){
    if(n == nullptr)
        return nullptr;

    Node* new_node = new Node(n->value);
    new_node->parent = parent;

    for(List_Node el = n->childs.begin(); !n->childs.end(el); el = n->childs.next(el)){
        new_node->childs.push_back(_copy(n->childs.read(el),n));
    }

    return new_node;
}

template <class T>
typename Tree<T>::Node* Tree<T>::insert_first_subtree(Node* n, Tree<T>& tree){

}

template <class T>
typename Tree<T>::Node* Tree<T>::insert_subtree(Node* n, Tree<T>& tree){
    if(tree.get_root() == nullptr)
        return nullptr;

    Node* new_node = this->_copy(tree.get_root(), n->parent);
    n->parent->childs.insert(new_node, n->parent->childs.find(n));

    return new_node;
}