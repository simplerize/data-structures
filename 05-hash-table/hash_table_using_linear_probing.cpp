/**
 * C++ example to demonstrate Hash Table implementation using Linear Probing
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
};

/**
 * Hash Table implementation using Linear Probing
 */
class HashTable
{
private:
    // Hash Table
    Node** hash_table;
    
    // Hash Table maximum capacity
    int capacity;
    
    // Hash Table current size
    int size;
    
    // Empty node used for deletion
    Node* del_node;

public:
    // Constructor
    HashTable(int capacity);
    
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
    int hash(std::string key, int capacity);
};

HashTable::HashTable(int capacity) : capacity(capacity), size(0)
{
    // Create the hash table for the given capacity 
    hash_table = new Node*[capacity];
    
    // Initialize the table entries to NULL
    for (int i=0; i < capacity; ++i) {
        hash_table[i] = NULL;
    }
    
    // Initialize the deleted node
    del_node = new Node();
    del_node->key = "";
    del_node->val = -1;
}

HashTable::~HashTable()
{
    for (int i=0; i < capacity; ++i) {
        if (hash_table[i] != NULL && ! hash_table[i]->key.empty()) {
            // Delete the table record
            delete hash_table[i];
            hash_table[i] = NULL;
        }
    }
    
    // Free the del node
    free(del_node);
}

Node* HashTable::insert(std::string key, int val)
{
    // Step 1. Check if the hash table size reached its capacity. If true, return.
    if (size == capacity) {
        return NULL;
    }
    
    // Step 2. Initialize the target index for insertion as -1.
    int target_index = -1;

    // Step 3. Determine the hash index for the key.
    int hash_index = hash(key, capacity);
    
    // Step 4. Check if the hash index is free. If true, set this as target index.
    if (hash_table[hash_index] == NULL ||
        hash_table[hash_index]->key.empty() || hash_table[hash_index]->key == key) {
            target_index = hash_index;
        
    } else {
        // Step 5. Otherwise, sequentially search the table for the free index.
        // Iterate the table once in circular motion from the next index.
        int i = (hash_index+1) % capacity;
        while (i != hash_index) {
            if (hash_table[i] == NULL || hash_table[i]->key.empty() || hash_table[i]->key == key) {
                // Step 6. If a free index is found, set this as target index and
                // stop the iteration
                target_index = i;
                break;
            }
            i = (i+1) % capacity;
        }
    }
    
    // Step 7. Create the new node.
    Node *new_node = new Node();
    new_node->key = key;
    new_node->val = val;
    
    // Step 8. Insert the new node to target index.
    hash_table[target_index] = new_node;
    ++size;
    
    return new_node;
}

bool HashTable::remove(std::string key)
{
    // Step 1. Initialize the target index as -1.
    int target_index = -1;
    
    // Step 2. Determine the hash index for the key.
    int hash_index = hash(key, capacity);
    
    // Step 3. Check if the key exists in the hash index.
    if (hash_table[hash_index]->key == key) {
        // Step 4. If true, set the hash index as target for deletion
        target_index = hash_index;
    } else {
    
        // Step 5. Otherwise, sequentially search the table for the key.
        // Iterate the table once in circular motion from the next index.
        // Stop the iteration if any NULL node found inbetween.
        int i = (hash_index+1) % capacity;
        while (i != hash_index && hash_table[i] != NULL) {
            if (hash_table[i]->key == key) {
                // Step 6. If key is found, set the index as target for deletion.
                target_index = i;
                break;
            }
            i = (i+1) % capacity;
        }
    }
    
    // Step 7. Otherwise, if the key is not found, return false.
    if (target_index == -1) {
        return false;
    }
    
    // Step 8. Delete the target node and return true.
    delete hash_table[target_index];
    hash_table[target_index] = del_node;
    --size;
    return true;
}

Node* HashTable::get(std::string key)
{
    // Step 1. Determine the hash index for the key
    int hash_index = hash(key, capacity);
    
    // Step 2. Check if the key is found on the hash index
    if (hash_table[hash_index]->key == key) {
        // Step 3. If true, return the node.
        return hash_table[hash_index];
    }
    
    // Step 3. Otherwise traverse the table once in circular motion from the next index.
    // Stop the iteration if any NULL node found inbetween.
    int i = (hash_index+1) % capacity;
    while (i != hash_index && hash_table[i] != NULL) {
        if (hash_table[i]->key == key) {
            // Step 4. If key is found, return the node.
            return hash_table[i];
        }
        i = (i+1) % capacity;
    }
    
    return NULL;
}

void HashTable::display(std::string msg)
{
    cout << msg << endl;
    cout << "(size = " << size << ")" << endl;
	
    // Traverse the entire hash table
    for (int i=0; i < capacity; ++i) {
        cout <<      "  +--------+--------+" << endl;
        cout << i << " |";
        Node* p = hash_table[i];
    	if (p == NULL ) {
    	    // NULL record, print empty
    	    cout << " " << setw(6) << "" << " | " << setw(6) << "" << " |";
  
        } else {
    	    // Print the record from the table
    	    cout << " " << setw(6) << left << p->key << " | " << setw(6) << right << p->val << " |";
    	}
    	cout << endl;
    }
    cout << "  +--------+--------+" << endl << endl;
}

int HashTable::hash(std::string key, int capacity)
{
    // A simple hash method to sum the ASCII values
    int hash = 0;
    for (int i=0; i < key.size(); ++i) {
        hash += key[i];
    }
    return hash % capacity;
}
 
// The main function to begin the execution   
int main()
{
    // Create the hash table of capacity 8
    HashTable keywords(8);
    
    // Insert key-value pairs
    keywords.insert("new", 1001);
    keywords.insert("delete", 1002);
    keywords.insert("int", 1003);
    keywords.insert("float", 1004);
    keywords.insert("if", 1005);
    keywords.insert("for", 1006);
    keywords.display("HASH TABLE after insertion of keywords 'new', 'delete', 'int', 'float', 'if', and 'for'");
    
    // Delete key-value pairs
    keywords.remove("int");
    keywords.remove("for");
    keywords.remove("delete");
    keywords.display("HASH TABLE after deletion of keywords 'int', 'for', and 'delete'");
    
    // Access a key
    Node* node = keywords.get("new");
    cout << "Accessing key 'new' returned value: " << node->val << endl;
    
    return 0;
}
