/*
Ivan Diliso 
*/

#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "../linear_list.hpp"
#include <iostream>

template <class T>
class Linked_list;

template <class T>
class Node{
    friend class Linked_list<T>;
private:
    T value;
    Node<T>* _next;
    Node<T>* _prev;
};

template <class T>
class Linked_list : public Linear_list<T, Node<T>*>{
public:
    typedef typename Linear_list<T, Node<T>*>::value_type value_type;
    typedef typename Linear_list<T, Node<T>*>::position position;

    //Constructors and destructors
    Linked_list();
    Linked_list(const Linked_list<T>&);
    ~Linked_list();

    //Operators
    void create();
    bool empty() const;
    value_type read(position) const ;
    void write(const value_type &, position);
    position begin() const;
    bool end(position) const;
    position next(position) const;
    position previous(position) const;
    void insert(const value_type &, position p);
    void erase(position);
    int size() const;

    // Other Operators
    void push_back(const value_type&);
    void clear();
    position find(const value_type&) const;

    // Overload Operators
    bool operator==(const Linked_list<T>&) const;
    Linked_list<T>& operator=(const Linked_list<T>&);
    
private:
    Node<T>* _head;
    int _lenght;
};

template <class T>
Linked_list<T>::Linked_list(){
    create(); 
}

template <class T>
Linked_list<T>::~Linked_list(){
    while(!end(begin())){
        erase(begin());
    }
    delete(_head);
}

template <class T>
Linked_list<T>::Linked_list(const Linked_list<T>& lista){
    this->create();
    for(position p = lista.begin(); !(lista.end(p)); p = lista.next(p)){
        this->push_back(lista.read(p));
    }
}

template <class T>
void Linked_list<T>::create(){
    _head = new Node<T>;
    _head->_next = _head;
    _head->_prev = _head;
    _lenght = 0;
}

template <class T>
int Linked_list<T>::size() const{
    return _lenght;
}

template <class T>
bool Linked_list<T>::empty() const{
    return (_lenght == 0);
}

template <class T>
typename Linked_list<T>::value_type Linked_list<T>::read(position pos) const{
    return pos->value;
}

template <class T>
void Linked_list<T>::write(const value_type& value, position pos){
    pos->value = value;
}

template <class T>
typename Linked_list<T>::position Linked_list<T>::begin() const{
    return _head->_next;
}

template <class T>
bool Linked_list<T>::end(position pos) const{
    return (pos == _head);
}

template <class T>
typename Linked_list<T>::position Linked_list<T>::next(position pos) const{
    return pos->_next;
}

template <class T>
typename Linked_list<T>::position Linked_list<T>::previous(position pos) const{
    return pos->_prev;
}

template <class T>
void Linked_list<T>::insert(const value_type& value, position pos){
    
    Node<T>* newn = new Node<T>;

    newn->value = value;
    newn->_next = pos->_next;
    newn->_prev = pos;
    pos->_next = newn;

    ++_lenght;
}

template <class T>
void Linked_list<T>::erase(position pos){

    position prev = pos->_prev;
    position next = pos->_next;
    
    prev->_next = next;
    next->_prev = prev;

    --_lenght;
    delete(pos);
}

template <class T>
void Linked_list<T>::push_back(const value_type& value){

    Node<T>* newn = new Node<T>;
    newn->value = value;
    newn->_prev = _head->_prev;
    newn->_next = _head;

    _head->_prev->_next = newn;
    _head->_prev = newn;

    ++_lenght;
}

template <class T>
void Linked_list<T>::clear(){
    while(!end(begin())){
        erase(begin());
    }
}

template <class T>
typename Linked_list<T>::position Linked_list<T>::find(const value_type& value) const{
    for(position p = begin(); !(end(p)); p = next(p)){
        if(read(p) == value){
            return p;
        }
    }
    return nullptr;
}
/*

Overload Functions

*/

template <class T>
std::ostream& operator<<(std::ostream& os, const Linked_list<T>& lista){
    os << "[";
    for(typename Linked_list<T>::position p = lista.begin(); !(lista.end(p)); p = lista.next(p)){
        os << lista.read(p);
        if(lista.next(p) != lista.previous(lista.begin()))
            os << ",";
    }
    os << "]\n";
    return os
    ;
}

template <class T>
bool Linked_list<T>::operator==(const Linked_list<T>& lista) const{
    if(this->size() == lista.size()){
        position p,q;
        for(p = lista.begin(), q = this->begin(); !(this->end(q)) && !(lista.end(p)); p = lista.next(p), q = this->next(q)){
            if(this->read(q) != lista.read(p)){
                return false;
            }
        }
    }else{
        return false;
    }
    return true;
}

template <class T>
Linked_list<T>& Linked_list<T>::operator=(const Linked_list<T>& lista){
    this->clear();
    for(position p = lista.begin(); !(lista.end(p)); p = lista.next(p)){
        this->push_back(lista.read(p));
    }
    return *this;
}
    

#endif // _LINKED_LIST_H