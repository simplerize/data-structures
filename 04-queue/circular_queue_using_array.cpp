/**
 * C++ example to demonstrate Circular Queue implementation using Array
 */
#include <iostream>
using namespace std;

// Queue maximum capacity
#define CAPACITY 8

/**
 * Circular Queue implementation using Array
 */
class CircularQueue
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
    CircularQueue() : front(-1), rear(-1) {}
    
    // Enqueue new element to the Queue
    void enqueue(int element);
    
    // Dequeue the element from Queue
    int dequeue();
    
    // Returns the Front element without deleting it
    int peek();
    
    // Print the Queue
    void display(string msg);
    
    // Check if the Queue is empty
    bool isEmpty();
    
    // Check if the Queue is full
    bool isFull();
};

// Enqueue new element to the Queue
void CircularQueue::enqueue(int element) {
    // Step 1. Return if the Queue is full, proceed otherwise
    if (isFull()) {
        return;
    }
    
    // Step 2. Move the Rear position
    if (front == -1) {
        // Step 2.A If Queue is empty, set Front and Rear to point the first position.
        front = rear = 0;
    } else if (rear == (CAPACITY-1)) {
        // Step 2.B If Rear reached the last position, move Rear to first position
        rear = 0;
    } else {
        // Step 2.C Otherwise increment the Rear to next position.
        rear++;
    }
    
    // Step 3. Insert the new element at Rear
    queue[rear] = element;
}

// Dequeue the element from Queue
int CircularQueue::dequeue() {
    // Step 1. Return if the Queue is empty, proceed otherwise
    if (isEmpty()) {
        return -1;
    }
    
    // Step 2. Retrieve the element at Front
    int element = queue[front];

    // Step 3. Move the Front position
    if (front == rear) {
        // Step 3.A If this is the last element, reset Front and Rear to -1.
        front = -1;
        rear = -1;
    } else if (front == (CAPACITY-1)) {
        // Step 3.B If Front reached the last position, move Front to first position
        front = 0;
    } else {
        // Step 3.C Otherwise increment the Front to next position
        front++;
    }
    
    return element;
}

// Returns the Front element without deleting it
int CircularQueue::peek() {
    if (isEmpty()) {
        return -1;
    }
    return queue[front];
}

// Check if the Queue is empty
bool CircularQueue::isEmpty() {
    if (front == -1) {
        cout << "Queue is Empty" << endl;
        return true;
    }
    return false;
}

// Check if the Queue is full
bool CircularQueue::isFull() {
    if ((front == 0 && rear == (CAPACITY-1)) ||
        (front == (rear+1))) {
        cout << "Queue is Full" << endl;
        return true;
    }
    return false;
}

// Print the Queue
void CircularQueue::display(string msg) {
    cout << msg << endl;
    if (isEmpty()) {
        return;
    }
    
    cout << "IDX ELEMENT" << endl;
    cout << "---+-------" << endl;
    for (int i=0; i < CAPACITY; i++) {
        if (front <= rear) {
            if (! (i >= front && i <= rear) ) {
                cout << "[" << i << "] " << endl;
                continue;
            }
        } else if (front > rear) {
            if (! (i >= front || i <= rear) ) {
                cout << "[" << i << "] " << endl;
                continue;
            }
        }
        
        if (i == front && front == rear) {
            cout << "[" << i << "] " << queue[i] << " <-- front, rear" << endl;
        } else if (i == front) {
            cout << "[" << i << "] " << queue[i] << " <-- front" << endl;
        } else if (i == rear) {
            cout << "[" << i << "] " << queue[i] << " <-- rear" << endl;
        } else {
            cout << "[" << i << "] " << queue[i] << endl;
        }
    }
}

// The main function to begin the execution
int main()
{
    // Create a Queue
    CircularQueue queue;
    
    // Enqueue elements (10, 20, 30, 40, and 50)
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);
    queue.display("Queue after inserting 10 20 30 40 and 50");
    
    // Get the peek element
    int element = queue.peek();
    cout << "Peek element returned " << element << endl;
    
    // Dequeue the elements from Queue
    element = queue.dequeue();
    cout << "Dequeue element returned " << element << endl;
    element = queue.dequeue();
    cout << "Dequeue element returned " << element << endl;
    queue.display("Queue after removing 10 and 20");
    
    // Enqueue elements (60, 70, 80, and 90) to check circular behavior
    queue.enqueue(60);
    queue.enqueue(70);
    queue.enqueue(80);
    queue.enqueue(90);
    queue.display("Queue after inserting 60, 70, 80, and 90");
}