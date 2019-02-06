#pragma once

#include <iostream>
#include <string>
#include "graph.hpp"
#include "../hash_table/hash_table.hpp"
#include "../linked_list/linked_list.hpp"
#include "../priorityqueue/priority_queue.hpp"

template<class T, class W, class L>
class Graph;

template <class T, class W, class L>
class GNode;

/*
    Node
*/
template <class T, class W, class L>
class GEdge{
public:
    friend class GNode<T,W,L>;

private:
    GNode<T,W,L>* first;
    GNode<T,W,L>* second;
    W weight;
};

/*
    Edge
*/
template <class T, class W, class L>
class GNode{
public:
    friend class Graph<T,W,L>;
    friend class GEdge<T,W,L>;
    GNode():length(0){};
    GNode(T value,L label):value(value),label(label),length(0){};


    // TODO REMOVE THIS SHIT
    void print(){
        std::cout << "[";
        for(int i = 0; i!=length; i++){
            std::cout << edges[i]->first->value << " -> " << edges->second->value;
            if(i!=length){
                std::cout << ",";
            }
        }
        std::cout << "]";
    }


private:
    T value;
    L label;
    GEdge<T,W,L>* edges;
    size_t length;
};

/*
    Graph
*/
template <class T, class W, class L>
class Graph{
public:
    typedef T value_type;
    typedef W weight;
    typedef L label;
    typedef GNode<T,W,L> Node;
    typedef GEdge<T,W,L> Edge; 

    Graph(size_t);
    Node* insert(value_type);

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
