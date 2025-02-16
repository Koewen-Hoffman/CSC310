#include "splay.h"
#include "Includes/customErrorClass.h"

SplayTree::SplayTree() 
{
    root = nullptr; 
}

// aka Zig
SplayTree::Node* SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// aka Zag
SplayTree::Node* SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayTree::Node* SplayTree::splay(Node* root, int key) {
    // First check if the tree is empty or if the key is already at the top
    if(root == nullptr){
        // This is the only place I can see an obvious use of exception handling.
        throw CustomException("Nothing can be splayed!");
    }

    if(root->key == key){
        return root;
    }

    if(key < root->key){
        // Key is not in the tree
        if(root->left == nullptr){
            return root;
        }

        // Check to see what rotations we need to make
        if(key < root->left->key){
            // Zig
            root->left->left = splay(root->left->left, key);
            // Performa right rotation
            root = rotateRight(root);
        } else if(key > root->left->key){
            root->left->right = splay(root->left->right, key);

            // Make sure the rightmost node is not null
            if(root->left->right != nullptr){
                // Perform a left rotation
                root->left = rotateLeft(root->left);
            }
        }

        // Make sure the left node is not null
        if(root->left != nullptr){
            // Rotate right
            root = rotateRight(root);
        }

        return root;
    } else {
        if (root->right == nullptr) {
            return root;
        }

        if (key < root->right->key) {
            // Zag
            root->right->left = splay(root->right->left, key);

            // Make sure the leftmost node is not null
            if (root->right->left != nullptr){
                // Rotate right
                root->right = rotateRight(root->right); 
            }
        } else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            // Rotate left
            root = rotateLeft(root);
        }

        root = rotateLeft(root);
        return root;
    }
}

SplayTree::Node* SplayTree::insertNode(Node* root, int key) {
    // Create a new node with the given key
    Node* newNode = new Node(key);

    // First check if the tree is empty
    if(root == nullptr){
        // If the root is empty, set the root to the new inserted node
        root = newNode;
        return root;
    }

    // Strore the current and parent nodes for crawling
    Node* current = root;
    Node* parent = nullptr;

    // Crawl the nodes to find the correct insertion point
    while(current != nullptr){
        // Travel down the tree
        parent = current;

        if(key < current->key){
            // If the key is less than the current, go down the left branch
            current = current->left;
        } else if (key > current->key){
            // If the ley is greater than the current, go down the right branch
            current = current->right;
        } else {
            // Oops, key already exists :)
            // Send this guy into the aether
            delete newNode; // Demolish
            return root;
        }
    }

    // Insert the new node as a child to either side of the parent
    if(key < parent->key){
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    root = splay(root, key); // Splay the inserted node
    return root;
}

SplayTree::Node* SplayTree::deleteNode(Node* root, int key) {
    // First check if the tree is empty
    if(root == nullptr){
        return root;
    }

    if(root->left == nullptr){
        // If the left branch is empty, there is 1 or no right branch
        Node* temp = root;
        root = root->right;
        delete temp; // Obliterate
    } else if(root->right == nullptr){
        // If the right branch is empty, there is 1 o no left branch
        Node* temp = root;
        root = root->right;
        delete temp; // Disintegrate
    } else {
        // Both branches are present
        // Find the larger node
        Node* larger = root->right;
        // Keep going as long as the branch has elements
        while(larger->left != nullptr){
            larger = larger->left;
        }

        // Use this to splay the nodes after deletion
        root = splay(root, larger->key);

        // Replace this node with the left most
        root->left = root->left->left;

        delete root->left; // Reduce to atoms
    }

    // Then return the root, definitly no memory destruction going on here :)
    return root;
}

void SplayTree::insert(int key) {
    root = insertNode(root, key);
}

void SplayTree::remove(int key) {
    root = deleteNode(root, key);
}

bool SplayTree::search(int key) {
    root = splay(root, key);
    return (root && root->key == key);
}

void SplayTree::printTree(Node* root, int space) {
    const int COUNT = 10; 

    if (root == nullptr) {
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->right, space);

    // Print the current node after right child

    for (int i = COUNT; i < space; i++) {
        cout << " "; // Indentation for tree depth
    }
    cout << root->key << endl;

    // Print the left child
    printTree(root->left, space);
}

void SplayTree::display() {
    printTree(root, 0);
    cout << endl;
}