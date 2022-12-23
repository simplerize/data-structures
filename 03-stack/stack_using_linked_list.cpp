/**
 * C++ example to demonstrate Stack implementation using Linked List
 */
#include <iostream>
using namespace std;

/**
 * Stack Node Representation
 */
 struct Node {
     int element;
     Node* next;
 };

/**
 * Stack implementation using Linked List
 */
class Stack
{
private:
    // Stack
    Node* top;
    
public:
    // Constructor
    Stack() : top(NULL) {}
    
    // Check if the Stack is empty
    bool isEmpty();
        
    // Returns the top element without deleting
    int peek();
    
    // Push the new element to Stack
    void push(int element);
    
    // Pop the element from Stack
    int pop();
    
    // Print the Stack
    void print(string msg);
};

bool Stack::isEmpty() {
    if (top == NULL) {
        cout << "Stack is Empty" << endl;
        return true;
    }
    return false;
}

int Stack::peek() {
    if (isEmpty()) {
        throw std::runtime_error("stack underflow");
    }
    return top->element;
}

void Stack::push(int element) {		
    // Step 1. Create the new node
    Node* node = new Node();
    if (node == NULL) {
        cout << "System out of memory" << endl;
        throw std::runtime_error("system out of memory");
    }
    node->element = element;
	
    // Step 2. Link the top node after this new node
    node->next = top;
	
    // Step 3. Change the Top to point the new node
    top = node;
}

int Stack::pop() {
    // Step 1. Return if the Stack is empty, proceed otherwise
    if (isEmpty()) {
        throw std::runtime_error("stack underflow");
    }
    
    // Step 2. Retrieve the element on the Top
    int element = top->element;
	
    // Step 3. Remember the Top node in a temporary pointer
    Node* tmp = top;
	
    // Step 4. Change the Top to point the next Node
    top = top->next;
	
    // Step 5. Delete the node stored in temporary pointer
    delete tmp;
    
    return element;
}

void Stack::print(string msg) {
    cout << msg << endl;
    if (isEmpty()) {
        return;
    }
    
    cout << top->element << " <-- top" << endl;
    for (Node* node=top->next; node != NULL; node = node->next) {
        cout << node->element << endl;
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
        int element = stack.pop(); // 50
        cout << "Pop element returned " << element << endl;
        element = stack.pop(); // 40
        cout << "Pop element returned " << element << endl;
        stack.print("Stack after poping two elements");
        
        // Now try poping elements until we get stack underflow
        stack.pop(); // 30
        stack.pop(); // 20
        stack.pop(); // 10
        stack.pop(); // expecting exception "stack underflow"
    } catch (const std::exception& e) {
        cout << "Pop: exception received: " << e.what() << endl;
    }
}