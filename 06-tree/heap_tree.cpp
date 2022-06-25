/**
 * C++ example to demonstrate the Heap
 */
#include <iostream>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

/**
 * Heap implementation
 */
class Heap
{
    // Heap
    std::vector<int> heap;

    // Comparator to decide min or max heap
    // Use std::greater for max heap and std::less for min heap
    std::function<bool(int,int)> comp;

public:
    // Constructor
    Heap(std::function<bool(int,int)> comp) : comp(comp) {}

    // Create the heap from an array of elements
    void build_heap(int data[], int size);

    // Heapify the tree from the given node
    void heapify(int i);

    // Insert a new element
    void insert(int data);

    // Delete the peek element and return the data
    int remove();

    // Print the heap
    int print(std::string label = "");
};

// Create the heap from an array of elements
void Heap::build_heap(int data[], int size)
{
    // Replace the heap data
    heap.assign(data, data+size);

    // Start heapify from the last non leaf node to root
    int non_leaf = (size / 2) - 1;
    for (int i=non_leaf; i >= 0; --i) {
        heapify(i);
    }
}

// Heapify the tree by the given data
void Heap::heapify(int i)
{
    // Locate the indexes of it left and right child
    int parent = i;
    int left  = 2*parent + 1;
    int right = 2*parent + 2;
    
    // Check left child should be the parent as per heap property
    // For max heap, check if the left is greater than the parent
    // For min heap, check if the left is smaller than the parent
    if (left < heap.size() && comp(heap[left], heap[parent])) {
        parent = left;
    }
    
    // Check if the right child should be the parent
    if (right < heap.size() && comp(heap[right], heap[parent])) {
        parent = right;
    }

    // Swap elements if parent is changed and continue heapify
    // down the tree till the bottom.
    if (parent != i) {
        swap(heap.at(i), heap.at(parent));
        heapify(parent);
    }
}

// Insert a new element
void Heap::insert(int data)
{
    // Insert the element at the last position
    heap.push_back(data);

    int i = (int) heap.size() - 1;
    int parent = ((1+i) / 2) - 1; // Find its parent index

    // Navigate from the last position to root via parent node
    // Compare current node with the parent to satisfy either min or max heap
    while (parent >= 0 && comp(heap[i], heap[parent])) {
        // Swap the elements to maintain the heap order
        swap(heap.at(i), heap.at(parent));

        // Repeat this process until it reaches the position.
        i = parent;
        parent = ((i+1) / 2) - 1;
    }
}

// Remove the peek element
int Heap::remove()
{
    if (heap.size() == 0) {
        // Heap empty
        return -1;
    }

    // Replace the root node with the last element and delete the last
    int peek = heap[0];
    heap[0] = heap[heap.size()-1];
    heap.pop_back();

    // Heapify the root node so that it can rearrange the tree as per heap
    heapify(0);
    return peek;
}

// Print the heap
int Heap::print(std::string label)
{
    // Print label if provided
    if (! label.empty()) {
        cout << label << endl;
    }

    // Print heap elements as per array order
    for (auto d: heap) {
        cout << d << " ";
    }
    cout << endl;
}

int main()
{
    // Create a Min heap and insert elements
    Heap min_heap(std::less<>{});
    min_heap.insert(40);
    min_heap.insert(60);
    min_heap.insert(30);
    min_heap.insert(50);
    min_heap.insert(20);
    min_heap.insert(10);
    min_heap.print("Min heap after inserting 40, 60, 30, 50, 20, and 10");

    // Remove elements
    min_heap.remove();
    min_heap.remove();
    min_heap.print("Heap after removing couple of peek elements");

    // Create a Max Heap from the array of elements
    Heap max_heap(std::greater<>{});
    int data[] = {40, 60, 50, 30, 70, 20, 10};
    max_heap.build_heap(data, sizeof(data) / sizeof(data[0]));
    max_heap.print("Max heap built from the array {40, 60, 50, 30, 70, 20, 10}");
}
