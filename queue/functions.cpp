#include <iostream>
#include "queue.hpp"
#include "../linked_stack/linked_stack.hpp"
#include <string>
#include <sstream>

using namespace std;

void transfer(Stack<char>& stk, Queue<string>& que);
string infix_to_postfix(string expr);
int priority(char operand);

int main(){

    string expr;
    cin >> expr;
    cout << infix_to_postfix(expr);
    
    return 0;
}

string infix_to_postfix(string expr){
    Stack<char> pila;
    Queue<string> coda;
    string output = "";
    string number = "";

    for(char token : expr){
        if(token >= '0' and token <='9'){
            number += token;
        }else if(pila.empty() or token == '('){
            pila.push(token);
        }else if(token == ')'){
            while(pila.read() != '('){
                transfer(pila, coda);
            }
            pila.pop();
        }else{
            while(!pila.empty() && (priority(token) <= priority(pila.read()))){
                transfer(pila,coda);
            }
            pila.push(token);
        }

        if(token >= '9' or token <= '0'){
            coda.push(number);
            number = "";
        } 
    }

    if(number != "") coda.push(number);

    while(!pila.empty()) transfer(pila, coda);
    while(!coda.empty()){
        output += coda.read() + " ";
        coda.pop();  
    }  

    return output;
}


void transfer(Stack<char>& stk, Queue<string>& que){
    stringstream ss;
    string a;
    ss << stk.read();
    ss >> a;
    que.push(a);
    stk.pop();
}

int priority(char operand){
    switch(operand){
        case '+':
            return 1;
        case '-':
            return 1;
        case '/':
            return 2;
        case '*':
            return 2;
        case '(':
            return 0;
    }

    return -1;
}