/**
 * C++ example to demonstrate the Priority Queue implementation using ordered Linked List
 */
#include <iostream>
using namespace std;

/**
 * Queue Node Representation
 */
 struct Node {
     int element;
     int priority; // Lowest number indicates high priority
     Node* next;
 };

/**
 * Priority Queue implementation using ordered Linked List
 */
class PriorityQueue
{
private:
    // Queue front pointer
    Node* front;
    
public:
    // Constructor
    PriorityQueue() : front(NULL) {}

    // Enqueue new element to Queue
    void enqueue(int element, int priority);

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
void PriorityQueue::enqueue(int element, int priority) {		
    // Step 1: Create the new node with priority
    Node* node = new Node();
    if (node == NULL) {
        cout << "System out of memory" << endl;
        return;
    }
    node->element = element;
    node->priority = priority;
	
    // Step 2: Check if the Queue is empty (or) the new node has higher
    // priority than the Front node.        
    if (front == NULL || priority < front->priority) {
		// Step 3. If true, connect the new node at Front and Exit.

        // Link the new node to point the Front
        node->next = front;
		// Set the Front to point the new node
        front = node;			
		return;
    }

    // Step 4. Iterate the list from Front based on the priority and find the node
    // after which the new node can be linked.
    Node* pos = front;
    while (pos->next != NULL && priority >= pos->next->priority) {
        pos = pos->next;
    }

    // Step 5. Link the new node to point the next of identified node
    node->next = pos->next;		
    // Step 6. Link the identified node to point the new node
    pos->next = node;
}

// Dequeue an element from Queue
int PriorityQueue::dequeue() {
    // Step 1. Check if the Queue is empty
    if (front == NULL) {
        return -1;
    }
    
    // Step 2. Retrieve the element at Front
    int element = front->element;
	
    // Step 3. Remember the front node in a temporary pointer
    Node* tmp = front;
	
    // Step 4. Change the Front to point the next node
    front = front->next;
	
    // Step 5. Delete the node referenced in the temporary pointer
    delete tmp;
    
    return element;
}

// Returns the top element without deleting
int PriorityQueue::peek() {
    if (isEmpty()) {
        return -1;
    }
    return front->element;
}

// Print the Queue
void PriorityQueue::display(string msg) {
    cout << msg << endl;
    if (isEmpty()) {
        return;
    }
    
    cout << front->element << " (" << front->priority << ")" << " <-- front" << endl;
    for (Node* node=front->next; node != NULL; node = node->next) {
        cout << node->element << " (" << node->priority << ")" << endl;
    }
    cout << endl;
}

// Check if the Queue is empty
bool PriorityQueue::isEmpty() {
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
    PriorityQueue queue;
    
    // Push the elements 10 (3), 20 (1), and 30 (2)
    queue.enqueue(10, 3);
    queue.display("Queue after enqueue(10, 3)");
    queue.enqueue(20, 1);
    queue.display("Queue after enqueue(20, 1)");
    queue.enqueue(30, 2);
    queue.display("Queue after enqueue(30, 2)");

    // Get the peek element
    int element = queue.peek();
    cout << "Peek element returned " << element << endl;
    
    // Pop the elements from Queue one by one
    for (int i=0; i < 3; i++) {
        element = queue.dequeue();
        cout << "Dequeue element returned " << element << endl;
        queue.display("Queue after dequeue()");
    }
}
