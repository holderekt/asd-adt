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
    tree.insert_root(0);
    BTNode<int>* node = tree.get_root();

    
    BTNode<int>* b = tree.insertsx(node,1);
    auto a = tree.insertdx(node,2);
    auto c = tree.insertsx(a, 3);
    auto d = tree.insertdx(a, 4);
    auto e = tree.insertsx(b, 5);
    auto f = tree.insertdx(b,6);
    b = tree.insertsx(f,7);
    a = tree.insertdx(f,8);
    tree.insertdx(a,9);
    tree.insertsx(a, 10);
    auto h = tree.insertdx(b, 11);
    tree.insertdx(h,12);
    tree.insertsx(h,13);
    tree.insertsx(b, 14);
    cout << tree;
    cout << tree;
    cout << b->value;

    cout << endl;
    cout << "-----------" << endl;
    Binary_Tree<int> tree2(tree);
    tree.remove(b);
    cout << tree;
    cout << endl;
    cout << "-----------" << endl;
    cout << tree2;
    tree2 = tree;
     cout << "-----------" << endl;
    cout << tree2;
    cout << "ddd" << tree.size() << tree2.size();
    tree.preOrder();



    return 0;
}