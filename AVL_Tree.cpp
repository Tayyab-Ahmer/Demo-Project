
// https://www.guru99.com/avl-tree.html

#include <iostream>

// AVL tree node structure
struct AVLNode
{
    int key;
    AVLNode *left;
    AVLNode *right;
    int height;
};

// Function to get height of a node
int height(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

// Function to get balance factor of a node
int balanceFactor(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNode *leftLeftRotation(AVLNode *root);
AVLNode *rightRightRotation(AVLNode *root);
AVLNode *LeftRightRotation(AVLNode *root);
AVLNode *RightLeftRotation(AVLNode *root);
// Function to perform left-left rotation
AVLNode *insertNode(AVLNode *root, int key)
{
    // Perform standard BST insertion
    if (root == nullptr)
    {
        return new AVLNode{key, nullptr, nullptr, 1};
    }

    if (key < root->key)
    {
        root->left = insertNode(root->left, key);
    }
    else
    {
        root->right = insertNode(root->right, key);
    }

    // Update height of current node
    root->height = std::max(height(root->left), height(root->right)) + 1;

    // Check balance factor of current node
    int balance = balanceFactor(root);

    // If unbalanced, perform rotations to balance the tree
    if (balance > 1 && key < root->left->key)
    {
        // Left-left case
        return leftLeftRotation(root);
    }
    if (balance < -1 && key > root->right->key)
    {
        // Right-right case
        return rightRightRotation(root);
    }
    if (balance > 1 && key > root->left->key)
    {
        // Left-right case
        return LeftRightRotation(root);
    }
    if (balance < -1 && key < root->right->key)
    {
        // Right-left case
        return RightLeftRotation(root);
    }

    // Standard AVL tree rotations for other cases omitted for brevity

    // Return the (possibly modified) root of the subtree
    return root;
}

AVLNode *leftLeftRotation(AVLNode *node)
{
    AVLNode *leftSubtree = node->left;
    AVLNode *leftRightSubtree = leftSubtree->right;

    // Perform rotation
    leftSubtree->right = node;
    node->left = leftRightSubtree;

    // Update heights
    node->height = std::max(height(node->left), height(node->right)) + 1;
    leftSubtree->height = std::max(height(leftSubtree->left), height(leftSubtree->right)) + 1;

    // Return new root
    return leftSubtree;
}
// Function to perform right-right rotation
AVLNode *rightRightRotation(AVLNode *node)
{
    AVLNode *rightSubtree = node->right;
    AVLNode *rightLeftSubtree = rightSubtree->left;

    // Perform rotation
    rightSubtree->left = node;
    node->right = rightLeftSubtree;

    // Update heights
    node->height = std::max(height(node->left), height(node->right)) + 1;
    rightSubtree->height = std::max(height(rightSubtree->left), height(rightSubtree->right)) + 1;

    // Return new root
    return rightSubtree;
}

// Function to perform left-right rotation
AVLNode *LeftRightRotation(AVLNode *node)
{
    AVLNode *leftSubtree = node->left;
    AVLNode *leftRightSubtree = leftSubtree->right;

    // Perform rotations
    leftSubtree->right = leftRightSubtree->left;
    node->left = leftRightSubtree->right;
    leftRightSubtree->left = leftSubtree;
    leftRightSubtree->right = node;

    // Update heights
    node->height = std::max(height(node->left), height(node->right)) + 1;
    leftSubtree->height = std::max(height(leftSubtree->left), height(leftSubtree->right)) + 1;
    leftRightSubtree->height = std::max(height(leftRightSubtree->left), height(leftRightSubtree->right)) + 1;

    // Return new root
    return leftRightSubtree;
}
// Function to perform right-left rotation
AVLNode *RightLeftRotation(AVLNode *node)
{
    AVLNode *rightSubtree = node->right;
    AVLNode *rightLeftSubtree = rightSubtree->left;

    // Perform rotations
    rightSubtree->left = rightLeftSubtree->right;
    node->right = rightLeftSubtree->left;
    rightLeftSubtree->left = node;
    rightLeftSubtree->right = rightSubtree;

    // Update heights
    node->height = std::max(height(node->left), height(node->right)) + 1;
    rightSubtree->height = std::max(height(rightSubtree->left), height(rightSubtree->right)) + 1;
    rightLeftSubtree->height = std::max(height(rightLeftSubtree->left), height(rightLeftSubtree->right)) + 1;

    // Return new root
    return rightLeftSubtree;
}

void inOrder(AVLNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    std::cout << root->key << " ";
    inOrder(root->right);
}
// Driver program to test AVL tree implementation
int main()
{

    AVLNode *root = nullptr;

    root = insertNode(root, 10);
    root = insertNode(root, 5);
    root = insertNode(root, 4);
    root = insertNode(root, 3);
    root = insertNode(root, 2);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);
    root = insertNode(root, 25);

    // Print inorder traversal of the AVL tree
    // Expected output: 10 20 25 30 40 50
    inOrder(root);

    return 0;
}
