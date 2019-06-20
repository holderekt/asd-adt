#include <iostream>
#include <string>
#include "bintree.hpp"

using namespace std;

int main(){

    // string mario =  "A";
    // if(mario[mario.size() - 1] != ' '){
    //     cout << "test:" << mario.substr(0, mario.size() - 3) << endl;
    // } 
    // cout << "-----" << endl;

    Binary_Tree<int> tree;
    tree.insert_root(0);
    BTNode<int>* node = tree.get_root();
    BTNode<int>* b = tree.insertsx(node,1);
    BTNode<int>* a = tree.insertdx(node,2);
    BTNode<int>* c = tree.insertsx(a, 3);
    BTNode<int>* d = tree.insertdx(a, 4);
    BTNode<int>* e = tree.insertsx(b, 5);
    BTNode<int>* f = tree.insertdx(b,6);

    cout << tree << endl;

    tree.remove(a);
    
    cout << tree << endl;

    tree.remove(node);

    cout << tree << endl;

    BTNode<int>* roo = tree.insert_root(9);

    cout << tree << endl;

    b = tree.insertsx(roo,7);
    a = tree.insertdx(roo,8);


    
    tree.insertdx(a,9);
    tree.insertsx(a, 10);

    cout << tree << endl;
    tree.preOrder();
    cout << endl;
    tree.postOrder();
    cout << endl;
    tree.inOrder();

    return 0;
}