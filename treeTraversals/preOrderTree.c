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

int* preOrder(struct TreeNode* root, int* arr, int* index) {
    if (root == NULL) {
        return arr;
    }

    arr[(*index)++] = root -> val;
    arr = preOrder(root -> left, arr, index);
    arr = preOrder(root -> right, arr, index);

    return arr;
}
int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    
    int* arr = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;

    arr = preOrder(root, arr, returnSize);

    return arr;
}