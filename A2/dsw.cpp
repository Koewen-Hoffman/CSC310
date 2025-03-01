#include "dsw.h"

// ----------------------- Private -------------------------------- 

void BST::rotateRight(Node*& node) {
    if (node == nullptr || node->left == nullptr) 
        return;

    Node* leftChild = node->left;   // get the node to rotate (left child of parent)
    node->left = leftChild->right; // nodes right child gets adopted as parents left child
    leftChild->right = node;       // parent becomes right child of node
    node = leftChild;              // replace parent by node
}


void BST::rotateLeft(Node*& node) {
    if (node == nullptr || node->right == nullptr) 
        return;

    Node* rightChild = node->right;  // get the node to rotate (right child of parent)
    node->right = rightChild->left;  // nodes left child gets adopted as parents right child 
    rightChild->left = node;         // parent becomes left child of node   
    node = rightChild;               // replace parent by node
}

// TODO: Fix phase 1 - Im not sure id this is what its supposed to look like or not
void BST::createVine() {
    if (root == nullptr) 
        return;

    Node* grandparent = nullptr;
    Node* parent = root;
    Node* child = root->right; // Instead of left, start with the right

    while (parent != nullptr) 
    {
        if (child != nullptr)
        {
            // Check if the subtree is smaller than 2 nodes
            if(subtreeSize(child) > 2){
                rotateRight(parent);
                if (grandparent == nullptr)
                    root = parent;
                else
                    // Update the grandparents left child
                    grandparent->left = parent;
            }

            grandparent = parent;
            parent = child;
            child = parent->right;
        } else {
            grandparent = parent;
            // Instead of moving right, move left
            parent = parent->left;
            if (parent != nullptr)
                // Switch this one to the right
                child = parent->right;
        }
    }
}

// MARK: Extra function used to skip rotateions on small subtrees
int BST::subtreeSize(Node* node){
    if(node == nullptr)
        return 0;
    // Return the size of the subtree at the given node
    return 1 + subtreeSize(node->left) + subtreeSize(node->right);
}

// TODO: Change phase 2
// Ok this one was tough, it took a lot of tweaking
// This makes to program crash, and I'm unsure as to why it does this
void BST::rebuildTree(int size) {
    // Use ceil to round up to the traget height
    int targetHeight = ceil(2 * log2(size));

    // Calculate initial right rotations
    int rightRotations = size - targetHeight; 
    performRotations(rightRotations); 

    // Do left rotations in decreasing powers of 2
    for (int i = rightRotations / 2; i > 0; i /= 2) {
        performRotations(i); 
    }
}

// Perform left rotations on every second node
void BST::performRotations(int count) {
    Node* grandparent = nullptr;
    Node* parent = root;
    Node* child = root->right;

    for (int i = 0; i < count; i++) {
        if (child == nullptr) 
            break;

        rotateLeft(parent);
        if (grandparent == nullptr)
            root = parent;
        else
            grandparent->right = parent;

        grandparent = parent;
        parent = parent->right;
        if (parent != nullptr)
            child = parent->right;
    }
}

void BST::printTree(Node* root, int space) {
    const int COUNT = 10;

    if (root == nullptr) {
        return;
    }

    space += COUNT;

    // Print the right child first
    printTree(root->right, space);

    // Print current node
    for (int i = COUNT; i < space; i++) {
        cout << " ";
    }
    cout << root->data << endl;

    // Print left child
    printTree(root->left, space);
}

// ------------------- Public ---------------------------------

BST::BST() {
    root = nullptr;
}

BST::~BST() {
   deleteTree(root);
}

void BST::deleteTree(Node* node) {
    if (node == nullptr) 
        return;

   deleteTree(node->left);
   deleteTree(node->right);

   delete node;
}


void BST::insert(int val) {
   Node* newNode = new Node(val);
   if (root == nullptr) {
       root = newNode;
       return;
   }

   Node* curr = root;
   Node* parent = nullptr;

   while (curr != nullptr) {
       parent = curr;
       if (val < curr->data)
           curr = curr->left;
       else
           curr = curr->right;
   }

   if (val < parent->data)
       parent->left = newNode;
   else
       parent->right = newNode;
}

void BST::dswBalance() {
   if (root == nullptr) 
       return;

   // Step 1: Flatten tree into vine
   createVine();

   // Print vine
   cout << "After Phase 1:";
   display();

   // Step 2: Count the number of nodes
   int size = 0;
   Node* temp = root;
   while (temp != nullptr) {
       size++;
       temp = temp->right;
   }

   // Step 3: Rebuild tree to balance it
   rebuildTree(size);
}

void BST::display() {
   cout << endl;
   printTree(root, 0);
   cout << endl;
}