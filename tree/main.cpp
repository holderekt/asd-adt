#include <iostream>
#include <string>
#include "tree.hpp"

using namespace std;

int main(){

    Tree<int> mario;
    mario.insert_root(1);
    auto a = mario.get_root();
    mario.insert_child(a,4);
    auto rm = mario.insert_child(a,3);
    mario.insert_child(rm, 1);
    mario.insert_child(rm, 2);
    mario.insert_child(rm, 3);
    mario.insert_child(rm, 4);
    mario.insert_child(a,5);

    cout << rm->childs;
    mario.remove(a);
    cout << rm->childs;
    cout << a->childs;


    mario.insert_root(4);
    auto c =  mario.get_root();
    mario.insert_child(c, 1);
    auto d = mario.insert_child(c,2);
    cout << c->value;
    cout << c->childs;

    mario.remove(d);

    cout << c->childs;

    return 0;
}