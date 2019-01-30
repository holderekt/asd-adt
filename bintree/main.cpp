#include <iostream>
#include <string>
#include "bintree.hpp"

using namespace std;

int main(){

    Binary_Tree<int> tree;
    tree.insert_root(5);
    BTNode<int>* node = tree.get_root();
    
    

    auto a = tree.insertsx(node,1);
    for(int i =0; i<10; i++){
        a = tree.insertsx(a,i);
    }
    auto b = tree.insertdx(node,2);
    

    cout << tree;

    return 0;
}