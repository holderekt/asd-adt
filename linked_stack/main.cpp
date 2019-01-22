#include <iostream>
#include "linked_stack.hpp"

using namespace std;

int main(){

    Stack<int> st;
    Stack<int> sp;

    sp.push(1);
    sp.push(2);
    
    Stack<int> test = sp;
    sp.print();
    test.print();
    sp.push(3);
    test.print();
    sp.print();
    sp.pop();
    sp.pop();
    cout << endl;
    sp.print();





    return 0;
}