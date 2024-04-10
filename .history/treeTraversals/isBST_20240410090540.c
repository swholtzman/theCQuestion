// given a binary tree with a root node, return 1 if it is BST, 0 otherwise
#include <stdio.h>
#include <stdlib.h>

#define INT_MIN
#define INT_MAX

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int 

int isBST(struct TreeNode* node) {
    if (node == NULL) {
        return;
    }
    if (node -> left > node ->right) {
        return 0;
    } else if (node -> right < node->left) {
        return 0;
    }

    if (node->right == NULL && node->left ==NULL) {
        return 1;
    }

    return isBST(node->right) && isBST(node->left);

}