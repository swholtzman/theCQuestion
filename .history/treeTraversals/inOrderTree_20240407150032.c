#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* inOrder(struct TreeNode* root, int* arr, int* index) {
    if (root == NULL) 
        return arr;
    
    // left
    arr = inOrder(root -> left, arr, index);

    // visit
    arr[(*index)++] = root -> val;

    // right
    arr = inOrder(root -> right, arr, index);

    return arr;
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int *arr = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;

    arr = inOrder(root, arr, returnSize);

    return arr;
}