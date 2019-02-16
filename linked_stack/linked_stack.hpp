/**
 * @file linked_stack.hpp
 * @author Ivan Diliso
 * Contact: diliso.ivan@gmail.com
 */

#pragma once
#include <iostream>

template <class T>
class Stack;

template <class T>
class SNode{
public:
    friend class Stack<T>;
private:
    typename Stack<T>::value_type _value;
    SNode<T>* _prev;
};

template <class T>
class Stack{
public:
    typedef T value_type;

    // Constructors and destructors
    Stack();
    Stack(const Stack<T>&);
    ~Stack();

    // Operators
    void create();
    bool empty() const;
    value_type read() const;
    void pop();
    void push(value_type);
    size_t lenght(){ return _lenght; }

    template <class Z>
    friend std::ostream& operator<<(std::ostream&, Stack<T>&);
    void print(std::ostream&) const;
    void operator=(const Stack<T>&);


private:
    SNode<T>* _head;
    int _lenght;

    void _copy(const Stack<T>&);
    void _clear();
};

template <class T>
Stack<T>::Stack(){
    create();
}

template <class T>
Stack<T>::Stack(const Stack<T>& stk){
    create();
    _copy(stk);
}

template <class T>
void Stack<T>::_copy(const Stack<T>& stk){
    this->_head = new SNode<T>;
    this->_head->_value = stk._head->_value;
    this->_lenght = stk._lenght;
    
    SNode<T>* prev_node = _head;

    SNode<T>* cp_node = stk._head->_prev;

    while(cp_node != nullptr){
        SNode<T>* new_node = new SNode<T>;

        new_node->_value = cp_node->_value;
        new_node->_prev = nullptr;
        cp_node = cp_node->_prev;
        

        prev_node->_prev = new_node;
        prev_node = new_node;
    }

}

template <class T>
void Stack<T>::operator=(const Stack<T>& stk){
    _clear();
    _copy(stk);
}

template <class T>
void Stack<T>::_clear(){
    while(!empty()){
        pop();
    }
}

template <class T>
Stack<T>::~Stack(){
    _clear();
}

template <class T>
void Stack<T>::create(){
    _head = nullptr;
}

template <class T>
bool Stack<T>::empty() const{
    return (_head == nullptr);
}

template <class T>
typename Stack<T>::value_type Stack<T>::read() const{
    return _head->_value;
}

template <class T>
void Stack<T>::pop(){
    if(!empty()){
        SNode<T>* old_head = _head;
        _head = _head->_prev;
        delete old_head;
    }
}

template <class T>
void Stack<T>::push(value_type value){
    SNode<T>* new_head = new SNode<T>;
    new_head->_value = value;
    new_head->_prev = _head;
    _head = new_head;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Stack<T>& stk){
    os << "[";
    stk.print(os);
    os << "]";
    return os;
}

template <class T>
void Stack<T>::print(std::ostream& os) const{
    SNode<T>* temp = _head;
    while(temp != nullptr){
        os << temp->_value;
        if(temp->_prev != nullptr){
            os <<",";
        }
        temp = temp->_prev;
    }
}