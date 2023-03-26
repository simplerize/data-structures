/**
 * C++ example to demonstrate the Priority Queue implementation using unordered Linked List
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
 * Priority Queue implementation using unordered Linked List
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
	
    // Step 2: Connect the new node at Front
    
    // Link the new node to point the Front
    node->next = front;
	
	// Set the Front to point the new node
    front = node;
}

// Dequeue an element from Queue
int PriorityQueue::dequeue() {
    // Step 1. Check if the Queue is empty
    if (front == NULL) {
        return -1;
    }
    
    // Step 2. Iterate the list and find the element with highest
    // priority. Store the reference to its previous node required
    // for deletion
    Node* highNode = front;
    Node* prevNode = NULL;
    for (Node *prev = front, *it = front->next; it != NULL; prev = it, it = it->next) {
        if (it->priority <= highNode->priority) {
            highNode = it;
            prevNode = prev;
        }
    }
    
    // Step 3. Retrieve the high priority element
    int element = highNode->element;
    
    // Step 4. Check if the highest priority element is at Front
    if (highNode == front) {
        // Step 5. If true, change the Front and delete the node
        front = highNode->next;
        delete highNode;
        
    } else {
        // Step 6. Else, delink the high priority node by directly
        // connecting its previous and next node and delete it.
        prevNode->next = highNode->next;
        delete highNode;
    }
    
    return element;
}

// Returns the top element without deleting
int PriorityQueue::peek() {
    if (isEmpty()) {
        return -1;
    }
    Node* highNode = front;
    for (Node *it = front->next; it != NULL; it = it->next) {
        if (it->priority < highNode->priority) {
            highNode = it;
        }
    }
    return highNode->element;
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
