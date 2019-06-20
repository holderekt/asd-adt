#include <iostream>
#include <string>
#include "tree.hpp"

using namespace std;

void inline newline();

int main(){

    Tree<int> mario;
    mario.insert_root(1);
    TNode<int>* a = mario.get_root();
    mario.insert_child(a,2);
    TNode<int>* rm = mario.insert_child(a,3);
    mario.insert_child(rm, 4);
    mario.insert_child(rm, 5);
    TNode<int>* rm1 = mario.insert_child(rm, 6);
    mario.insert_child(rm, 7);
    mario.insert_child(a,8);

    cout <<  "ESKER " <<  mario << endl;

    Linked_list<TNode<int>*> ma = rm->childs;
    mario.remove(a);

    cout << mario << endl;

    mario.insert_root(6);

    cout << mario << endl;
  
    mario.insert_root(4);
    TNode<int>* c =  mario.get_root();
    mario.insert_child(c, 1);
    TNode<int>* cac = mario.insert_child(c, 2);
    mario.insert_child(c, 3);
    TNode<int>* d = mario.insert_child(c,2);
    TNode<int>* e = mario.insert_child(d,4);

    cout << mario;

    TNode<int>* f = mario._copy(d, nullptr);
    cout << endl;

    cout << "......."<< endl;
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

    cout << "----------" << endl;
    luigi = mario;
    mario.insert_subtree(cac, mario);
    cout << mario;
    newline();
    luigi.insert_first_subtree(cac, mario);
    newline();
    cout << mario;
    newline();
    cout << luigi;

    return 0;
}

void inline newline(){
    std::cout << std::endl;
}