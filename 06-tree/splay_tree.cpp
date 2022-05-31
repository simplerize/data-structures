/**
 * C++ example to demonstrate the Splay Tree
 */
#include <iostream>
#include <queue>
using namespace std;

// Tree node representation
struct Node
{
    int data;     // Actual data
    Node* left;   // Pointer to left child
    Node* right;  // Pointer to right child
    Node* parent; // Pointer to parent node

    // Node constructor
    Node(int d, Node* pp) : data(d), left(NULL), right(NULL), parent(pp)
    {}
};

/**
 * Splay Tree implementation
 */
class SplayTree
{
    // The root node
    Node* root;

public:
    // Constructor
    SplayTree() : root(NULL)
    {}

    // Insert a new node
    void insert(int data);

    // Delete the node by the given data
    void remove(int data);

    // Search the node by the given data
    Node* search(int data);
    
    // Preorder traversal
    void preorder() {
        preorder(root);
    }

private:
    // Splay the tree by the given node
    void splay(Node* x);
    // Perform zag rotation of the given node
    void left_rotate(Node* p);
    // Perform zig rotation of the given node
    void right_rotate(Node* p);
    // Traverse the tree in preorder
    void preorder(Node* p);
};

// Splay the tree by a given node
void SplayTree::splay(Node* x)
{
    while (x->parent != NULL) {
        if (x->parent->parent == NULL) {
            // Node has only parent and not grantparent
            if (x == x->parent->left) {
                // Node is on left: perform right rotation 
                //      p           x
                //     /     =>      \
                //    x               p
                right_rotate(x->parent);
            } else {
                // Node is on right: perform left rotation 
                //    p               x
                //     \     =>      /
                //      x           p
                left_rotate(x->parent);
            }

        } else {
            // Node has parent and grandparent
            Node* parent = x->parent;
            Node* grandpa = x->parent->parent;
            if (x == parent->left && parent == grandpa->left) {
                // Zig zig rotation: Rotate grantparent first for better balance
                //        g          p          x
                //       /          / \          \
                //      p     =>   x   g   =>     p
                //     /                           \
                //    x                             g
                right_rotate(x->parent->parent);
                right_rotate(x->parent);
            } else if (x == parent->right && parent == grandpa->right) {
                // Zag zag rotation: Rotate grantparent first for better balance
                //    g              p              x
                //     \            / \            /
                //      p     =>   g   x   =>     p
                //       \                       /
                //        x                     g
                left_rotate(x->parent->parent);
                left_rotate(x->parent);
            } else if (x == parent->left && parent == grandpa->right) {
                // Zig zag rotation: Rotate parent first because rotating the
                // grantparent first would change the position of the node
                //    g            g              x
                //     \            \            / \
                //      p     =>     x     =>   g   p
                //     /              \
                //    x                p
                right_rotate(x->parent);
                left_rotate(x->parent);
            } else {
                // Zag zig rotation: Rotate parent first because rotating the
                // grantparent first would change the position of the node
                //      g          g              x
                //     /            \            /
                //    p       =>     x     =>   g
                //     \            /            \
                //      x          p              p
                left_rotate(x->parent);
                right_rotate(x->parent);
            }
        }
    }

    // Make the splay node as root
    root = x;
}

// Perform zag (left) rotation of the given node
void SplayTree::left_rotate(Node* p)
{
    // Pull up the right side node on top
    Node* top = p->right;
    top->parent = p->parent;
    if (top->parent != NULL) {
        if (p == p->parent->left) {
            p->parent->left = top;
        } else {
            p->parent->right = top;
        }
    }

    // Link the left subtree to right of the target node p
    p->right = top->left;
    if (p->right) {
        p->right->parent = p;
    }

    // Pull down the target node p to left
    top->left = p;
    top->left->parent = top;
}

// Perform zig rotation of the given node
void SplayTree::right_rotate(Node* p)
{
    // Pull up the left side node on top
    Node* top = p->left;
    top->parent = p->parent;
    if (top->parent != NULL) {
        if (p == p->parent->left) {
            p->parent->left = top;
        } else {
            p->parent->right = top;
        }
    }

    // Link the right subtree to left of the target node p
    p->left = top->right;
    if (p->left) {
        p->left->parent = p;
    }

    // Pull down the target node p to right
    top->right = p;
    top->right->parent = top;
}

// Insert a new node
void SplayTree::insert(int data)
{
    if (root == NULL) {
        // Insert the first node as root and return
        root = new Node(data, NULL);
        return;
    }

    Node* p = root;
    Node* pp = NULL;
    // Traverse the tree from the root
    while (1) {
        pp = p;
        if (data < p->data) {
            // Traverse the left subtree if the data is smaller
            p = p->left;
            if (p == NULL) {
                // Insert the node on left and stop the traversal
                p = new Node(data, pp);
                pp->left = p;
                break;
            }
        } else {
            // Traverse the right subtree if the data is greater
            p = p->right;
            if (p == NULL) {
                // Insert the node on right and stop the traversal
                p = new Node(data, pp);
                pp->right = p;
                break;
            }
        }
    }

    // Splay the tree to make the new node as root
    splay(p);
}

// Delete the node by the given data
void SplayTree::remove(int data)
{
    if (root == NULL) {
        // Return if the tree is empty
        return;
    }

    // Traverse the tree and find the node
    Node* p = root;
    while(1) {
        if (data < p->data && p->left != NULL) {
            // Search on the left subtree for smaller elements.
            p = p->left;

        } else if (data > p->data && p->right != NULL) {
            // Search on the right subtree for greater elements.
            p = p->right;

        } else {
            // Found element
            break;
        }
    }

    // Splay the target node or the last node as root
    splay(p);

    if (data == p->data) {
        // Delete the root node and the make it as two subtrees
        Node* left_subtree = p->left;
        Node* right_subtree = p->right;
        delete p;

        // Node has either no child or one child
        if (left_subtree != NULL && right_subtree != NULL) {
            // Node has both left and right child.
            // Find the smallest node on its right subtree (inorder successor)
            Node* min;
            for (min = right_subtree; min->left != NULL; min = min->left)
                ;

            // Splay the inorder success node to bring it as root of the right subtree
            right_subtree->parent = NULL;
            splay(min);

            // Make it as root and link left subtree on its left
            root = min;
            root->left = left_subtree;
            left_subtree->parent = root;

        } else if (left_subtree == NULL) {
            // The right child becomes root if left is NULL
            root = right_subtree;
            right_subtree->parent = NULL;

        } else {
            // The left child becomes root if right is NULL
            root = left_subtree;
            left_subtree->parent = NULL;
        }
    }
}

// Search the node by the given data
Node* SplayTree::search(int data)
{
    if (root == NULL) {
        // Return if the tree is empty
        return NULL;
    }

    Node* p = root;
    while(1) {
        if (data < p->data && p->left != NULL) {
            // Search on the left subtree for smaller elements.
            p = p->left;

        } else if (data > p->data && p->right != NULL) {
            // Search on the right subtree for greater elements.
            p = p->right;

        } else {
            // Found element
            break;
        }
    }

    // Always splay the tree either with target or the last node
    splay(p);

    // Return the node if found, NULL otherwise
    return (data == p->data)? p : NULL;
}

// Traverse the tree in preorder (parent, left, right)
void SplayTree::preorder(Node* p)
{
    if (p != NULL) {
        cout << p->data << endl;
        preorder(p->left);
        preorder(p->right);
    }
}

int main()
{
    // Create a Splay tree and insert data
    SplayTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(60);
    tree.insert(40);
    tree.insert(50);
    tree.insert(30);
    cout << "Tree after inserting 20, 10, 60, 40, 50, and 30" << endl;
    tree.preorder();

    // Delete data
    tree.remove(60);
    tree.remove(30);
    cout << "Tree after removing 60 and 30" << endl;
    tree.preorder();

    // Search
    Node* p = tree.search(20);
    if (p != NULL) {
        cout << "search(20) located node: " << p->data << endl;
    }
    cout << "Tree after searching 20" << endl;
    tree.preorder();
}
