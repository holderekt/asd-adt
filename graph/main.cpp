#include <iostream>
#include <string>
#include "graph.hpp"
#include <ctime>

using namespace std;

int main(){
    srand(time(NULL));
    int i = rand()%40;
    std::cout << i;


    Graph<int,int,std::string> grafo(5);


    

    return 0;
}