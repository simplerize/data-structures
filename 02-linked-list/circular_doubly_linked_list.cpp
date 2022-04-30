/**
 * C++ example to demonstrate the circular doubly linked list
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
 * Circular doubly linked list implementation
 */
class CircularDoublyList
{
    // The first node of the list
    Node* head;

public:
    // Constructor
    CircularDoublyList() : head(NULL) {}

    // Insert an element in front of the list
    // Returns the new node inserted
    Node* insert_front(int element);

    // Insert an element at the end of the list
    // Returns the new node inserted
    Node* insert_back(int element);

    // Insert an element after the given node
    // Returns the new node inserted
    Node* insert_after(Node* prev, int element);
    
    // Delete the first node
    // Returns the next node if available, NULL otherwise.
    Node* delete_front();
    
    // Delete the last node
    // Returns the previous node if available, NULL otherwise.
    Node* delete_back();
    
    // Delete the specific node
    // Returns the next node if available, NULL otherwise.
    Node* delete_node(Node* prev);

    // Search and delete the given element
    // Returns true on success, false otherwise.
    bool remove(int element);
    
    // Search an element from the list
    // Returns the matching node if found, NULL otherwise.
    Node* search(int element);
    
    // Traverse the list and print the elements
    void traverse(const std::string& msg);
};

Node* CircularDoublyList::insert_front(int element)
{
    // Step 1. Create the new node
    Node* new_node = new Node();
    new_node->element = element;

    // Step 2. Check if the list is empty. If true, make the new node
    // as head and point itself to form the one node circle.
    if (head == NULL) {
        new_node->prev = new_node;
        new_node->next = new_node;
        head = new_node;
        return new_node;
    }
    
    // Step 3. Connect the new node at front.
    new_node->prev = head->prev;
    new_node->prev->next = new_node;
    new_node->next = head;
    new_node->next->prev = new_node;

    // Step 4. Make the new node as head
    head = new_node;
    
    return new_node;
}

Node* CircularDoublyList::insert_back(int element)
{
    // Step 1. Create the new node
    Node *new_node = new Node();
    new_node->element = element;
    
    // Step 2. Check if the list is empty. If true, make the new node
    // as head and point itself to form the one node circle.
    if (head == NULL) {
        new_node->prev = new_node;
        new_node->next = new_node;
        head = new_node;
        return new_node;
    }
    
    // Step 3. Link the new node after the last node
    new_node->prev = head->prev;
    new_node->prev->next = new_node;
    new_node->next = head;
    new_node->next->prev = new_node;

    return new_node;
}

Node* CircularDoublyList::insert_after(Node* prev, int element)
{
    // Step 1. Create the new node
    Node *new_node = new Node();
    new_node->element = element;

    // Step 2. Link the new node after the given node
    new_node->next = prev->next;
    new_node->next->prev = new_node;
    new_node->prev = prev;
    new_node->prev->next = new_node;

    return new_node;
}

Node* CircularDoublyList::delete_front()
{
    // Step 1. Check if the list is empty. If true, return.
    if (head == NULL) {
        return NULL;
    }

    // Step 2. Check if the list has single node. If true, delete the node,
    // reset the head to NULL, and return.
    if (head->next == head) {
        delete head;
        head = NULL;
        return NULL;
    }

    // Step 3. Skip the front node and connect the last node directly with next node.
    head->prev->next = head->next;
    head->next->prev = head->prev;
    
    // Step 4. Store the reference to front node as target
    Node* target = head;

    // Step 5. Move the head to next node
    head = head->next;
    
    // Step 6. Delete the target node
    delete target;
    return head;
}

Node* CircularDoublyList::delete_back()
{
    // Step 1. Check if the list is empty. If true, return.
    if (head == NULL) {
        return NULL;
    }

    // Step 2. Check if the list has single node. If true, delete the node,
    // reset the head to NULL, and return.
    if (head->next == head) {
        delete head;
        head = NULL;
        return NULL;
    }

    // Step 3. Skip the last node and connect its previous node with first node
    Node* target = head->prev;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    
    // Step 4. Delete the target node
    delete target;
    return head->prev;
}

Node* CircularDoublyList::delete_node(Node* target)
{
    // Step 1. Check if the list is empty. If true, return.
    if (head == NULL) {
        return NULL;
    }

    // Step 2. Check if the target node is head. If true,
    // perform delete_front()
    if (target == head) {
        return delete_front();
    }

    // Step 3. Otherwise, disconnect the node by directly linking
    // its previous and next node
    target->prev->next = target->next;
    target->next->prev = target->prev;
    
    // Step 4. Delete the target node
    Node* next_node = target->next;
    delete target;
    return next_node;
}

bool CircularDoublyList::remove(int element)
{
    // Step 1. Check if the list is empty and return if true.
    if (head == NULL) {
        return false;
    }

    // Step 2. Check if the element matches the head node. If true,
    // perform delete_front()
    if (element == head->element) {
        delete_front();
        return true;
    }
    
    // Step 3. Otherwise, iterate the linked list from start to end,
    // and search if the element is found.
    for (Node* node = head->next; node != head; node = node->next) {
        
        if (node->element == element) {
            // Step 4. If found, set the node as target node and disconnect
            // it by directly linking its previous and next node.
            Node* target = node;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            
            // Step 5. Delete the target node
            delete target;
            return true;
        }
    }
    
    return false;
}

Node* CircularDoublyList::search(int element)
{
    // Check if the list is empty
    if (head == NULL) {
        return NULL;
    }

    // Iterate the linked list from start to end and search element
    Node* node = head;
    do {
        if (node->element == element) {
            return node; // Found element
        }
        node = node->next;
    } while (node != head);

    return NULL; // Not found
}

// Traverse and print the linked list
void CircularDoublyList::traverse(const std::string& msg)
{
    cout << msg << endl;
    if (head == NULL ) {
        cout << "NULL" << endl << endl;
        return;
    }
    
    // Iterate the linked list from start to end
    Node* node = head;
    do {
        cout << " --> " << node->element ;
        node = node->next;
    } while (node != head);
    cout << " --> " << endl << endl;
}

int main()
{
    // Create a linked list
    CircularDoublyList list;
    list.traverse("initial list");

    // Insert elements
    Node* node_20 = list.insert_front(20);
    list.traverse("insert_front(20)");

    list.insert_front(10);
    list.traverse("insert_front(10)");

    list.insert_back(40);
    list.traverse("insert_back(40)");

    list.insert_after(node_20, 30);
    list.traverse("insert_after(node_20, 30)");

    // Search an element
    node_20 = list.search(20);
    cout << "search(20) matches node " << node_20->element << endl << endl;

    // Delete elements
    list.delete_front();
    list.traverse("delete_front()");
    
    list.delete_back();
    list.traverse("delete_back()");
    
    list.delete_node(node_20);
    list.traverse("delete_node(node_20)");
    
    list.remove(30);
    list.traverse("remove(30)");
}
