#include <iostream>
#include <string>
#include "bintree.hpp"

using namespace std;

int main(){

    string mario =  "A";
    if(mario[mario.size() - 1] != ' '){
        cout << "test:" << mario.substr(0, mario.size() - 3) << endl;
    } 
    cout << "-----" << endl;

    Binary_Tree<string> tree;
    tree.insert_root("mario");
    BTNode<string>* node = tree.get_root();
    
    BTNode<string>* b = tree.insertsx(node,"cciao");
    auto a = tree.insertdx(node,"asddaa");
    auto c = tree.insertsx(a, "bgsfdg");
    auto d = tree.insertdx(a, "csgf");
    auto e = tree.insertsx(b, "dsgf");
    auto f = tree.insertdx(b,"esg");
    b = tree.insertsx(f,"fsfg");
    a = tree.insertdx(f,"gjjj");
    tree.insertdx(a,"hasd");
    tree.insertsx(a, "liul");
    auto h = tree.insertdx(b, "mgkj");
    tree.insertdx(h,"ngkjk");
    tree.insertsx(h,"ogkj");
    tree.insertsx(b, "pgk");
    cout << tree;
    delete b;
    cout << tree;
    cout << b->value;


    return 0;
}