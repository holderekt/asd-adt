#include <iostream>
#include "priority_queue.hpp"

using namespace std;

int main(){

    Priority_Queue<int> que;
    int value;
    cin >> value;
    while(value != 0){
        cout << " --- " << endl;
        que.insert(value);
        que.print();
        cout << endl;
        cin >> value;
    }
    

que.remove();
que.remove();
que.remove();
que.remove();
que.remove();
que.remove();
que.remove();
   
    que.print();

    return 0;
}