/**
 * C++ example to demonstrate Deque implementation using Circular Array
 */
#include <iostream>
using namespace std;

// Queue maximum capacity
#define CAPACITY 8

/**
 * Deque implementation using Circular Array
 */
class Deque
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
    Deque() : front(-1), rear(-1) {}

    // Insert the new element at Front side
    void insertFront(int element);

    // Insert the new element at Rear side
    void insertRear(int element);

    // Delete the element from Front side
    int deleteFront();

    // Delete the element from Rear side
    int deleteRear();

    // Print the Queue
    void display(string msg);

    // Check if the Queue is empty
    bool isEmpty();

    // Check if the Queue is full
    bool isFull();
};

// Insert the new element at Front side
void Deque::insertFront(int element) {
    // Step 1. Check if the Queue is full, and return if true.
    if (isFull()) {
        return;
    }
    
    // Step 2. Move the Front by one position backward based on
    // the below conditions
    if (isEmpty()) {
        // If the Front is -1 (queue is empty), initialize the
        // Front and Rear to point the first index
        front = rear = 0;
    } else if (front == 0) {
        // If the Front is 0, move Front to the last index
        front = (CAPACITY-1);
    } else {
        // Otherwise decrement the Front by one position.
        front--;
    }
    
    // Step 3. Insert the new element at Front
    queue[front] = element;
}

// Insert the new element at Rear side
void Deque::insertRear(int element) {
    // Step 1. Check if the Queue is full, and return if true.
    if (isFull()) {
        return;
    }
    
    // Step 2. Move the Rear one position forward based on
    // the below conditions
    if (front == -1) {
        // If the Front is -1 (queue is empty), initialize the
        // Front and Rear to point the first index.
        front = rear = 0;
    } else if (rear == (CAPACITY-1)) {
        // If the Rear is at the last index, move Rear to first index
        rear = 0;
    } else {
        // Otherwise increment the Rear by one position.
        rear++;
    }
    
    // Step 3. Insert the new element at Rear
    queue[rear] = element;
}

// Delete the element from Front side
int Deque::deleteFront() {
    // Step 1. Check if the Queue is empty, and return if true.
    if (isEmpty()) {
        return -1;
    }
    
    // Step 2. Retrieve the element at Front
    int element = queue[front];

    // Step 3. Move the Front by one position forward based on
    // the below conditions
    if (front == rear) {
        // If Front and Rear are at the same index, reset 
        // Front and Rear to -1
        front = -1;
        rear = -1;
    } else if (front == (CAPACITY-1)) {
        // If Front is at the last index, move Front to first index
        front = 0;
    } else {
        // Otherwise increment the Front by one position
        front++;
    }
    
    return element;
}

// Delete the element from Rear side
int Deque::deleteRear() {
    // Step 1. Check if the Queue is empty, and return if true.
    if (isEmpty()) {
        return -1;
    }
    
    // Step 2. Retrieve the element at Rear
    int element = queue[rear];

    // Step 3. Move the Rear by one position backward based on
    // the below conditions
    if (front == rear) {
        // If Front and Rear are at the same index, reset 
        // Front and Rear to -1
        front = -1;
        rear = -1;
    } else if (rear == 0) {
        // If Rear is at index 0, move Rear to last index
        rear = (CAPACITY-1);
    } else {
        // Otherwise decrement the Rear by one position
        rear--;
    }
    
    return element;
}

// Print the Queue
void Deque::display(string msg) {
    cout << msg << endl;
    if (isEmpty()) {
        return;
    }
    
    cout << "INDEX | ELEMENT" << endl;
    cout << "------+--------" << endl;
    int i=front;
    while (true) {
        // Just frame the Front & Rear pointers to print
        string ptrs = "";
        if (i == front && front == rear) {
            ptrs = " <-- front, rear";
        } else if (i == front) {
            ptrs = " <-- front";
        } else if (i == rear) {
            ptrs = " <-- rear";
        }
        
        // Print the element
        cout << "  [" << i << "] | " << queue[i] << ptrs << endl;
        
        // Navigate to next position
        if (i == rear) {
            break;
        } else if (i == (CAPACITY-1)) {
            i = 0;
        } else {
            i++;
        }
    }
    
    cout << endl;
}

// Check if the Queue is empty
bool Deque::isEmpty() {
    if (front == -1) {
        return true;
    }
    return false;
}

// Check if the Queue is full
bool Deque::isFull() {
    if ((front == 0 && rear == (CAPACITY-1)) ||
        (front == (rear+1))) {
        return true;
    }
    return false;
}

// The main function to begin the execution
int main()
{
    // Create a Deque
    Deque queue;
    
    // Insert Front
    queue.insertFront(5);
    queue.insertFront(3);
    queue.insertFront(1);
    queue.display("Queue after inserting 5, 3, and 1 at the Front side");
    
    // Insert Rear
    queue.insertRear(10);
    queue.insertRear(20);
    queue.insertRear(30);
    queue.display("Queue after inserting 10, 20, and 30 at the Rear side");
    
    // Delete Front
    int element = queue.deleteFront();
    queue.display("Queue after deleting an element at Front");

    // Delete Rear    
    element = queue.deleteRear();
    queue.display("Queue after deleting an element at Rear");
}
