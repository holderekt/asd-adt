#include <iostream>
#include <string>
#include "tree.hpp"

using namespace std;

int main(){

    Tree<int> mario;
    mario.insert_root(1);
    auto a = mario.get_root();
    mario.insert_child(a,4);
    mario.insert_child(a,3);
    cout << a->childs;

    return 0;
}