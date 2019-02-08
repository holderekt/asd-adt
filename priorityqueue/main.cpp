#include <iostream>
#include "priority_queue.hpp"

using namespace std;

int main(){

    Priority_Queue<int,int> que;
    int value;
    int priority;
    cin >> value;
    cin >> priority;
    while(value != 0){
        cout << " --- " << endl;
        que.insert(value, priority);
        que.print();
        cout << endl;
        cin >> value;
        cin >> priority;
    }
    
    que.remove();
    que.print();

    return 0;
}