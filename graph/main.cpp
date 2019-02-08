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

    auto a0 = grafo.insert_node(0, "ciao");
    auto a1 = grafo.insert_node(1,"mario");
    auto a2 = grafo.insert_node(2,"cass");
    auto a3 = grafo.insert_node(3,"cass");
    auto a4 = grafo.insert_node(4,"cass");
    auto a5 = grafo.insert_node(5,"cass");


    grafo.insert_edge(a0,a1, 1);
    grafo.insert_edge(a0,a2, 2);
    grafo.insert_edge(a1,a3,1);
    grafo.insert_edge(a2,a3,2);
    grafo.insert_edge(a1,a4,3);
    grafo.insert_edge(a3,a4,1);
    grafo.insert_edge(a0,a4,6);
    grafo.insert_edge(a4,a5,1);
    

    cout << grafo;
    std::cout << std::endl;
    
    grafo.findShortestPath(a0, a5);

    return 0;
}