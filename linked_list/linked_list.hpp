/**
 * @file linked_list.hpp
 * @author Ivan Diliso
 * Contact: diliso.ivan@gmail.com
 */

#pragma once

#include "../linear_list.hpp"
#include <iostream>
#define nullptr 0

template <class T>
class Linked_list;

template <class T>
class LNode{
    friend class Linked_list<T>;
private:
    T value;
    LNode<T>* _next;
    LNode<T>* _prev;
};

template <class T>
class Linked_list : public Linear_list<T, LNode<T>*>{
public:
    typedef typename Linear_list<T, LNode<T>*>::value_type value_type;
    typedef typename Linear_list<T, LNode<T>*>::position position;

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
    void push_back(const value_type&);
    void push_front(const value_type&);
    void clear();
    position find(const value_type&) const;

    // Overload Operators
    bool operator==(const Linked_list<T>&) const;
    Linked_list<T>& operator=(const Linked_list<T>&);

    template <class Z>
    friend std::ostream& operator<<(std::ostream&, const Linked_list<Z>&);
    
private:
    LNode<T>* _head;
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
    _head = new LNode<T>;
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
    
    LNode<T>* newn = new LNode<T>;

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

    LNode<T>* newn = new LNode<T>;
    newn->value = value;
    newn->_prev = _head->_prev;
    newn->_next = _head;

    _head->_prev->_next = newn;
    _head->_prev = newn;

    ++_lenght;
}

template <class T>
void Linked_list<T>::push_front(const value_type& value){

    LNode<T>* newn = new LNode<T>;
    newn->value = value;
    newn->_prev = _head;
    newn->_next = _head->_next;

    _head->_next->_prev = newn;
    _head->_next = newn;

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
Overload Operators
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
    return os;
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
