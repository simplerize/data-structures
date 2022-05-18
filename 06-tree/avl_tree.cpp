/**
 * C++ example to demonstrate the AVL Tree
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
    int height;  // Height of the node

    // Node constructor
    Node(int d) : data(d), left(NULL), right(NULL), height(1)
    {}
};

/**
 * AVL Tree implementation
 */
class AVLTree
{
    // The root node
    Node* root;

public:
    // Constructor
    AVLTree() : root(NULL)
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

    // Height of the tree
    int height() {
        return height(root);
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

    // Returns the height of given node
    int height(Node* p);
    // Returns the balance factor of given node
    int balance_factor(Node* p);
    // Perform left rotation of the given node
    Node* left_rotate(Node* p);
    // Perform right rotation of the given node
    Node* right_rotate(Node* p);
    // Left-Right rotation
    Node* left_right_rotate(Node* p);
    // Right-Left rotation
    Node* right_left_rotate(Node* p);
    // Rebalance the tree after insertion
    Node* rebalance_after_insert(Node* p, int data);
    // Rebalance the tree after deletion
    Node* rebalance_after_remove(Node* p);
};

// Height of the node
int AVLTree::height(Node* p)
{
    if (p == NULL) {
        return 0;
    }
    return p->height;
}

// Balance factor of the node
int AVLTree::balance_factor(Node* p)
{
    if (p == NULL) {
        return 0;
    }
    return height(p->right) - height(p->left);
}

// Perform left rotation of the given node
Node* AVLTree::left_rotate(Node* p)
{
    // Left rotation
    Node* parent = p->right;
    p->right = parent->left;
    parent->left = p;

    // Recalculate height
    p->height = 1 + std::max(height(p->left), height(p->right));
    parent->height = 1 + std::max(height(parent->left), height(parent->right));
    return parent;
}

// Perform right rotation of the given node
Node* AVLTree::right_rotate(Node* p)
{
    // Right rotation
    Node* parent = p->left;
    p->left = parent->right;
    parent->right = p;

    // Recalculate height
    p->height = 1 + std::max(height(p->left), height(p->right));
    parent->height = 1 + std::max(height(parent->left), height(parent->right));
    return parent;
}

// Left-Right rotation
Node* AVLTree::left_right_rotate(Node* p)
{
    p->left = left_rotate(p->left);
    return right_rotate(p);
}

// Right-Left rotation
Node* AVLTree::right_left_rotate(Node* p)
{
    p->right = right_rotate(p->right);
    return left_rotate(p);
}

// Insert a new node
Node* AVLTree::insert(Node* p, int data)
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
    p->height = 1 + std::max(height(p->right), height(p->left));

    // Rebalance the tree if required
    p = rebalance_after_insert(p, data);
    return p;
}

// Rebalance the tree after insertion
Node* AVLTree::rebalance_after_insert(Node* p, int data)
{
    // Check Balance factor and perform rotations if needed
    int bf = balance_factor(p);
    if (bf > 1) {
        if (data < p->right->data) {
            // Right-Left rotation
            p = right_left_rotate(p);
        } else {
            // Left rotation
            p = left_rotate(p);
        }

    } else if (bf < -1) {
        if (data >= p->left->data) {
            // Left-Right rotation
            p = left_right_rotate(p);
        } else {
            // Right rotation
            p = right_rotate(p);
        }
    }

    return p;
}

// Delete the node by the given data
Node* AVLTree::remove(Node* p, int data)
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
        return p;
    }
    p->height = 1 + std::max(height(p->right), height(p->left));

    // Rebalance the tree if required
    p = rebalance_after_remove(p);
    return p;
}

// Rebalance the tree after deletion
Node* AVLTree::rebalance_after_remove(Node* p)
{
    // Check Balance factor and perform rotations if needed
    int bf = balance_factor(p);
    if (bf > 1) {
        int right_bf = balance_factor(p->right);
        if (right_bf < 0) {
            // Right-Left rotation
            p = right_left_rotate(p);
        } else {
            // Left rotation
            p = left_rotate(p);
        }

    } else if (bf < -1) {
        int left_bf = balance_factor(p->left);
        if (left_bf > 0) {
            // Left-Right rotation
            p = left_right_rotate(p);
        } else {
            // Right rotation
            p = right_rotate(p);
        }
    }

    return p;
}

// Search the node by the given data
Node* AVLTree::search(Node* p, int data)
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
void AVLTree::preorder(Node* p)
{
    if (p != NULL) {
        cout << p->data << endl;
        preorder(p->left);
        preorder(p->right);
    }
}

// Traverse the tree in postorder (left, right, parent)
void AVLTree::postorder(Node* p)
{
    if (p != NULL) {
        postorder(p->left);
        postorder(p->right);
        cout << p->data << endl;
    }
}

// Traverse the tree inorder (left, parent, right)
void AVLTree::inorder(Node* p)
{
    if (p != NULL) {
        inorder(p->left);
        cout << p->data << endl;
        inorder(p->right);
    }
}

// Traverse the tree in level order (breadth first)
void AVLTree::levelorder(Node* p)
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
    // Create a AVL tree and insert data
    AVLTree tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    tree.insert(50);
    tree.insert(40);
    cout << "Tree height = " << tree.height() << " (after inserting 30, 20, 10, 50, 40)" << endl;

    // Search
    Node* p = tree.search(30);
    cout << "Search(30) located node: " << p->data << endl;

    // Traversals
    cout << "AVL Tree inorder traversal" << endl;
    tree.inorder();
    cout << "AVL Tree preorder traversal" << endl;
    tree.preorder();
    cout << "AVL Tree postorder traversal" << endl;
    tree.postorder();
    cout << "AVL Tree level order traversal" << endl;
    tree.levelorder();

    // Delete data
    tree.remove(10);
    tree.remove(50);
    cout << "Tree height = " << tree.height() << " (after removing 10 and 50)" << endl;
}
