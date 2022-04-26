/**
 * C++ example to demonstrate Array data structure
 */
#include <iostream>
using namespace std;

// Mmaximum capacity
#define CAPACITY 10

/**
 * Array implementation
 */
class Array
{
    // Array data
    int array[CAPACITY];
    
    // Size of the array
    int size;
    
public:
    // Constructor
    Array() : size(0) {}
    
    // Insert an element into the given position
    void insert_at(int element, int pos);
    
    // Delete an element by the given position
    void delete_at(int pos);
    
    // Search the given element and return the position
    // Returns the index if found, -1 otherwise.
    int search(int element);
    
    // Access the element at given position
    // Returns the element
    int get(int pos);
    
    // Traverse and print the elements
    void traverse(const std::string& msg);
};

void Array::insert_at(int element, int pos)
{
    // Step 1. Check if the Array is full. If true, return error.
    if (size >= CAPACITY) {
        throw std::runtime_error("array capacity reached");
    }
    
    // Step 2. Check if the given position is out of data range. If true, return error.
    // Allow to insert at the end of array anyway.
    if (pos < 0 || pos > size) {
        throw std::runtime_error("position out of insertion range");
    }
    
    // Step 3. Free up the space for the new element by shifting the elements to next position.
    for (int i=size ; i > pos ; --i) {
        array[i] = array[i-1];
    }
    
    // Step 4. Insert the new element at the given position
    array[pos] = element;
    
    // Step 5. Increment the size by 1
    ++size;
}

void Array::delete_at(int pos)
{
    // Step 1. Check if the given position is out of data range. If true, return error.
    if (pos < 0 || pos >= size) {
        throw std::runtime_error("position out of data range");
    }
    
    // Step 2. Delete the element by shifting the elements to previous position.
    for (int i=pos; i < (size-1); ++i) {
        array[i] = array[i+1];
    }
    
    // Step 3. Decrement the size by 1
    --size;
}

int Array::search(int element)
{
    // Step 1. Traverse the array from the first position
    for (int i=0; i < size; i++) {
        // Step 2. Check if the element exists in the position. If true, return the position.
        if (array[i] == element) {
            return i;
        }
    }
    // Step 3. If the element is not found after the traversal, return -1
    return -1;
}

int Array::get(int pos)
{
    // Step 1. Check if the given position is out of array range. If true, return error.
    if (pos < 0 || pos >= size) {
        throw std::runtime_error("position out of data range");
    }
    
    // Step 2. Return the element at the given position
    return array[pos];
}

void Array::traverse(const std::string& msg)
{
    cout << msg << endl;
    cout << "[";
    for (int i=0; i < size; i++) {
        cout << "  " << array[i];
    }
    cout << "  ]" << endl;
}

int main()
{
    // Creating an Array
    Array arr;
    
    // Insert elements
    arr.insert_at(0, 0);
    arr.traverse("Array after insert_at(0, 0)");
    //==> [ 0 ]
    
    arr.insert_at(10, 1);
    arr.traverse("Array after insert_at(10, 1)");
    //==> [ 0, 10 ]
    
    arr.insert_at(20, 2);
    arr.traverse("Array after insert_at(20, 2)");
    //==> [ 0, 10, 20 ]
    
    arr.insert_at(5, 1);
    arr.traverse("Array after insert_at(5, 1)");
    //==> [ 0, 5, 10, 20 ]
    
    arr.insert_at(15, 3);
    arr.traverse("Array after insert_at(15, 3)");
    //==> [ 0, 5, 10, 15, 20 ]
    
    cout << "Access element at index 3 = " << arr.get(3) << endl;
    
    cout << "Searching element 5 found at index = " << arr.search(5) << endl;
    
    // Delete elements
    arr.delete_at(1);
    arr.traverse("Array after delete_at(1)");
    //==> [ 0, 10, 15, 20 ]
    
    arr.delete_at(2);
    arr.traverse("Array after delete_at(2)");
    //==> [ 0, 10, 20 ]
    
    return 0;
}
