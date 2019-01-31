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

    Binary_Tree<int> tree;
    tree.insert_root(5);
    BTNode<int>* node = tree.get_root();
    
    auto b = tree.insertsx(node,6);
    auto a = tree.insertdx(node,2);
    auto c = tree.insertsx(a, 1);
    auto d = tree.insertdx(a, 3);
    auto e = tree.insertsx(b, 8);
    auto f = tree.insertdx(b,9);
    b = tree.insertsx(f,0);
    a = tree.insertdx(f,7);
    tree.insertdx(a,1);
    tree.insertsx(a, 2);
    auto h = tree.insertdx(b, 6);
    tree.insertdx(h,1);
    tree.insertsx(h,2);
    tree.insertsx(b, 3);
    cout << tree;
    return 0;
}