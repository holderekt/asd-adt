#include <iostream>
#include <string>
#include "graph.hpp"
#include <ctime>

using namespace std;

int main(){

    /*
    */


    Graph<int,int,std::string> grafo(10);
    Hash<GNode<int,int,std::string>*> hash;

        
    typename Graph<int,int,string>::Node* a1 = grafo.insert_node(1,"mario");
    typename Graph<int,int,string>::Node* a2 = grafo.insert_node(2,"cass");
    // typename Graph<int,int,string>::Node* a3 = grafo.insert_node(3,"cass");
    // typename Graph<int,int,string>::Node* a4 = grafo.insert_node(4,"cass");
    // typename Graph<int,int,string>::Node* a5 = grafo.insert_node(5,"cass");
    // typename Graph<int,int,string>::Node* a6 = grafo.insert_node(6,"caa");
    // typename Graph<int,int,string>::Node* a7 = grafo.insert_node(7,"caa");

    grafo.insert_edge(a1,a2,1);
    // grafo.insert_edge(a1,a3,2);
    // grafo.insert_edge(a2,a4,4);
    // grafo.insert_edge(a3,a4,2);
    // grafo.insert_edge(a3,a6,5);
    // grafo.insert_edge(a4,a7,1);
    // grafo.insert_edge(a6,a7,1);
    // grafo.insert_edge(a1,a2,1);
    // grafo.insert_edge(a7,a5,1);
    // grafo.insert_edge(a4,a5,10);


    cout << grafo;
    std::cout << std::endl;
    
    Linked_list<typename Graph<int,int,string>::Node*> a = grafo.findShortestPath(a1, a2);

    std::cout << "Maior FIne" << std::endl;

    std::cout << a << endl; 
    

    return 0;
}