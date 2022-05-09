/**
 * C++ example to demonstrate the Binary Search Tree
 */
#include <iostream>
#include <queue>
using namespace std;

// Tree node representation
struct Node
{
    int data;    // Actual data
    Node* left;  // Pointer to left child
    Node* right; // Pointer to right child

    // Node constructor
    Node(int d) : data(d), left(NULL), right(NULL)
    {}
};

/**
 * Binary Search Tree implementation
 */
class BinarySearchTree
{
    // The root node
    Node* root;

public:
    // Constructor
    BinarySearchTree() : root(NULL)
    {}

    // Insert a new node
    void insert(int data) {
        root = insert(root, data);
    }

    // Delete the node by the given data
    void remove(int data) {
        root = remove(root, data);
    }

    // Search the node by the given data
    Node* search(int data) {
        return search(root, data);
    }
    
    // Preorder traversal
    void preorder() {
        preorder(root);
    }

    // Postorder traversal
    void postorder() {
        postorder(root);
    }

    // Inorder traversal
    void inorder() {
        inorder(root);
    }

    // Levelorder traversal
    void levelorder() {
        levelorder(root);
    }

private:
    // Private methods that works recursively to perform the operations
    Node* insert(Node* p, int data);
    Node* remove(Node* p, int data);
    Node* search(Node* p, int data);
    void preorder(Node* p);
    void postorder(Node* p);
    void inorder(Node* p);
    void levelorder(Node* p);
};

// Insert a new node
Node* BinarySearchTree::insert(Node* p, int data)
{
    if (p == NULL) {
        // Found the location. Insert the node
        return new Node(data);
    } else if (data < p->data) {
        // Insert on left sub tree
        p->left = insert(p->left, data);
    } else {
        // Insert on right sub tree
        p->right = insert(p->right, data);
    }

    return p;
}

// Delete the node by the given data
Node* BinarySearchTree::remove(Node* p, int data)
{
    if (p == NULL) {
        // Reached the depth and the node not found
        return NULL;
    }

    if (data < p->data) {
        // Search on the left subtree for smaller elements.
        p->left = remove(p->left, data);

    } else if (data > p->data) {
        // Search on the right subtree for greater elements.
        p->right = remove(p->right, data);

    } else {
        // Found the target node
        // Node has either no child or one child
        if (p->left == NULL) {
            Node* right = p->right;
            delete p;
            return right;
        } else if (p->right == NULL) {
            Node* left = p->left;
            delete p;
            return left;
        }

        // Node has both left and right child.
        // Find the smallest node on its right subtree (inorder successor)
        Node* min;
        for (min = p->right; min->left != NULL; min = min->left)
            ;

        // Replace the target node's data with the smallest node
        p->data = min->data;
        p->right = remove(p->right, min->data);
    }

    return p;
}

// Search the node by the given data
Node* BinarySearchTree::search(Node* p, int data)
{
    if (p == NULL) {
        // Reached the depth and the node not found
        return NULL;
    }

    // Check if the current node matches the data and return the node if true.
    if (data == p->data) {
        return p;
    } else if (data < p->data) {
        // Search on the left sub tree and return the node if found.
        return search(p->left, data);
    } else {
        // Search on the right sub tree and return the node if found.
        return search(p->right, data);
    }
}

// Traverse the tree in preorder (parent, left, right)
void BinarySearchTree::preorder(Node* p)
{
    if (p != NULL) {
        cout << p->data << endl;
        preorder(p->left);
        preorder(p->right);
    }
}

// Traverse the tree in postorder (left, right, parent)
void BinarySearchTree::postorder(Node* p)
{
    if (p != NULL) {
        postorder(p->left);
        postorder(p->right);
        cout << p->data << endl;
    }
}

// Traverse the tree inorder (left, parent, right)
void BinarySearchTree::inorder(Node* p)
{
    if (p != NULL) {
        inorder(p->left);
        cout << p->data << endl;
        inorder(p->right);
    }
}

// Traverse the tree in level order (breadth first)
void BinarySearchTree::levelorder(Node* p)
{
    if (p == NULL) {
        return;
    }

    // Start the traversal from root node
    std::queue<Node*> q;
    q.push(root);

    while (! q.empty()) {
        Node* p = q.front();
        q.pop();

        // Visit the current node
        cout << p->data << endl;

        // Enqueue the left and right child to process in order.
        if (p->left != NULL) {
            q.push(p->left);
        }
        if (p->right != NULL) {
            q.push(p->right);
        }
    }
}

int main()
{
    /** Create a binary search tree and insert data
     *           30
     *         /    \
     *        20    50
     *       /     /  \
     *      10   40    60
     */
    BinarySearchTree tree;
    tree.insert(40);
    tree.insert(20);
    tree.insert(50);
    tree.insert(30);
    tree.insert(10);

    // Search
    Node* p = tree.search(30);
    cout << "Search(30) located node: " << p->data << endl;

    // Traversals
    cout << "Binary Tree inorder traversal" << endl;
    tree.inorder();
    cout << "Binary Tree preorder traversal" << endl;
    tree.preorder();
    cout << "Binary Tree postorder traversal" << endl;
    tree.postorder();
    cout << "Binary Tree level order traversal" << endl;
    tree.levelorder();

    // Delete data
    tree.remove(20);
    tree.remove(10);
    cout << "Binary Tree level inorder traversal after removing 20 and 10" << endl;
    tree.inorder();
}
