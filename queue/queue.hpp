#pragma once

#include <iostream>

template <class T>
class Queue;

template <class T>
class QNode{
public:
    friend class Queue<T>;
    typename Queue<T>::value_type _value;
    QNode<T>* _prev;
};

template <class T>
class Queue{
public:
    typedef T value_type;

    // Constructors and destructors
    Queue();
    Queue(const Queue<T>&);
    ~Queue();

    // Operators
    void create();
    bool empty() const;
    value_type read() const;
    void pop();
    void push(value_type);

    // Overload Operands
    template <class Z>
    friend std::ostream& operator<<(std::ostream& os, Queue<Z>& que);


private:
    QNode<T>* _head;
    QNode<T>* _tail;
    int _lenght;
};

template <class T>
Queue<T>::Queue(){
    create();
}


// TODO Completare
template <class T>
Queue<T>::Queue(const Queue<T>& que){
    create();

    this->_head = new QNode<T>;
    this->_head->_value = que._head->_value;
    QNode<T>* prev_node = _head;


    QNode<T>* cp_node = que._head->_prev;

    while(cp_node != nullptr){
        QNode<T>* new_node = new QNode<T>;

        new_node->_value = cp_node->_value;
        new_node->_prev = nullptr;
        cp_node = cp_node->_prev;
        

        prev_node->_prev = new_node;
        prev_node = new_node;

        if(cp_node == nullptr){
            _tail = new_node;
        }
    }
}

template <class T>
Queue<T>::~Queue(){
    while(!empty()){
        pop();
    }   
}

template <class T>
void Queue<T>::create(){
    _head = nullptr;
    _tail = nullptr;
    _lenght = 0;
}

template <class T>
bool Queue<T>::empty() const{
    return (_head == nullptr);
}

template <class T>
typename Queue<T>::value_type Queue<T>::read() const{
    return _head->_value;
}

template <class T>
void Queue<T>::pop(){
    if(!empty()){
        QNode<T>* old_head = _head;
        _head = _head->_prev;
        delete old_head;
    }

    --_lenght;
}

template <class T>
void Queue<T>::push(value_type value){
    QNode<T>* new_tail = new QNode<T>;
    new_tail->_value = value;
    new_tail->_prev = nullptr;

    if(_lenght == 0){
        _head = _tail = new_tail;
    }else{
        _tail->_prev = new_tail;
        _tail = new_tail;
    }

    ++_lenght;
}

/*
Overload Operators
*/

template <class T>
std::ostream& operator<<(std::ostream& os, Queue<T>& que){
    os << "[";
    QNode<T>* test = que._head;
    while(test != nullptr){
        os << test->_value;
        test = test->_prev;
        if(test != nullptr) os << ",";
    }
    os << "]";
    return os;
}