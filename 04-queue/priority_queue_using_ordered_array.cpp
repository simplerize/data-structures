/**
 * C++ example to demonstrate Priority Queue implementation using ordered Array
 */
#include <iostream>
using namespace std;

// Queue maximum capacity
#define CAPACITY 8

/**
 * Priority Queue Element
 */
struct Element
{
    int value;
    int priority;
    
    Element() : value(-1), priority(-1) {}
    Element(int v, int p) : value(v), priority(p) {}
};

/**
 * Priorty Queue implementation using Array
 */
class PriorityQueue
{
private:
    // Queue
    Element queue[CAPACITY];
    
    // Rear position
    int rear;
    
public:
    // Constructor
    PriorityQueue() : rear(-1) {}
    
    // Enqueue new element to the Queue
    void enqueue(Element element);
    
    // Dequeue the element from Queue
    Element dequeue();
    
    // Returns the Front element without deleting it
    Element peek();
    
    // Print the Queue
    void display(string msg);
    
    // Check if the Queue is empty
    bool isEmpty();
    
    // Check if the Queue is full
    bool isFull();
};
    
// Enqueue new element to the Queue
void PriorityQueue::enqueue(Element element) {
    // Step 1. Return if the Queue is full, proceed otherwise
    if (isFull()) {
        return;
    }
    
    // Step 2. Check if the Queue is empty
    if (isEmpty()) {
        // Step 3. If the Queue is empty, insert at position 0
        queue[0] = element;
    } else {
        // Step 4. Otherwise if the Queue is not empty, insert on its sorted position by shifting the other elements.
        // The high priority element is aligned at the Rear side to ease the deletion.
        int pos = rear;
        for (; element.priority >= queue[pos].priority && pos >= 0; pos--) {
            queue[pos+1] = queue[pos]; // Shift element
        }
        queue[pos+1] = element; // Insert the new element
    }
        
    // Step 5. Increment the Rear by one position
    rear++;
}

// Dequeue the element from Queue
Element PriorityQueue::dequeue() {
    // Step 1. Return if the Queue is empty, proceed otherwise
    if (isEmpty()) {
        throw runtime_error("Queue is Empty");
    }
    
    // Step 2. Retrieve the element at Rear
    Element element = queue[rear];

    // Step 3. Move Rear to the previous position
    rear--;
    
    return element;
}

// Returns the Front element without deleting it
Element PriorityQueue::peek() {
    if (isEmpty()) {
        throw runtime_error("Queue is Empty");
    }
    return queue[rear];
}

// Print the Queue
void PriorityQueue::display(string msg) {
    cout << msg << endl;
    if (isEmpty()) {
        return;
    }
    
    for (int i=0; i < rear; i++) {
        cout << queue[i].value << " (" << queue[i].priority << ")" << endl;
    }
    cout << queue[rear].value << " (" << queue[rear].priority << ") <-- rear" << endl;
}

// Check if the Queue is empty
bool PriorityQueue::isEmpty() {
    if (rear == -1) {
        return true;
    }
    return false;
}

// Check if the Queue is full
bool PriorityQueue::isFull() {
    if (rear == (CAPACITY-1)) {
        return true;
    }
    return false;
}

// The main function to begin the execution
int main()
{
    // Create a Queue
    PriorityQueue queue;
    
    // Enqueue elements (10, 20, 30, 40, and 50)
    queue.enqueue(Element(10, 3));
    queue.enqueue(Element(20, 1));
    queue.enqueue(Element(30, 2));
    queue.display("Queue after inserting 10 (3), 20 (1), and 30 (2)");
    
    // Get the peek element
    Element element = queue.peek();
    cout << "Peek element returned " << element.value << endl;
    
    // Dequeue the elements from Queue
    element = queue.dequeue();
    cout << "Dequeue element returned " << element.value << endl;
    element = queue.dequeue();
    cout << "Dequeue element returned " << element.value << endl;
    queue.display("Queue after removing two elements");
}
