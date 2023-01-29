/**
 * C++ example to demonstrate Queue implementation using Array
 */
#include <iostream>
using namespace std;

// Queue maximum capacity
#define CAPACITY 10

/**
 * Linear Queue implementation using Array
 */
class Queue
{
private:
    // Queue
    int queue[CAPACITY];
    
    // Front position
    int front;
    
    // Rear position
    int rear;
    
public:
    // Constructor
    Queue() : front(-1), rear(-1) {}
    
    // Enqueue new element to the Queue
    void enqueue(int element);
    
    // Dequeue the element from Queue
    int dequeue();
    
    // Returns the Front element without deleting it
    int peek();

    // Check if the Queue is empty
    bool isEmpty();
    
    // Check if the Queue is full
    bool isFull();
    
    // Traverse and display the Queue
    void display(string msg);
};

// Enqueue new element to the Queue
void Queue::enqueue(int element) {
    // Step 1. Return if the Queue is full, proceed otherwise
    if (isFull()) {
        return;
    }
    
    // Step 2. If the Queue is empty, set the Front and Rear to point the first position.
	// Otherwise move the Rear to point the next position.
    if (front == -1) {
        front = rear = 0;
    } else {
        rear++;
    }
    
    // Step 3. Insert the new element at Rear
    queue[rear] = element;
}

// Dequeue the element from Queue
int Queue::dequeue() {
    // Step 1. Return if the Queue is empty, proceed otherwise
    if (isEmpty()) {
        return -1;
    }
    
    // Step 2. Retrieve the element at Front
    int element = queue[front];

    // Step 3. If this is the last element, reset Front and Rear to -1.
	// Otherwise move Front to next position
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front++;
    }
    
    return element;
}

// Returns the Front element without deleting it
int Queue::peek() {
    if (isEmpty()) {
        return -1;
    }
    return queue[front];
}

// Traverse and display the queue
void Queue::display(string msg) {
    cout << msg << endl;
    if (isEmpty()) {
        return;
    }
    
    if (front == rear) {
        cout << queue[front] << " <-- front, rear" << endl;
        return;
    }
    
    cout << queue[front] << " <-- front" << endl;
    for (int i=front+1; i < rear; i++) {
        cout << queue[i] << endl;
    }
    cout << queue[rear] << " <-- rear" << endl;
}

// Check if the Queue is full
bool Queue::isFull() {
    if (rear == (CAPACITY-1)) {
        cout << "Queue is Full" << endl;
        return true;
    }
    return false;
}

// Check if the Queue is empty
bool Queue::isEmpty() {
    if (front == -1) {
        cout << "Queue is Empty" << endl;
        return true;
    }
    return false;
}

// The main function to begin the execution
int main()
{
    // Create a Queue
    Queue queue;
    
    // Enqueue elements (10, 20, 30, 40, and 50)
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.display("Queue after inserting 10 20 30 and 40");
    queue.enqueue(50);
    queue.display("Queue after inserting 50");
    
    // Get the peek element
    int element = queue.peek();
    cout << "Peek element returned " << element << endl;
    
    // Dequeue the elements from Queue
    element = queue.dequeue();
    cout << "Dequeue element returned " << element << endl;
    element = queue.dequeue();
    cout << "Dequeue element returned " << element << endl;
    queue.display("Queue after removing two elements");
}