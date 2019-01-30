#include <iostream>
#include <string>
#include "bintree.hpp"

using namespace std;

int main(){

    Binary_Tree<int> tree;
    tree.insert_root(5);
    BTNode<int>* node = tree.get_root();
    
    
    BTNode<int>* nn;
    auto a = tree.insertsx(node,1);
    for(int i =0; i<10; i++){
        if(i == 4){
        nn = tree.insertsx(a,i);
        a = nn;
        }else{
        a = tree.insertsx(a,i);

        }
    }
    auto b = tree.insertdx(node,2);
    tree.remove(b);
    tree.remove(node);
    tree.insert_root(5);


    cout << tree;

    return 0;
}