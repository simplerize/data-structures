/**
 * C++ example to demonstrate the Binary Tree
 */
#include <iostream>
#include <queue>
using namespace std;

// Binary Tree node representation
struct Node
{
    int data;    // Actual data
    Node* left;  // Pointer to left child
    Node* right; // Pointer to right child

    // Node constructor
    Node(int d) : data(d), left(NULL), right(NULL) {}
};

/**
 * Binary Tree implementation
 */
class BinaryTree
{
    // The root node
    Node* root;

public:
    // Constructor
    BinaryTree() : root(NULL) {}

    // Get the root node
    Node* get_root() { return root; }

    // Insert a node in the deepest location
    // Returns the node inserted
    Node* insert(int data);

    // Delete the node by the given data
    void remove(int data);

    // Search the node by the given data
    Node* search(int data, Node* root);
    
    // Preorder traversal
    void traverse_preorder(Node* p);

    // Postorder traversal
    void traverse_postorder(Node* p);

    // Inorder traversal
    void traverse_inorder(Node* p);

    // Levelorder traversal
    void traverse_levelorder(Node* p);
};

// Insert a node in the deepest location
Node* BinaryTree::insert(int data)
{
    // Check if the tree is empty. If so, insert the node at the root.
    if (root == NULL) {
        root = new Node(data);
        return root;
    }

    // Traverse the tree in level order to insert in the deepest location. 
    std::queue<Node*> q;
    q.push(root);
    while (! q.empty()) {
        Node* p = q.front();
        q.pop();

        if (p->left == NULL) {
            p->left = new Node(data);
            return p->left;
        } else {
            q.push(p->left);
        }

        if (p->right == NULL) {
            p->right = new Node(data);
            return p->right;
        } else {
            q.push(p->left);
        }
    }
}

// Delete the node by the given data
void BinaryTree::remove(int data)
{
    // Check the tree is empty and return if true
    if (root == NULL) {
        return;
    }

    // Check the tree has only a single node.
    if (root->left == NULL && root->right == NULL) {
        // Check if the root node matches the given data.
        if (root->data == data) {
            // Delete the root node
            delete root;
            root = NULL;
        }
        return;
    }

    Node *target = NULL; // Node requested for deletion
    Node* p = NULL;      // Last node of the tree
    Node *pp = NULL;     // Parent of last node

    // Traverse the tree in level order
    std::queue<Node*> q;
    q.push(root);
    while (! q.empty()) {
        p = q.front();
        q.pop();

        if (p->data == data) {
            // Found the target node, proceed to find the last node
            target = p;
        }
        if (p->left != NULL) {
            pp = p;
            q.push(p->left);
        }
        if (p->right != NULL) {
            pp = p;
            q.push(p->right);
        }
    }

    // Replace the target node with the last node's data and delete the last node
    if (target != NULL) {
        target->data = p->data;
        if (pp->left == p) {
            pp->left = NULL;
        } else {
            pp->right = NULL;
        }
        delete p;
    }
}

// Search the node by the given data
Node* BinaryTree::search(int data, Node* root)
{
    // Check if the tree is empty and return
    if (root == NULL) {
        return NULL;
    }

    // Check if the current node matches the data and return the node if true.
    if (root->data == data) {
        return root;
    }

    // Search on the left sub tree and return the node if found.
    Node* target = search(data, root->left);
    if (target != NULL) {
        return target;
    }

    // Search on the right sub tree and return the node if found.
    target = search(data, root->right);
    return target;
}

// Traverse the tree in preorder (parent, left, right)
void BinaryTree::traverse_preorder(Node* p)
{
    if (p != NULL) {
        cout << p->data << endl;
        traverse_preorder(p->left);
        traverse_preorder(p->right);
    }
}

// Traverse the tree in postorder (left, right, parent)
void BinaryTree::traverse_postorder(Node* p)
{
    if (p != NULL) {
        traverse_postorder(p->left);
        traverse_postorder(p->right);
        cout << p->data << endl;
    }
}

// Traverse the tree inorder (left, parent, right)
void BinaryTree::traverse_inorder(Node* p)
{
    if (p != NULL) {
        traverse_inorder(p->left);
        cout << p->data << endl;
        traverse_inorder(p->right);
    }
}

// Traverse the tree in level order (breadth first)
void BinaryTree::traverse_levelorder(Node* p)
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
    /** Create a binary tree and insert data
     *           10
     *         /    \
     *        20    30
     *      /    \
     *     40    50
     */
    BinaryTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    // Search
    Node* p = tree.search(30, tree.get_root());
    cout << "Search(30) located node: " << p->data << endl;

    // Traversals
    cout << "Binary Tree preorder traversal" << endl;
    tree.traverse_preorder(tree.get_root());
    cout << "Binary Tree inorder traversal" << endl;
    tree.traverse_inorder(tree.get_root());
    cout << "Binary Tree postorder traversal" << endl;
    tree.traverse_postorder(tree.get_root());
    cout << "Binary Tree level order traversal" << endl;
    tree.traverse_levelorder(tree.get_root());

    // Delete data
    tree.remove(20);
    tree.remove(10);
    cout << "Binary Tree level order traversal" << endl;
    tree.traverse_levelorder(tree.get_root());
}
