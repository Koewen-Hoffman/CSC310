#include "bstP.h"
#include "customErrorClass.h"

// MARK: Most of this code I had salvaged from the projects we did in CSC300, and they work.
node::node(int value){
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST(){
    root = nullptr;
}

BST::~BST(){
    // deleteNode
    clearTree(root);
}

// From starter
void BST::printTree(node* root, int space) {
    const int COUNT = 10; 

    if (root == nullptr) {
        // Exception for an empty tree
        if(BST::root == nullptr){
            throw CustomException("The tree is empty!");
        }
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->rightChild, space);

    // Print the current node after right child

    for (int i = COUNT; i < space; i++) {
        cout << " "; // Indentation for tree depth
    }
    cout << root->data << endl;

    // Print the left child
    printTree(root->leftChild, space);
}

// Salvaged
void BST::clearTree(node* node){
    if(node == nullptr){
        // Exception for an empty tree
        if(BST::root == nullptr){
            throw CustomException("The tree is empty!");
        }
        return;
    }

    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

// Salvaged
// Function to insert a node
void BST::insertNode(node*& root, int data){
    // Check to make sure the tree is not empty and insert the initial node
    if(root == nullptr){
        root = new node(data);
        return;
    }

    if(data != root->data){
        if(data < root->data)
            insertNode(root->leftChild, data);
        else
            insertNode(root->rightChild, data);
    } else {
        // Duplicate value was found - exception
        throw CustomException("Duplace value cannot be added!");
    }
}

// Salvaged
node* BST::searchNode(node*& root, int data){
    if(root == nullptr){
        cout << data << " was not found" << endl;
        return nullptr;
    }

    if(root->data == data){
        cout << data << " was found" << endl;
        return root;
    }

    if(data < root->data)
        return searchNode(root->leftChild, data);
    else
        return searchNode(root->rightChild, data);
}

// Ok, this function took a while to make, and get to work correctly
// Only thing I had to work off of was the array implementation from CSC300
void BST::deleteNode(node*& root, int data){
    // Check if the tree is empty
    if(root == nullptr){
        // Exception for an empty tree
        if(BST::root == nullptr){
            throw CustomException("The tree is empty!");
        }
        return;
    }

    // Find the highest probability as to where the node is based on tree structure
    if(data < root->data){
        // If the data given is smaller than the root, go left
        deleteNode(root->leftChild, data);
    } else if (data > root->data) {
        // If the data given is larger than the root, go right
        deleteNode(root->rightChild, data);
    } else {
        // Else means that the data to delete was found

        // Now, make checks to replace the parent with a child, if the parent has children
        if(root->leftChild == nullptr){
            // If the left child is null, use the right child to replace node
            node* temp = root->rightChild;
            delete root;
            root = temp;
        } else if (root->rightChild == nullptr){
            // If the right child is null, use the left child to replace parent
            node* temp = root->leftChild;
            delete root;
            root = temp;
        } else {
            // If both children exist, find the successor or the higher value and replace the parent
            node* temp = root->rightChild;
            // As long as the left point is not null, find the higher value
            while (temp->leftChild != nullptr){
                temp = temp->leftChild;
            }
            
            // Delete the found node recusrively
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }

    return;
}

// Salvaged
void BST::preorder(node* root){
    if(root == nullptr){
        // Exception for an empty tree
        if(BST::root == nullptr){
            throw CustomException("The tree is empty!");
        }
        return;
    }
    
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::inorder(node* root){
    // First check if the tree is empty
    if(root == nullptr){
        // Exception for an empty tree
        if(BST::root == nullptr){
            throw CustomException("The tree is empty!");
        }
        return;
    }

    // Recursively call inorder to get all of the elements in the tree
    inorder(root->leftChild);
    // Print the current node and add it to the printed list
    cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root){
    // Check if the tree is empty
    if(root == nullptr){
        if(BST::root == nullptr){
            throw CustomException("The tree is empty!");
        }
        return;
    }

    // Recursively call inorder to get all of the elements in the tree
    postorder(root->leftChild);
    postorder(root->rightChild);
    // Print the current node and add it to the printed list
    cout << root->data << " ";
}

// Recursively find the height of a node
// In not sure how to test this without using a function like is balanced, as is balanced needs to use this function
int BST::height(node* node){
    // Check if the tree is empty
    if(node == nullptr){
        // Exception for an empty tree
        if(BST::root == nullptr){
            throw CustomException("The tree is empty!");
        }
        return 0;
    }

    // Call height again on both branches to see how deep the tree goes
    int left = height(node->leftChild);
    int right = height(node->rightChild);

    // Return the updated hight based on the largest branch
    if(left > right){
        return left + 1;
    } else {
        return right + 1;
    }
}

bool BST::isBalanced(node* root)
{
    // First check if the tree is empty
    if(root == nullptr){
        // No need for an eception as we have a desired result
        return true; // After all, and emoty tree is technically balanced
    }

    // We need to use our height function to find balance through every subtree
    int left = height(root->leftChild);
    int right = height(root->rightChild);

    // The height of subtrees is used to check for balance
    if(left - right <= 1 && right - left <= 1 && isBalanced(root->leftChild) && isBalanced(root->rightChild)) {
        // Both subtrees need to have the same height to be balanced
        return true;
    }

    // If anything else fails, it is not balanced
    return false;
}