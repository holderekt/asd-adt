#pragma once

#include <iostream>
#include <string>
#include <climits>
#include "graph.hpp"
#include "../hash_table/hash_table.hpp"
#include "../queue/queue.hpp"
#include "../linked_stack/linked_stack.hpp"
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

    void setWeight(W weight){ this->weight = weight;}
    void setEmpty(bool value){ this->empty = value;}

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
    
    void setLabel(L label){this->label = label;}
    void setWeight(W weight){this->weight = weight;}
    void setValue(T value){this->value = value;}
    void setEmpty(bool value){this->empty = value;}

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


template<>
class Hash<GNode<int,int,std::string>*>{
public:
    size_t operator()(GNode<int,int,std::string>* key) const{
        return size_t(key) << 5;
    }
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

    Node* insert_node(value_type,label);
    void insert_edge(Node*, Node*, weight);
    void remove_node(Node*);
    void remove_edge(Node*, Node*);

    bool existsEdge(Node*, Node*) const;
    Linked_list<Node*> adjacent(Node*) const;

    bool existsPath(Node*, Node*) const;
    Linked_list<Node*> findShortestPath(Node*, Node*) const;
    Linked_list<Node*> getNodes() const { return this->nodes; };

    Linked_list<Node*> BFS(Node*) const;
    Linked_list<Node*> DFS(Node*) const;


    template <class _T, class _W, class _L>
    friend std::ostream& operator<<(std::ostream&, const Graph<_T,_W,_L>&);



private:
    Node* matrix;
    size_t length;
    size_t size;
    Linked_list<Node*> nodes;

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
        nodes.push_back(&matrix[i]);
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

template <class T, class W, class L>
void Graph<T,W,L>::remove_node(Node* n){
    if(n == nullptr){
        throw "Nodo nullo";
    }else if( n->getId() <0 || n->getId() >= size){
        throw "Index out of bound";
    }else if(n->isEmpty()){
        throw "Node not found";
    }

    for(int i=0; i!=size; i++){
        if(i != n->getId()){
            if(!matrix[i].edges[n->getId()].isEmpty()){
                matrix[i].edges[n->getId()].empty = true;                
            }
        }
    }

    nodes.erase(nodes.find(n));
    matrix[n->getId()].empty = true;
    length--;
}

template <class T, class W, class L>
void Graph<T,W,L>::remove_edge(Node* n1, Node* n2){
    if(n1 == nullptr && n2 != nullptr){
        throw "Nodo nullo";
    }else if(n1->getId() <0 || n1->getId() >= size || n2->getId() <0 || n2->getId() >= size){
        throw "Index out of bound";
    }else if(n1->isEmpty() || n2->isEmpty()){
        throw "Node not found";
    }
    
    if(existsEdge(n1,n2)){
        matrix[n1->getId()].edges[n2->getId()].empty = true;
    }else{
        throw "Edge not found";
    }
}

template <class T, class W, class L>
bool Graph<T,W,L>::existsEdge(Node* n1, Node* n2) const{
    return !n1->edges[n2->getId].isEmpty();
}

template <class T, class W, class L>
Linked_list<typename Graph<T,W,L>::Node*> Graph<T,W,L>::adjacent(Node* n) const{
    if(n == nullptr){
        throw "Null node";
    }
    Linked_list<Node*> list;
    for(int i = 0; i!=size; i++){
        if(!n->edges[i].isEmpty()){
            list.push_back(n->edges[i].second);
        }
    }

    return list;
}

template <class T, class W, class L>
Linked_list<typename Graph<T,W,L>::Node*> Graph<T,W,L>::BFS(Node* n) const{
    Linked_list<Node*> visited;
    Queue<Node*> que;

    visited.push_back(n);
    que.push(n);

    while(!que.empty()){
        Node* temp = que.read();
        que.pop();

        Linked_list<Node*> adj = this->adjacent(temp);
        LNode<Node*>* i = adj.begin();

        while(!adj.end(i)){
            if(visited.find(adj.read(i)) == nullptr){
                visited.push_back(adj.read(i));
                que.push(adj.read(i));
            }

            i = adj.next(i);
        }
    }

    return visited;
}

template <class T, class W, class L>
Linked_list<typename Graph<T,W,L>::Node*> Graph<T,W,L>::DFS(Node* n) const{
    Linked_list<Node*> visited;
    Stack<Node*> stk;

    visited.push_back(n);
    stk.push(n);

    while(!stk.empty()){
        Node* temp = stk.read();
        

        Linked_list<Node*> adj = this->adjacent(temp);
        LNode<Node*>* i = adj.begin();
        bool found = false;

        while(!adj.end(i) && !found){
            if(visited.find(adj.read(i)) == nullptr){
                found = true;
                visited.push_back(adj.read(i));
                stk.push(adj.read(i));
            }

            i = adj.next(i);
        }

        if(found == false){
            stk.pop();
        }
    }

    return visited;
}

template <class T, class W, class L>
bool Graph<T,W,L>::existsPath(Node* start, Node* end) const{
    Linked_list<Node*> dfsresult = DFS(start);
    return (dfsresult.find(end) != nullptr);
}

template <class T, class W, class L>
Linked_list<typename Graph<T,W,L>::Node*> Graph<T,W,L>::findShortestPath(Node* start, Node* end) const{
    if(!existsPath(start, end))
        throw "Help";
    
    Hash_Table<Node*, size_t> elements(length);
    Linked_list<Node*> nodes = getNodes();

    for(auto i = nodes.begin(); !nodes.end(i); i = nodes.next(i)){
        elements.insert({nodes.read(i), INT_MAX});
    }
    
    
    
    
}