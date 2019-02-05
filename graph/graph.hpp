#pragma once

#include <iostream>
#include <string>
#include "grap.hpp"
#include "../hash_table/hash_table.hpp"
#include "../linked_list/linked_list.hpp"
#include "../priorityqueue/priority_queue.hpp"

template<class T>
class Graph;

template <class T, class W>
class Edge(){
public:

private:
    T* first;
    T* second;
    W weight;
}

template <class T, class W, class L>
class GNode(){
public:
    friend class Graph<T>;


private:
    T value;
    L label;
    Linked_List<Edge<T,W>*> edges;
}