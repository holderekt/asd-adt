#include <iostream>
#include "set.hpp"

using namespace std;

int main(){

    Set<int> mario;
    mario.insert(4);
    mario.insert(5);
    mario.insert(4);
    cout << mario;
    return 0;
}