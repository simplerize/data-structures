/**
 * C++ example to demonstrate the Doubly Linked List
 */
#include <iostream>
using namespace std;

// Linked list node representation
struct Node
{
    int element;
    Node* prev;
    Node* next;
};

/**
 * Doubly Linked list implementation
 */
class DoublyList
{
    // Head of the list
    Node* head;

public:
    // Constructor
    DoublyList() : head(NULL) {}

    // Insert an element in front of the list
    // Returns the new node inserted
    Node* insert_front(int element);

    // Insert an element at the end of the list
    // Returns the new node inserted
    Node* insert_back(int element);

    // Insert an element before the given node
    // Returns the new node inserted
    Node* insert_before(Node* next, int element);

    // Insert an element after the given node
    // Returns the new node inserted
    Node* insert_after(Node* prev, int element);

    // Delete the front element
    // Returns the next node if available, NULL otherwise.
    Node* delete_front();

    // Delete the element from end of the list
    // Returns the previous node, NULL otherwise.
    Node* delete_back();

    // Delete the given node
    // Returns the next node if available, NULL otherwise.
    Node* delete_node(Node* target);

    // Search and delete the given element
    void remove(int element);

    // Search an element from the list
    // Returns the matching node if found, NULL otherwise.
    Node* search(int element);

    // Print the elements
    void print(const std::string& msg);
};

Node* DoublyList::insert_front(int element)
{
    // Step 1. Create the new node
    Node* new_node = new Node();
    new_node->element = element;

    // Step 2. Link the new node before the head node
    new_node->prev = NULL;
    new_node->next = head;
    if (head != NULL) {
        head->prev = new_node;
    }

    // Step 3. Change the head to point the new node
    head = new_node;

    return new_node;
}

Node* DoublyList::insert_before(Node* next, int element)
{
    // Step 1. Create the new node
    Node *new_node = new Node();
    new_node->element = element;

    // Step 2. Link the new node before the given node
    new_node->prev = next->prev;
    new_node->next = next;
    next->prev = new_node;
    if (new_node->prev != NULL) {
        new_node->prev->next = new_node;
    }

    return new_node;
}

Node* DoublyList::insert_after(Node* prev, int element)
{
    // Step 1. Create the new node
    Node *new_node = new Node();
    new_node->element = element;

    // Step 2. Link the new node after the given node
    new_node->prev = prev;
    new_node->next = prev->next;
    prev->next = new_node;
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }

    return new_node;
}

Node* DoublyList::insert_back(int element)
{
    // Step 1. Check if the list is empty. If true, perform insert_front() and return.
    if (head == NULL) {
        return insert_front(element);
    }

    // Step 2. Traverse the list and find the last node
    Node *p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    // Step 3. Perform insert_after() with the last node found
    return insert_after(p, element);
}

Node* DoublyList::delete_front()
{
    // Step 1. Store the reference to head as target and
    // move the head to next node if available, NULL otherwise.
    Node* target = head;
    head = head->next;

    // Step 2. Disconnect the target node from the list
    if (head != NULL) {
        head->prev = NULL;
    }

    // Step 3. Delete the target node
    delete target;

    return head;
}

Node* DoublyList::delete_node(Node* target)
{
    // Step 1. Check if the target node is head. If true, perform
    // delete_front() and return.
    if (target->prev == NULL) {
        return delete_front();
    }

    // Step 2. Disconnect the target node by directly linking its
    // previous and next node.
    Node *next = target->next;
    target->prev->next = next;
    if (next != NULL) {
        next->prev = target->prev;
    }

    // Step 3. Delete the target node
    delete target;

    return next;
}

Node* DoublyList::delete_back()
{
    // Step 1. Check if the list is empty and return if true.
    if (head == NULL) {
        return NULL;
    }

    // Step 2. Traverse the list and find the last node as target
    Node *target = head;
    while (target->next != NULL) {
        target = target->next;
    }
    Node* prev = target->prev;

    // Step 3. Delete the target node using delete_node()
    delete_node(target);
    
    return prev;
}

void DoublyList::remove(int element)
{
    // Step 1. Search the element in linked list from start to end.
    for (Node* p = head ; p != NULL ; p = p->next) {
        if (p->element == element) {
            // Step 2. If found, perform delete_node() and return.
            delete_node(p);
            return;
        }
    }

    return;
}

Node* DoublyList::search(int element)
{
    // Iterate the linked list from start to end
    for (Node* node = head ; node != NULL ; node = node->next) {
        if (node->element == element) {
            return node; // Found element
        }
    }
    return NULL; // Not found
}

// Print the linked list
void DoublyList::print(const std::string& msg)
{
    cout << msg << endl;
    cout << "HEAD --> ";
    // Iterate the linked list from start to end
    for (Node* node = head ; node != NULL ; node = node->next) {
        cout << node->element;
        cout << ((node->next == NULL)? " --> " : " <==> ");
    }
    cout << "NULL" << endl << endl;
}

int main()
{
    // Create a linked list
    DoublyList list;
    list.print("initial list");

    // Insert elements
    Node* node_10 = list.insert_front(10);
    list.print("insert_front(10)");

    Node* node_40 = list.insert_back(40);
    list.print("insert_back(40)");

    list.insert_after(node_10, 20);
    list.print("insert_after(node_10, 20)");

    list.insert_before(node_40, 30);
    list.print("insert_before(node_40, 30)");

    // Search an element
    Node *node_30 = list.search(30);
    cout << "search(30) matches node " << node_30->element << endl << endl;

    // Delete elements
    list.delete_front();
    list.print("delete_front()");

    list.delete_node(node_30);
    list.print("delete_node(node_30)");

    list.delete_back();
    list.print("delete_back()");

    list.remove(20);
    list.print("remove(20)");
}
