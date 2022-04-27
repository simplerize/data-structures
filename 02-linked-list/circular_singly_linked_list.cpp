/**
 * C++ example to demonstrate the circular linked list
 */
#include <iostream>
using namespace std;

// Linked list node representation
struct Node
{
    int element;
    Node* next;
};

/**
 * Circular linked list implementation
 */
class CircularList
{
    // The last node of the list
    // The last->next contains the address of head node
    Node* last;

public:
    // Constructor
    CircularList() : last(NULL) {}

    // Insert an element in front of the list
    // Returns the new node inserted
    Node* insert_front(int element);

    // Insert an element at the end of the list
    // Returns the new node inserted
    Node* insert_back(int element);

    // Insert an element after the given node
    // Returns the new node inserted
    Node* insert_after(Node* prev, int element);
    
    // Delete the front element
    // Returns the next node if available, NULL otherwise.
    Node* delete_front();
    
    // Delete the node after the given node
    // Returns true on success, false otherwise.
    bool delete_after(Node* prev);

    // Search and delete the given element
    // Returns true on success, false otherwise.
    bool remove(int element);
    
    // Search an element from the list
    // Returns the matching node if found, NULL otherwise.
    Node* search(int element);
    
    // Traverse the list and print the elements
    void traverse(const std::string& msg);
};

Node* CircularList::insert_front(int element)
{
    // Step 1. Create the new node
    Node* new_node = new Node();
    new_node->element = element;

    // Step 2. Check if the list is empty. If true, make the new node
    // as last and point itself to form the one node circle.
    if (last == NULL) {
        new_node->next = new_node;
        last = new_node;
        return new_node;
    }
    
    // Step 3. Connect the new node at front.
    // The last->next is the front node of circular linked list
    new_node->next = last->next;
    last->next = new_node;
    
    return new_node;
}

Node* CircularList::insert_back(int element)
{
    // Step 1. Create the new node
    Node *new_node = new Node();
    new_node->element = element;
    
    // Step 2. Check if the list is empty. If true, make the new node
    // as last and point itself to form the one node circle.
    if (last == NULL) {
        new_node->next = new_node;
        last = new_node;
        return new_node;
    }
    
    // Step 3. Link the new node after the last node
    new_node->next = last->next;
    last->next = new_node;

    // Step 4. Make the new node as last node
    last = new_node;
    
    return new_node;
}

Node* CircularList::insert_after(Node* prev, int element)
{
    // Step 1. Create the new node
    Node *new_node = new Node();
    new_node->element = element;

    // Step 2. Link the new node after the given node
    new_node->next = prev->next;
    prev->next = new_node;

    return new_node;
}

Node* CircularList::delete_front()
{
    // Step 1. Check if the list is empty. If true, return.
    if (last == NULL) {
        return NULL;
    }

    // Step 2. Check if the list has single node. If true, delete the node,
    // reset the last to NULL, and return.
    if (last->next == last) {
        delete last;
        last = NULL;
        return NULL;
    }

    // Step 3. Store the reference to front node as target
    Node* target = last->next;
    
    // Step 4. Skip the front node and connect the last node directly with next node.
    last->next = last->next->next;
    
    // Step 5. Delete the target node
    delete target;

    return last->next;
}

bool CircularList::delete_after(Node* prev)
{
    // Step 1. Initialize target with the reference to target node
    Node* target = prev->next;

    // Step 2. Check if the list has single node and return if true.
    if (prev == target) {
        return false;
    }

    // Step 3. Disconnect the target node by directly linking its
    // previous and next node.
    prev->next = target->next;

    // Step 4. Check if the target node is the last node. If true,
    // move the last pointer to previous node
    if (target == last) {
        last = prev;
    }

    // Step 4. Delete the target node
    delete target;

    return true;
}

bool CircularList::remove(int element)
{
    // Step 1. Check if the list is empty and return if true.
    if (last == NULL) {
        return false;
    }

    // Step 2. Check if the list contains only node
    if (last == last->next) {
        if (last->element == element) {
            delete last;
            last = NULL;
            return true;
        }
        return false;
    }
    
    // Step 3. Iterate the linked list from start to end,
    // and search if the element is found.
    for (Node* node = last; node->next != last; node = node->next) {
        
        if (node->next->element == element) {
            // Step 4. If found, set the node as target node and disconnect
            // it by directly linking its previous and next node.
            Node* target = node->next;
            node->next = node->next->next;
            
            // Step 5. Delete the target node
            delete target;
            return true;
        }
    }
    
    return false;
}

Node* CircularList::search(int element)
{
    // Check if the list is empty
    if (last == NULL) {
        return NULL;
    }

    // Iterate the linked list from start to end and search element
    Node* node = last->next;
    do {
        if (node->element == element) {
            return node; // Found element
        }
        node = node->next;
    } while (node != last->next);

    return NULL; // Not found
}

// Traverse and print the linked list
void CircularList::traverse(const std::string& msg)
{
    cout << msg << endl;
    if (last == NULL ) {
        cout << "NULL" << endl << endl;
        return;
    }
    
    // Iterate the linked list from start to end
    Node* node = last->next;
    do {
        cout << " --> " << node->element ;
        node = node->next;
    } while (node != last->next);
    cout << " --> " << endl << endl;
}

int main()
{
    // Create a linked list
    CircularList list;
    list.traverse("initial list");

    // Insert elements
    Node* node_10 = list.insert_front(10);
    list.traverse("insert_front(10)");

    list.insert_back(30);
    list.traverse("insert_back(30)");

    list.insert_after(node_10, 20);
    list.traverse("insert_after(node_10, 20)");
    
    // Search an element
    Node* node_20 = list.search(20);
    cout << "search(20) matches node " << node_20->element << endl << endl;

    // Delete elements
    list.delete_front();
    list.traverse("delete_front()");
    
    list.delete_after(node_20);
    list.traverse("delete_after(node_20)");
    
    list.remove(20);
    list.traverse("remove(20)");
}
