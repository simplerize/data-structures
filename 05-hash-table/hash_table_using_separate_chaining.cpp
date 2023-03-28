/**
 * C++ example to demonstrate Hash Table implementation using Seperate Chaining
 */

#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Hash Table Node
 */
struct Node
{
	std::string key;
	int val;
	Node* next;
};

/**
 * Hash Table implementation using Separate Chaining
 */
class HashTable
{
private:
    // Hash Table
    Node** hash_table;
    
    // Hash Table Size
    int size;

public:
    // Constructor
    HashTable(int size);
    
    // Destructor
    ~HashTable();
    
    // Insert the key-value pair
    // Return the node inserted, NULL otherwise.
    Node* insert(std::string key, int val);
    
    // Delete the element by key
    // Returns true on success, false otherwise.
    bool remove(std::string key);
    
    // Access the key-value pair
    // Returns the node associated with the key
    Node* get(std::string key);
    
    // Traverse and print the hash table
    void display(std::string msg);
    
private:
    // Hash function to determine the index for every key
    int hash(std::string key, int size);
};

HashTable::HashTable(int sz) : size(sz)
{
    // Create the hash table for the given size 
    hash_table = new Node*[size];
    
    // Initialize the table entries to NULL
    for (int i=0; i < size; ++i) {
        hash_table[i] = NULL;
    }
}

Node* HashTable::insert(std::string key, int val)
{
    // Step 1. Create the new node
    Node *new_node = new Node();
    new_node->key = key;
    new_node->val = val;

    // Step 2. Determine the hash index for the key
    int index = hash(key, size);
    
    // Step 3. Insert the node in the front side of chain
    new_node->next = hash_table[index];
    hash_table[index] = new_node;
    
    return new_node;
}

bool HashTable::remove(std::string key)
{
    // Step 1. Determine the hash index for the key
    int index = hash(key, size);
    
    // Step 2. Check if the key exists in the located index
    if (hash_table[index]->key.compare(key) == 0) {
        // Step 3. If true, remove the node found on the index
        
        // Set this node as target node
        Node* target = hash_table[index];
        
        // Replace the index with the next node if found. NULL otherwise.
        hash_table[index] = hash_table[index]->next;
        
        // Delete the target node and return.
        delete target;
        return true;
    }
    
    // Step 4. Otherwise, search and remove the key in the chain.
    // Traverse the chain from start to end.
    for (Node* p = hash_table[index]; p->next != NULL; p = p->next) {
        if (p->next->key.compare(key) == 0) {
            // If the key exists, set the node as target
            Node* target = p->next;
            // Disconnect the node by directly linking its previous and next.
            p->next = p->next->next;
            // Delete the target node and return.
            delete target;
            return true;
        }
    }
    
    return false;
}

Node* HashTable::get(std::string key)
{
    // Step 1. Determine the hash index for the key
    int index = hash(key, size);
    
    // Step 2. Traverse the chain starting from the index node.
    for (Node* p = hash_table[index]; p != NULL; p = p->next) {
        if (p->key.compare(key) == 0) {
            // Step 3. Return the node if the key matches any of the node. NULL otherwise.
            return p;
        }
    }
    return NULL;
}

void HashTable::display(std::string msg)
{
	cout << msg << endl;
	
	// Traverse the entire hash table
	for (int i=0; i < size; ++i) {
	    cout <<      "  +--------+--------+" << endl;
	    cout << i << " |";
	    Node* p = hash_table[i];
		if (p == NULL ) {
		    // NULL record, print empty
		    cout << " " << setw(6) << "" << " | " << setw(6) << "" << " |";
		    
		} else {
		    // Print the record from the table
		    cout << " " << setw(6) << left << p->key << " | " << setw(6) << right << p->val << " |";
		    
		    // Traverse and print the chain
		    for (p = p->next; p != NULL ; p = p->next) {
		      cout << " --> " << "[ " << p->key << " | " << p->val << " ]";
		    }
		}
		cout << endl;
	}
	cout << "  +--------+--------+" << endl << endl;
}

HashTable::~HashTable()
{
    for (int i=0; i < size; ++i) {
        Node* p = hash_table[i];
        if (p != NULL) {
            // Delete the chain if available
            Node* chain = p->next;
            while (chain != NULL) {
                Node* target = chain;
                chain = chain->next;
                delete target;
            }
            
            // Delete the table record
            delete p;
            hash_table[i] = NULL;
        }
    }
}

int HashTable::hash(std::string key, int size)
{
    // A simple hash method to sum the ASCII values
    int hash = 0;
    for (int i=0; i < key.size(); ++i) {
        hash += key[i];
    }
    return hash % size;
}
 
// The main function to begin the execution   
int main()
{
    // Create the hash table of size 8
    HashTable customers(8);
    
    // Insert key-value pairs
    customers.insert("Alice", 101);
    customers.insert("Bell", 102);
    customers.insert("Max", 103);
    customers.insert("Evin", 104);
    customers.insert("Ana", 105);
    customers.insert("Dave", 106);
    customers.insert("Leo", 107);
    customers.display("HASH TABLE after insertion of customers 'Alice', 'Bell', 'Max', 'Evin', 'Ana', 'Dave', and 'Leo'.");
    
    // Delete key-value pairs
    customers.remove("Dave");
    customers.remove("Ana");
    customers.remove("Max");
    customers.display("HASH TABLE after deletion of customers 'Dave', 'Ana', and 'Max'.");
    
    // Access a key
    Node* bell = customers.get("Bell");
    cout << "Accessing key 'Bell' returned value: " << bell->val << endl;
}
