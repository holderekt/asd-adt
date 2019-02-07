#include <iostream>
#include <string>
#include "graph.hpp"
#include <ctime>

using namespace std;

int main(){



    Graph<int,int,std::string> grafo(5);

    auto a = grafo.insert_node(3, "ciao");
    auto b = grafo.insert_node(4,"mario");
    auto g = grafo.insert_node(5,"cass");
    grafo.insert_edge(a,b, 10);
    grafo.insert_edge(a,g, 4);
    grafo.insert_edge(b,a, 10);
    grafo.remove_edge(a,b);
    grafo.remove_edge(b,a);
  
    cout << grafo;


    

    return 0;
}