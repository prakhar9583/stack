#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <algorithm> // Add this for the reverse function
using namespace std;

// Node structure for the stack
struct Node {
    char data;
    Node* next;
};

class Stack {
    Node* top;
public:
    Stack() : top(nullptr) {}

    void push(char x) {
        Node* newNode = new Node{x, top};
        top = newNode;
    }

    char pop() {
        if (!top) return '\0';
        char x = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return x;
    }

    char peek() {
        return top ? top->data : '\0';
    }

    bool isEmpty() {
        return !top;
    }
};

// Utility functions for expression handling
int precedence(char op) {
    return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Infix to Postfix
string infixToPostfix(const string& infix) {
    Stack s;
    string postfix;
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.isEmpty() && s.peek() != '(') postfix += s.pop();
            s.pop();
        } else if (isOperator(c)) {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(c)) postfix += s.pop();
            s.push(c);
        }
    }
    while (!s.isEmpty()) postfix += s.pop();
    return postfix;
}

// Infix to Prefix
string infixToPrefix(const string& infix) {
    string rev, prefix;
    for (auto it = infix.rbegin(); it != infix.rend(); ++it) {
        char c = *it;
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
        rev += c;
    }
    prefix = infixToPostfix(rev);
    reverse(prefix.begin(), prefix.end());
    return prefix;
}

// Postfix Evaluation
int evaluatePostfix(const string& postfix) {
    stack<int> s;
    for (char c : postfix) {
        if (isdigit(c)) s.push(c - '0');
        else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            if (c == '+') s.push(a + b);
            else if (c == '-') s.push(a - b);
            else if (c == '*') s.push(a * b);
            else if (c == '/') s.push(a / b);
        }
    }
    return s.top();
}

// Prefix Evaluation
int evaluatePrefix(const string& prefix) {
    stack<int> s;
    for (auto it = prefix.rbegin(); it != prefix.rend(); ++it) {
        char c = *it;
        if (isdigit(c)) s.push(c - '0');
        else {
            int a = s.top(); s.pop();
            int b = s.top(); s.pop();
            if (c == '+') s.push(a + b);
            else if (c == '-') s.push(a - b);
            else if (c == '*') s.push(a * b);
            else if (c == '/') s.push(a / b);
        }
    }
    return s.top();
}

int main() {
    string infix = "(3+5)*2";
    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);

    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;
    cout << "Postfix Evaluation: " << evaluatePostfix(postfix) << endl;
    cout << "Prefix Evaluation: " << evaluatePrefix(prefix) << endl;

    return 0;
}
