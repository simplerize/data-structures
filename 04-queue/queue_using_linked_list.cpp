/**
 * C++ example to demonstrate Queue implementation using Linked List
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
 * Queue implementation using Linked List
 */
class Queue
{
private:
    // Queue front pointer
    Node* front;
    
    // Queue rear pointer
    Node* rear;
    
public:
    // Constructor
    Queue() : front(NULL), rear(NULL) {}

    // Check if the Queue is empty
    bool isEmpty();
	
	// Returns the top element without deleting
    int peek();
	
	// Enqueue new element to Queue
    void enqueue(int element);
	
	// Dequeue an element from Queue
    int dequeue();
	
	// Traverse and display the Queue
    void display(string msg);
};

// Check if the Queue is empty
bool Queue::isEmpty() {
	if (front == NULL) {
		cout << "Queue is Empty" << endl;
		return true;
	}
	return false;
}

// Returns the top element without deleting
int Queue::peek() {
	if (isEmpty()) {
		return -1;
	}
	return front->element;
}

// Enqueue new element to Queue
void Queue::enqueue(int element) {		
	// Step 1: Create the new node
	Node* node = new Node();
	if (node == NULL) {
		cout << "System out of memory" << endl;
		return;
	}
	node->element = element;
	node->next = NULL;
	
	// Step 2: If the Queue is empty, set the Front to point the new node. Otherwise connect the new node at Rear.
	if (rear == NULL) {
		front = node;
	} else {
		rear->next = node;
	}
	
	// Step 3: Change the rear to point the new node
	rear = node;
}

// Dequeue an element from Queue
int Queue::dequeue() {
	// Check if the Queue is empty
	if (front == NULL) {
		return -1;
	}
	
	// Step 1: Retrieve the element at Front
	int element = front->element;
	
	// Step 2: Remember the front node in a temporary pointer
	Node* tmp = front;
	
	// Step 3: If the next node is available, change the Front to point the next node. Otherwise set Front and Rear to point the NULL
	if (front->next == NULL) {
		front = rear = NULL;
	} else {
		front = front->next;
	}
	
	// Step 4: Delete the node stored in temporary pointer
	delete tmp;
	
	return element;
}

// Traverse and display the Queue
void Queue::display(string msg) {
	cout << msg << endl;
	if (isEmpty()) {
		return;
	}
	
	if (front == rear) {
		cout << front->element << " <-- front, rear" << endl;
		return;
	}
	
	cout << front->element << " <-- front" << endl;
	for (Node* node=front->next; node != rear; node = node->next) {
		cout << node->element << endl;
	}
	cout << rear->element << " <-- rear" << endl;
}

// The main function to begin the execution
int main()
{
    // Create a Queue
    Queue queue;
    
    // Push the elements (10, 20, 30, 40 and 50)
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
    
    // Pop the elements from Queue
    element = queue.dequeue();
    cout << "Dequeue element returned " << element << endl;
    element = queue.dequeue();
    cout << "Dequeue element returned " << element << endl;
    queue.display("Queue after removing two elements");
}