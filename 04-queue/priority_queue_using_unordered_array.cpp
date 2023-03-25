/**
 * C++ example to demonstrate Priority Queue implementation using unordered Array
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
 * Priorty Queue implementation using unordered Array
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

    // Returns the high priority element without deleting it
    Element peek();

    // Print the Queue
    void display(string msg);

    // Check if the Queue is empty
    bool isEmpty();

    // Check if the Queue is full
    bool isFull();

    // Search the high priority element from Queue
    int getHighPriorityPos();
};

// Enqueue new element to the Queue
void PriorityQueue::enqueue(Element element) {
    // Step 1. Return if the Queue is full, proceed otherwise
    if (isFull()) {
        return;
    }
    
    // Step 2. Move the Rear to next position
    rear++;
    
    // Step 3. Insert the new element at Rear
    queue[rear] = element;
}

// Dequeue the element from Queue
Element PriorityQueue::dequeue() {
    // Step 1. Return if the Queue is empty, proceed otherwise
    if (isEmpty()) {
        throw runtime_error("Queue is Empty");
    }
        
    // Step 2. Find and Retrieve the next high priority element
    int pos = getHighPriorityPos();
    Element element = queue[pos];

    // Step 3. Replace the high priority element with the Rear element
    // (or) Shift elements if you want to preserve the original order
    queue[pos] = queue[rear];
    
    // Step 4. Move Rear to previous position
    rear--;
    
    return element;
}

// Returns the high priority element without deleting it
Element PriorityQueue::peek() {
    if (isEmpty()) {
        throw runtime_error("Queue is Empty");
    }
    int pos = getHighPriorityPos();
    return queue[pos];
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

// Search the high priority element from Queue
int PriorityQueue::getHighPriorityPos() {
    if (isEmpty()) {
        return -1;
    }
    
    int pos = 0;
    int highPriority = queue[pos].priority;
    for (int i=1; i <= rear; i++) {
        if (highPriority > queue[i].priority) {
            pos = i;
            highPriority = queue[i].priority;
        }
    }
    return pos;
}

// The main function to begin the execution
int main()
{
    // Create a Queue
    PriorityQueue queue;
    
    // Enqueue elements (10, 20, and 30)
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
