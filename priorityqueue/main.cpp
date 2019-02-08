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

    que.print();
    
    que.remove();
    que.remove();
    que.remove();
    que.remove();
    que.remove();
    que.remove();
    
    std::cout << std::endl;
    

    que.print();


    return 0;
}