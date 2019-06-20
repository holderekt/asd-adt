/**
 * @file hash_table.hpp
 * @author Ivan Diliso
 * Contact: diliso.ivan@gmail.com
 */

#pragma once

#include <iostream>
#include <string>

#define nullptr 0

using namespace std;

template <class T>
class Hash{
public:
    size_t operator()(const T value) const{
        return size_t(value);
    }
};

struct KeyNotFoundError : public std::exception{
    const char * message() const throw(){
        return "Key Not Found";
    }
};

template<>
class Hash<std::string>{
public:
    size_t operator()(const std::string key) const{
        unsigned long hash_value = 0;
        for(int i=0; i!=key.length();  i++){
            char el = key[i];
            hash_value = hash_value*5 + el;
        }
        return size_t(hash_value);
    }
};

template<class K, class E>
struct DPair{
    K key;
    E value;

    DPair(){};
    DPair(K key,E value): key(key), value(value){};

    inline void operator=(E value){
        this->value = value;
    }

    inline void operator=(DPair<K,E>& pair){
        key = pair.key;
        value = pair.value;
    }

    friend std::ostream& operator<<(std::ostream& os, const DPair<K,E>& pair){
        os << "{" << pair.key << " : " << pair.value << "}";
        return os;
    }
};

template<class K, class E>
class Hash_Table{
public:

    typedef K key;
    typedef E value;

    // Constructor and destructors 
    Hash_Table(size_t);
    Hash_Table(const Hash_Table<K,E>&);
    ~Hash_Table();

    // Operators
    void create(size_t);
    bool empty() const;
    bool insert(const DPair<K,E>&);
    bool insert(K,E);
    void erase(const key&);
    void resize();
    size_t divisor() const { return this->_divisor; }
    size_t size() const{ return this->_size; }

    // Overload operands
    template<class KK, class EE>
    friend std::ostream& operator<<(std::ostream&, Hash_Table<KK,EE>&);
    E operator[](const key&) const;
    E& operator[](const key&);
    void operator=(const Hash_Table<K,E>&);

    
private:
    
    Hash<K> fhash;
    size_t _size;
    size_t _divisor;
    DPair<K,E> **table;

    size_t _search(const key&) const;
    void _clear();
    void _copy(const Hash_Table<K,E>&);
};



template<class K, class E>
Hash_Table<K,E>::Hash_Table(size_t divisor){
    create(divisor);
}

template<class K,class E>
Hash_Table<K,E>::Hash_Table(const Hash_Table<K,E>& ht){
    create(ht.divisor());
    this->_size = ht.size();
    _copy(ht);
}

template<class K, class E>
void Hash_Table<K,E>::create(size_t divisor){
    this->_divisor = divisor;
    this->_size = 0;
    this->table = new DPair<K,E>*[divisor];

    for(int i=0; i!=_divisor; i++){
        this->table[i] = nullptr;
    }
}

template <class K, class E>
void Hash_Table<K,E>::_copy(const Hash_Table<K,E>& ht){
    for(int i=0; i!=_divisor; i++){
        if(ht.table[i] != nullptr){
            this->table[i] = new DPair<K,E>(ht.table[i]->key, ht.table[i]->value);            
        }else{
            this->table[i] = nullptr;
        }
    }
}

template <class K, class E>
void Hash_Table<K,E>::_clear(){
    for(int i = 0; i!=_divisor; i++){
    if(table[i] != nullptr){
            delete table[i];
        }
    }
    delete [] table;
}

template <class K, class E>
Hash_Table<K,E>::~Hash_Table(){
    _clear();
}

template<class K, class E>
std::ostream& operator<<(std::ostream& os, Hash_Table<K,E>& ht){
    os << "[";
    bool flag = false;
    for(int i = 0, count = 0; i!= ht._divisor; i++){
        if(ht.table[i] != nullptr){
            os << "{" << ht.table[i]->key << " : " << ht.table[i]->value << "}"; 
            count++;   
            if(count != ht._size) os << ",";
        }
    }
    os << "]";
    return os;
}


template<class K, class E>
size_t Hash_Table<K,E>::_search(const key& key) const{
    size_t i = (size_t) fhash(key) % _divisor;
    size_t j = i;
    do{
        if(table[j] == nullptr || table[j]->key == key){
            return j;
        }else{
            j = (j+1) % _divisor;
        }
    }while(j!=i);

    return j; 
}

template<class K, class E>
bool Hash_Table<K,E>::insert(K key, E element){
    DPair<K,E> pair(key, element);
    return insert(pair);
}

template<class K, class E>
bool Hash_Table<K,E>::insert(const DPair<K,E>& pair){
    size_t pos = _search(pair.key);

    if(table[pos] == nullptr){
        table[pos] = new DPair<K,E>(pair);
        ++_size;
    }else{
        if(table[pos]->key == pair.key){
            table[pos]->value = pair.value;
        }else{
            return false;
        }
    }
    return true;
}


template <class K, class E>
E& Hash_Table<K,E>::operator[](const key& key){
    size_t pos = _search(key);

    if(table[pos] == nullptr || table[pos]->key != key){
        throw KeyNotFoundError();
        
    }else{
        return table[pos]->value;
    }
}


template <class K, class E>
E Hash_Table<K,E>::operator[](const key& key) const{
    size_t pos = _search(key);

    if(table[pos] == nullptr || table[pos]->key != key){
        throw KeyNotFoundError();
        
    }else{
        return table[pos]->value;
    }
}

template <class K, class E>
void Hash_Table<K,E>::erase(const key& key){
    size_t pos = _search(key);

    if(table[pos] == nullptr || table[pos]->key != key){
        throw KeyNotFoundError();
        
    }else{
        DPair<K,E> *pair = table[pos];
        table[pos] = nullptr;
        delete(pair);
        --_size;
    }
}

template <class K,class E>
void Hash_Table<K,E>::operator=(const Hash_Table<K,E>& ht){
    _clear();
    create(ht.divisor());
    this->_size = ht.size();
    _copy(ht);
}
