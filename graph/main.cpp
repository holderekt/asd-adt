#include <iostream>
#include <string>
#include "graph.hpp"
#include <ctime>

using namespace std;

int main(){

    /*
    */

    Graph<int,int,std::string> grafo(5);

    auto a = grafo.insert_node(3, "ciao");
    auto b = grafo.insert_node(4,"mario");
    auto g = grafo.insert_node(5,"cass");
    grafo.insert_edge(a,b, 10);
    grafo.insert_edge(b,g, 4);
    

    cout << grafo.adjacent(a);
    std::cout << std::endl;
    cout << grafo;

    grafo.DFS(a);


    

    return 0;
}