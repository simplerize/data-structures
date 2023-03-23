/**
 * C++ example to demonstrate Circular Queue implementation using Linked List
 */
#include <iostream>
using namespace std;

/**
 * Queue Node Representation
 */
 struct Node {
     int element;
     Node* next;
 };

/**
 * Circular Queue implementation using Linked List
 */
class CircularQueue
{
private:
    // Queue front pointer
    Node* front;
    
    // Queue rear pointer
    Node* rear;
    
public:
    // Constructor
    CircularQueue() : front(NULL), rear(NULL) {}
    
    // Enqueue new element to Queue
    void enqueue(int element);
    
    // Dequeue an element from Queue
    int dequeue();

    // Returns the top element without deleting
    int peek();
    
    // Print the Queue
    void display(string msg);
    
    // Check if the Queue is empty
    bool isEmpty();
};

// Enqueue new element to Queue
void CircularQueue::enqueue(int element) {		
    // Step 1. Create the new node
    Node* node = new Node();
    if (node == NULL) {
        cout << "System out of memory" << endl;
        return;
    }
    node->element = element;
	
    // Step 2. Connect the new node at Rear side
    if (rear == NULL) {
        // Step 2.A. If the Queue is empty, set the Front to point the new node.
        front = node;
    } else {
        // Step 2.B. Otherwise connect the new node after the Rear.
        rear->next = node;
    }
    
    // Step 3. Connect the new node to Front and form the circle
    node->next = front;
    
    // Step 4. Change the rear to point the new node
    rear = node;
}

// Dequeue an element from Queue
int CircularQueue::dequeue() {
    // Check if the Queue is empty
    if (front == NULL) {
        return -1;
    }
    
    // Step 1. Retrieve the element at Front
    int element = front->element;
	
    // Step 2. Remember the front node in a temporary pointer
    Node* tmp = front;
	
    // Step 3. Disconnect the front node
    if (front->next == NULL) {
        // Step 3.A. If the next node is not available, set Front and Rear to point the NULL
        front = rear = NULL;
    } else {
        // Step 3.B. Otherwise, change the Front to point the next node
        // and link the Rear to point the new Front node to form circle.
        front = front->next;
        rear->next = front;
    }
    
    // Step 4: Delete the node stored in temporary pointer
    delete tmp;
    
    return element;
}

// Returns the top element without deleting
int CircularQueue::peek() {
    if (isEmpty()) {
        return -1;
    }
    return front->element;
}

// Print the Queue
void CircularQueue::display(string msg) {
    cout << msg << endl;
    if (isEmpty()) {
        return;
    }
    
    if (front == rear) {
        cout << front->element << " <-- front, rear" << endl;
        
    } else {
        cout << front->element << " <-- front" << endl;
        for (Node* node=front->next; node != rear; node = node->next) {
            cout << node->element << endl;
        }
        cout << rear->element << " <-- rear";
    }
    
    if (rear->next == front) {
        cout << " (linked to front)" << endl;
    }
}

// Check if the Queue is empty
bool CircularQueue::isEmpty() {
    if (front == NULL) {
        cout << "Queue is Empty" << endl;
        return true;
    }
    return false;
}

// The main function to begin the execution
int main()
{
    // Create a Queue
    CircularQueue queue;
    
    // Push the elements (10, 20, 30, 40 and 50)
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);
    queue.display("Queue after inserting 10 20 30 40 and 50");
    
    // Get the peek element
    int element = queue.peek();
    cout << "Peek element returned " << element << endl;
    
    // Pop the elements from Queue
    element = queue.dequeue();
    cout << "Dequeue element returned " << element << endl;
    element = queue.dequeue();
    cout << "Dequeue element returned " << element << endl;
    queue.display("Queue after removing two elements");
}
