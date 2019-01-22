#include <iostream>
#include "linked_stack.hpp"
#include <string>

using namespace std;    
float evaluate_postfix(string);
string infix_to_postfix(string expr);

int main(){

    string expr;
    //cin >> expr;
    //cout << evaluate_postfix(expr); 
    cin >> expr;
    cout << infix_to_postfix(expr);

    return 0;
}
float evaluate_postfix(string expr){
    Stack<float> st;
    for(char &token : expr){
        // Number
        if(token >= '0' && token <= '9'){
            st.push(token - '0');
        }
        // Addition
        if(token == '+'){
            float operand_1 = st.read(); st.pop();
            float result = st.read() + operand_1; st.pop();
            st.push(result);
        }
        // Product
        if(token == '*'){
            float operand_1 = st.read(); st.pop();
            float result = st.read() * operand_1; st.pop();
            st.push(result);
        }
        // Division
        if(token == '/'){
            float operand_1 = st.read(); st.pop();
            float result = st.read() / operand_1; st.pop();
            st.push(result);
        }
        // Sottraction
        if(token == '-'){
            float operand_1 = st.read(); st.pop();
            float result = st.read() - operand_1; st.pop();
            st.push(result);
        }

       cout << "[" << token << "]"; st.print(); cout << endl;
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

