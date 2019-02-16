#include <iostream>
#include "linked_stack.hpp"
#include <string>

using namespace std;    
float evaluate_postfix(string);
string infix_to_postfix(string);
void quicksort(int*,int);
void swap(int &, int &);

int main(){

    // string expr;
    // cin >> expr;
    // cout << evaluate_postfix(expr); 
    // cin >> expr;
    // cout << infix_to_postfix(expr);

    // int a[] = {10,9,8,7,6,5,4,3,2,1};
    // quicksort(a,10);

    // for(int i = 0; i<10; i++){
    //     cout << a[i] << " ";
    // }

    Stack<int> an;
    Stack<int> bn;
    bn.push(1);
    bn.push(2);
    an.push(5);
    an.push(6);
    an.push(7);
    an.push(8);

    cout << an.read() << endl;

    cout << bn << endl;
    cout << an << endl;

    bn = an;

    cout << bn << endl;

    bn.pop();
    bn.pop();
    bn.pop();
    bn.pop();

    cout << bn << endl;

    bn = an;

    
    cout << bn << endl;


    return 0;
}

float evaluate_postfix(string expr){
    Stack<float> st;
    for(char &token : expr){
        // Number
        if(token >= '0' && token <= '9'){
            st.push(token - '0');
        }else{
            float operand_1 = st.read(); st.pop();
            float result;

            switch(token){
                case '+':
                    result = st.read() + operand_1;
                    break;
                case '-':
                    result = st.read() - operand_1;
                    break;
                case '/':
                    result = st.read() / operand_1;
                    break;
                case '*':
                    result = st.read() * operand_1;
                    break;
            }
            st.pop();
            st.push(result);
        }
       cout << "[" << token << "]" << st << endl;
    }
    return st.read();
}

string infix_to_postfix(string expr){
    Stack<char> st;
    string output = "";
    for(char token : expr){
        // Operand
        if(token >= '0' && token <= '9'){
            output += token;
        }
        // Operation
        if(token == '+' or token == '-' or token == '/' or token == '*'){
            st.push(token);
        }
        // Close operation
        if(token == ')'){
            output += st.read();
            st.pop();
        }
    }
    return output;    
}

void quicksort(int* a, int n){
    int left, right, i, j, pivot, var;
    Stack<int> pila;
    pila.push(0); pila.push(n-1);

    while(!pila.empty()){
        j = right = pila.read(); pila.pop();
        i = left = pila.read(); pila.pop();
        pivot = a[(i+j)/2];

        while(i<=j){
            while(a[i] < pivot) i++;
            while(pivot < a[j]) j--;
            
            if(i<=j){
                if(i != j) swap(a[i],a[j]);
                i++; j--;
            }
        }

        if(left < j){
            pila.push(left);
            pila.push(j);
        }
        if(i < right){
            pila.push(i);
            pila.push(right);
        }
    }
}


void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}