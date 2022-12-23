/**
 * C++ example to demonstrate the Stack implementation using Array
 */
#include <iostream>
#include <string>
using namespace std;

// Stack maximum capacity
#define CAPACITY 5

/**
 * Stack implementation using Array
 */
class Stack
{
private:
    // Stack data
    int stack[CAPACITY];
    
    // Index of top element
    int top;
    
public:
    // Constructor
    Stack() : top(-1) {}
    
    // Return true if the Stack is empty, false otherwise.
    bool isEmpty();
    
    // Returns true if the Stack is full, false otherwise.
    bool isFull();
    
    // Returns the top element without deleting
    int peek();
    
    // Push the new element to Stack
    // Throws runtime_error if the stack is full
    void push(int element);
    
    // Pop the element from Stack
    // Throws runtime_error if the stack is empty
    int pop();
    
    // Print the Stack
    void print(string msg);
};
    
bool Stack::isEmpty() {
    if (top == -1) {
        cout << "Stack is Empty" << endl;
        return true;
    }
    return false;
}

bool Stack::isFull() {
    if (top == (CAPACITY-1)) {
        cout << "Stack is Full" << endl;
        return true;
    }
    return false;
}

int Stack::peek() {
    if (isEmpty()) {
        throw std::runtime_error("stack underflow");
    }
    return stack[top];
}

void Stack::push(int element) {
    // Step 1. Return if the Stack is full, proceed otherwise
    if (isFull()) {
        throw std::runtime_error("stack overflow");
    }
	
    // Step 2. Move the Top to next position
    top++;
	
    // Step 3. Insert the new element on Top
    stack[top] = element;
}

int Stack::pop() {
    // Step 1. Return if the Stack is empty, proceed otherwise
    if (isEmpty()) {
        throw std::runtime_error("stack underflow");
    }
	
    // Step 2. Retrieve the element on Top
    int element = stack[top];
	
    // Step 3. Move Top to one position down
    top--;
	
    return element;
}

void Stack::print(string msg) {
    cout << msg << endl;
    if (isEmpty()) {
        return;
    }
    
    cout << stack[top] << " <-- top" << endl;
    for (int i=top-1; i >= 0; i--) {
        cout << stack[i] << endl;
    }
}

// The main function to begin the execution
int main()
{
    // Create a Stack
    Stack stack;
    
    // Push the elements (10, 20, 30, 40 and 50)
    try {
        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.push(40);
        stack.print("Stack after inserting 10 20 30 and 40");
        stack.push(50);
        stack.print("Stack after pushing 50");
        stack.push(60); // Expecting exception "stack overflow"
    } catch (const std::exception& e) {
        cout << "Push: exception received: " << e.what() << endl;
    }
    
    // Get the peek element
    try {
        int element = stack.peek();
        cout << "Peek element returned " << element << endl;
    } catch (const std::exception& e) {
        cout << "Peek: exception received: " << e.what() << endl;
    }
    
    // Pop the elements from Stack
    try {
        int element = stack.pop();
        cout << "Pop element returned " << element << endl;
        element = stack.pop();
        cout << "Pop element returned " << element << endl;
        stack.print("Stack after poping two elements");
    } catch (const std::exception& e) {
        cout << "Pop: exception received: " << e.what() << endl;
    }
}