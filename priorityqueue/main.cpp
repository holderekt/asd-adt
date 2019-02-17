#include <iostream>
#include "priority_queue.hpp"
#include <time.h>
#include <pthread.h>
#include <unistd.h>

unsigned int sleep(unsigned int seconds);

using namespace std;

int main(){

    Priority_Queue<int,int> que;
 
  

    que.insert(1,1);
    que.insert(2,2);
    que.insert(3,3);
    que.insert(4,4);
    que.insert(5,5);
    que.insert(6,6);

    cout << que << endl;
    
    que.remove();
    cout << que << endl;
    que.remove();
    cout << que << endl;

    que.remove();
    cout << que << endl;

    que.remove();
    cout << que << endl;

    que.remove();
    cout << que << endl;

    que.remove();

    que.insert(5,8);
    cout << que << endl;
  
    return 0;
}