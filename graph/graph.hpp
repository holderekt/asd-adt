#pragma once

#include <iostream>
#include <string>
#include "graph.hpp"
#include "../hash_table/hash_table.hpp"
#include "../linked_list/linked_list.hpp"
#include "../priorityqueue/priority_queue.hpp"

template<class T, class W, class L>
class Graph;


template <class T, class W>
class GEdge{
public:

private:
    T* first;
    T* second;
    W weight;
};

template <class T, class W, class L>
class GNode{
public:
    friend class Graph<T,W,L>;
    GNode(){};
    GNode(T value,L label):value(value),label(label){};

private:
    T value;
    L label;
    GEdge<GNode<T,W,L>* ,W>* edges;
};


template <class T, class W, class L>
class Graph{
public:
    typedef T value_type;
    typedef W weight;
    typedef L label;
    typedef GNode<T,W,L> Node;
    typedef GEdge<Node*,W> Edge; 

    Graph(size_t);

private:
    Node* matrix;
    size_t lenght;
    size_t size;
};

template <class T, class W, class L>
Graph<T,W,L>::Graph(size_t dimension){
    lenght = 0;
    size = dimension;
    matrix = new Node[dimension];
    for(int i = 0; i!=dimension; i++){
        matrix[i].edges = new Edge[dimension];
    }
}

