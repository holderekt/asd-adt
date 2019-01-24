#pragma once

#include <iostream>
#include <string>


using namespace std;

template <class T>
class Hash{
public:
    size_t operator()(const T) const;
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
    //~Hash_Table();

    // Operators
    void create();
    bool empty() const;
    size_t size() const;
    DPair<K,E>* find(const key&) const;
    size_t search(const key&) const;
    bool insert(const DPair<K,E>&);
    void erase(const key&);
    void modify(const key&, const value&);

    // Overload operands
    template<class KK, class EE>
    friend std::ostream& operator<<(std::ostream&, Hash_Table<KK,EE>&);
    DPair<K,E>& operator[](const key&);


private:
    DPair<K,E> **table;
    Hash<K> fhash;
    size_t dsize;
    size_t divisor;
};

template<class K, class E>
std::ostream& operator<<(std::ostream& os, Hash_Table<K,E>& ht){
    os << "[";
   for(int i = 0; i!= ht.divisor; i++){
       if(ht.table[i] != nullptr){
           if(i != 0) os << ",";
            os << "{" << ht.table[i]->key << " : " << ht.table[i]->value << "}";    
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
DPair<K,E>& Hash_Table<K,E>::operator[](const key& key){
    size_t pos = search(key);

    if(table[pos] == nullptr || table[pos]->key != key){
        throw "Not found";
    }else{
        return *table[pos];
    }
}


