#ifndef _LINKED_STACK_H
#define _LINKED_STACK_H

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

    // Temporary
    void print(){
        SNode<T>* temp = _head;
        while(temp != nullptr){
            std::cout << temp->_value << " ";
            temp = temp->_prev;
        }
    }

private:
    SNode<T>* _head;
    int _lenght;
};

template <class T>
Stack<T>::Stack(){
    create();
}

template <class T>
Stack<T>::Stack(const Stack<T>& stk){
    create();

    this->_head = new SNode<T>;
    this->_head->_value = stk._head->_value;
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
Stack<T>::~Stack(){
    while(!empty()){
        pop();
    }
    
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


#endif // _LINKED_STACK_H