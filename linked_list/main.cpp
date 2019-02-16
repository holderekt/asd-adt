#include <iostream>
#include "linked_list.hpp"
#include "string"
#include <vector>

using namespace std;

int main(){

    Linked_list<int> lista;
    lista.push_back(18);
    lista.push_back(14);
    lista.push_back(15);

    Linked_list<int> lista2;
    lista2.push_back(1);
    lista2.push_back(2);
    lista2.push_back(3);

    cout << lista << lista2;
    cout << (lista2 == lista);
    lista2 = lista;

    cout << lista2;

    LNode<int> *mario = lista.find(14);
    cout << lista.read(mario);

return 0;  
}