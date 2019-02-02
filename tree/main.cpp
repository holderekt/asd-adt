#include <iostream>
#include <string>
#include "tree.hpp"

using namespace std;

void inline newline();

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

    mario.remove(a);
  


    mario.insert_root(4);
    auto c =  mario.get_root();
    mario.insert_child(c, 1);
    auto cac = mario.insert_child(c, 2);
    mario.insert_child(c, 3);
    auto d = mario.insert_child(c,2);
    auto e = mario.insert_child(d,4);

    cout << mario;

    auto f = mario._copy(d, nullptr);
    cout << endl;


    Tree<int> luigi(mario);
    mario._print(cout, f);
    cout << endl;
    cout << mario;
    newline();
    mario._print(cout, f);
    newline();
    cout << luigi;
    luigi = mario;
    newline();
    cout << luigi;

    mario.insert_subtree(cac, mario);

    newline();
    cout << mario;

    return 0;
}

void inline newline(){
    std::cout << std::endl;
}