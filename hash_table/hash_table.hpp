#pragma once

#include <iostream>
#include <string>


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
        for(char el : key){
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
    void create();
    bool empty() const;
    size_t size() const;
    bool insert(const DPair<K,E>&);
    bool insert(K,E);
    void erase(const key&);
    void resize();
    size_t getDivisor() const {return this->divisor; }

    // Overload operands
    template<class KK, class EE>
    friend std::ostream& operator<<(std::ostream&, Hash_Table<KK,EE>&);
    value operator[](const key&) const;
    value& operator[](const key&); 

    DPair<K,E> **table;
private:
    
    Hash<K> fhash;
    size_t dsize;
    size_t divisor;

    size_t search(const key&) const;
};


template<class K,class E>
Hash_Table<K,E>::Hash_Table(const Hash_Table<K,E>& ht){
    this->divisor = ht.divisor;
    this->table = new DPair<K,E>*[divisor];
    this->dsize = ht.dsize;

    for(int i=0; i!=divisor; i++){
        if(ht.table[i] != nullptr){
            this->table[i] = new DPair<K,E>(ht.table[i]->key, ht.table[i]->value);            
        }else{
            this->table[i] = nullptr;
        }
    }
}

template <class K, class E>
Hash_Table<K,E>::~Hash_Table(){
    for(int i = 0; i!=divisor; i++){
        if(table[i] != nullptr){
            delete table[i];
        }
    }
    delete [] table;
}

template<class K, class E>
std::ostream& operator<<(std::ostream& os, Hash_Table<K,E>& ht){
    os << "[";
    bool flag = false;
    for(int i = 0, count = 0; i!= ht.divisor; i++){
        if(ht.table[i] != nullptr){
            os << "{" << ht.table[i]->key << " : " << ht.table[i]->value << "}"; 
            count++;   
            if(count != ht.dsize) os << ",";
        }
    }
    os << "]";
    return os;
}

template<class K,class E>
size_t Hash_Table<K,E>::size() const{
    return this->dsize;
}

template<class K, class E>
Hash_Table<K,E>::Hash_Table(size_t divisor){
    this->divisor = divisor;
    this->dsize = 0;
    this->table = new DPair<K,E>*[divisor];

    for(int i=0; i!=divisor; i++){
        this->table[i] = nullptr;
    }
}

template<class K, class E>
size_t Hash_Table<K,E>::search(const key& key) const{
    size_t i = (size_t) fhash(key) % divisor;
    size_t j = i;
    do{
        if(table[j] == nullptr || table[j]->key == key){
            return j;
        }else{
            j = (j+1) % divisor;
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
    size_t pos = search(pair.key);

    if(table[pos] == nullptr){
        table[pos] = new DPair<K,E>(pair);
        ++dsize;
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
typename Hash_Table<K,E>::value& Hash_Table<K,E>::operator[](const key& key){
    size_t pos = search(key);

    if(table[pos] == nullptr || table[pos]->key != key){
        throw KeyNotFoundError();
        
    }else{
        return table[pos]->value;
    }
}

template <class K, class E>
typename Hash_Table<K,E>::value Hash_Table<K,E>::operator[](const key& key) const{
    size_t pos = search(key);

    if(table[pos] == nullptr || table[pos]->key != key){
        throw KeyNotFoundError();
        
    }else{
        return table[pos]->value;
    }
}

template <class K, class E>
void Hash_Table<K,E>::erase(const key& key){
    size_t pos = search(key);

    if(table[pos] == nullptr || table[pos]->key != key){
        throw KeyNotFoundError();
        
    }else{
        DPair<K,E> *pair = table[pos];
        table[pos] = nullptr;
        delete(pair);
        --dsize;
    }
}
