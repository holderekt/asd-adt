#include <iostream>
#include "priority_queue.hpp"

using namespace std;

int main(){

    Priority_Queue<int> que;
    int value;

    // while(value != 0){
    //     cin >> value;
    //     cout << " --- " << endl;
    //     que.insert(value);
    //     que.print();
    //     cout << endl;
    // }

    que.insert(1);
    que.insert(2);
    que.insert(3);

    que.print();
    que.remove();
    que.print();
    return 0;
}