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

int* postOrder(struct TreeNode* root, int* arr, int* index) {
    if (root == NULL) {
        return arr;
    }

    arr = postOrder(root -> left, arr, index);
    arr = postOrder(root -> right, arr, index);
    arr[(*index)++] = root -> val;

    return arr;
}

int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int* arr = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;

    arr = postOrder(root, arr, returnSize);
    return arr;
}