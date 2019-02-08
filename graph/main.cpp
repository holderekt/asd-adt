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

    auto a1 = grafo.insert_node(1, "ciao");
    auto a2 = grafo.insert_node(2,"mario");
    auto a3 = grafo.insert_node(3,"cass");
    auto a4 = grafo.insert_node(4,"cass");
    auto a5 = grafo.insert_node(5,"cass");
    auto a6 = grafo.insert_node(6,"cass");
    auto a7 = grafo.insert_node(7,"cass");
    auto a8 = grafo.insert_node(8,"cass");
    auto a9 = grafo.insert_node(9,"cass");

    grafo.insert_edge(a1,a2, 10);
    grafo.insert_edge(a2,a3, 4);
    grafo.insert_edge(a2,a4,1);
    grafo.insert_edge(a1,a5,2);
    grafo.insert_edge(a5,a6,10);
    grafo.insert_edge(a1,a6,2);
    grafo.insert_edge(a6,a7,2);
    grafo.insert_edge(a6,a8,2);
    grafo.insert_edge(a7,a9,2);
    grafo.insert_edge(a8,a1, 1);
    

    auto nodes = grafo.getNodes();

    for(auto a = nodes.begin(); !nodes.end(a); a = nodes.next(a)){
        cout << nodes.read(a)->getValue();
    }
    

    std::cout << std::endl;
    

    cout << "Nodi adiacenti: " << grafo.adjacent(a1);
    std::cout << std::endl;
    cout << grafo;
    std::cout << std::endl;
    cout << "BFS: ";
    grafo.BFS(a1);
    std::cout << std::endl;
    cout << "DFS: ";
    grafo.DFS(a1);

    std::cout << std::endl;
    
    grafo.DFS(a5);

    cout << grafo.existsPath(a1,a9);
    cout << grafo.existsPath(a3,a1);
    cout << grafo.existsPath(a8,a4);

    std::cout << std::endl;
    std::cout << std::endl;
     

    cout << hash(a1);
    std::cout << std::endl;
    
    cout << hash(a2);

    std::cout << std::endl;
    
    int a = 2000 >> 4;
    cout << a;

    std::cout << std::endl;
    
    grafo.findShortestPath(a1, a9);

    return 0;
}