#pragma once

#include <iostream>
#define nullptr 0

template <class T>
class Set{
public:
    typedef T value_type;


    //Constructors and destructors
    Set();
    Set(const Set<T>&);
    ~Set();

    // Operations
    void create();
    int size() const;
    int lenght() const;
    bool empty() const;
    void realloc(int);
    bool find(value_type&) const;
    bool insert(const value_type&);
    void erase(value_type&);
    Set<T>& union_(const Set<T>&) const;
    Set<T>& intersection(const Set<T>&) const;
    Set<T>& difference(const Set<T>&) const;
    
    // Overload operands
    template <class Z>
    friend std::ostream& operator<<(std::ostream&, const Set<Z>&);

private:
    value_type* _elements;
    int _lenght;
    int _size;
};

template <class T>
void Set<T>::create(){
    _elements  = new value_type[2];
    _lenght = 0;
    _size = 2;
}

template <class T>
Set<T>::Set(){
    create();
}

template <class T>
Set<T>::Set(const Set<T>& cset){
    this->_lenght = cset->lenght();
    this->_size = cset->size();
    this->_elements = new value_type[cset->size()];
    for(int i = 0; i< cset->lenght(); i++){
        this->_elements[i] = cset->_elements[i];
    }
}

template <class T>
Set<T>::~Set(){

}

template <class T>
void Set<T>::realloc(int new_size){
    value_type* temp = new value_type[new_size];
    _size = new_size;

    for(int i = 0; i!=_lenght; i++){
        temp[i] = _elements[i];
    }
    delete [] _elements,
    _elements = temp;
}

template <class T>
int Set<T>::size() const{
    return _size;
}

template <class T>
int Set<T>::lenght() const{
    return _lenght;
}

template <class T>
bool Set<T>::empty() const{
    return (size() == 0);
}

template <class T>
bool Set<T>::insert(const value_type& value){
    for(int i = 0; i!= _lenght; i++){
        if(value == _elements[i]){
            return 0;
        }
    }
    if(_lenght == (_size -1)){
        realloc(_size*2);
    }

    _elements[_lenght] = value;
    _lenght++;
    return 1;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Set<T>& st){
    os << "[";
    for(int i=0; i!=st._lenght; i++){
        os << st._elements[i];
        if(i != st._lenght - 1){
            os << ",";
        }
    }
    os << "]";
    return os;
}