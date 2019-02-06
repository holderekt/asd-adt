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
    friend class Graph<T,W,L>;

    GEdge():empty(true){}

    bool isEmpty() const{ return empty; }
    W getWeight() const{ return weight;}
    GNode<T,W,L>* getFirst() const{return first;}
    GNode<T,W,L>* getSecond() const{return second;}

    void setData(GNode<T,W,L>* first, GNode<T,W,L>* second, W weight){
        this->first = first;
        this->second = second;
        this->weight = weight;
        this->empty = false;
    }

private:
    GNode<T,W,L>* first;
    GNode<T,W,L>* second;
    W weight;
    bool empty;
};

/*
    Edge
*/
template <class T, class W, class L>
class GNode{
public:
    friend class Graph<T,W,L>;
    friend class GEdge<T,W,L>;

    GNode():empty(true){};

    T getValue() const{return value;}
    size_t getId() const{return id;}
    bool isEmpty() const{return empty;}
    L getLabel() const{ return label;}

    void setData(T value,L label, size_t id){
        this->value = value;
        this->label = label;
        this->id = id;
        this->empty = false;
    }

    GEdge<T,W,L>* edges;
    
private:
    T value;
    L label;
    bool empty;
    size_t id;
};

/*
    Graph
*/
template <class T, class W, class L>
class Graph{
public:
    friend class GNode<T,W,L>;
    friend class GEdge<T,W,L>;

    typedef T value_type;
    typedef W weight;
    typedef L label;
    typedef GNode<T,W,L> Node;
    typedef GEdge<T,W,L> Edge; 

    Graph(size_t);
    Node* insert_node(value_type,label);
    void insert_edge(Node*, Node*, weight);

    template <class _T, class _W, class _L>
    friend std::ostream& operator<<(std::ostream&, const Graph<_T,_W,_L>&);

    Node* matrix;
    size_t length;
    size_t size;

private:

};

template <class T, class W, class L>
Graph<T,W,L>::Graph(size_t dimension){
    length = 0;
    size = dimension;
    matrix = new Node[dimension];
    for(int i = 0; i!=dimension; i++){
        matrix[i].edges = new Edge[dimension];
    }
}

template <class T, class W, class L>
typename Graph<T,W,L>::Node* Graph<T,W,L>::insert_node(value_type value, label lab){
    if(matrix != nullptr){

        int i = 0;
        while(!matrix[i].isEmpty()){ i++; }

        matrix[i].setData(value, lab, i);
    
        for(int j = 0; j!= size; j++){
            matrix[i].edges[j].empty = true;
        }

        ++length;
        return &matrix[i];
    }
    return nullptr;
}

/*
TODO REMOVE THIS SHIT   
*/

template <class T, class W, class L>
std::ostream& operator<<(std::ostream& os, const Graph<T,W,L>& gph){
    os << "[\n";
    for(int i =0, count = 0; i != gph.size; i++){
        if(!(gph.matrix[i].isEmpty())){
            os << "("<< gph.matrix[i].getLabel() <<")\t" << gph.matrix[i].getValue() << ":[";

            for(int j = 0; j!= gph.size; j++){
                if(!(gph.matrix[i].edges[j].isEmpty())){
                    os << "(";
                    os << gph.matrix[i].edges[j].getFirst()->getValue();
                    os << " {" << gph.matrix[i].edges[j].getWeight() << "}" << "-> ";
                    os << gph.matrix[i].edges[j].getSecond()->getValue();   
                    os << ")";
                }
            }

            os << "]";
            count ++;

            if(count < gph.length){
                os << ",\n";
                
            }
        }
    }
    os << "\n]";
    return os;
}

template <class T, class W, class L>
void Graph<T,W,L>::insert_edge(Node* n1, Node* n2, weight w){
    if(n1->getId() < length && n2->getId() < length){
        n1->edges[n2->getId()].setData(n1,n2, w);
    }else{
        throw "Index out of bound";
    }

}