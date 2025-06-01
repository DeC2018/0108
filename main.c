#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10000

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Recursive function to build height-balanced BST
struct TreeNode* ConvToBST(int *nums, int beg, int end){
    if(end < beg)
        return NULL;
    int mid = (beg + end) / 2;
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = nums[mid];
    root->left = ConvToBST(nums, beg, mid - 1);
    root->right = ConvToBST(nums, mid + 1, end);
    return root;
}

struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    if(numsSize <= 0)
        return NULL;
    else
        return ConvToBST(nums, 0, numsSize - 1);
}

// Helper to parse input string like "[-10,-3,0,5,9]" into array
int parseInput(const char* s, int* arr) {
    int n = 0;
    int i = 0, sign = 1, num = 0, inNum = 0;
    while (s[i]) {
        if (s[i] == '-' || (s[i] >= '0' && s[i] <= '9')) {
            sign = 1;
            if (s[i] == '-') {
                sign = -1;
                ++i;
            }
            num = 0;
            inNum = 0;
            while (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
                ++i;
                inNum = 1;
            }
            if (inNum) arr[n++] = num * sign;
        } else {
            ++i;
        }
    }
    return n;
}

// Helper to print tree in level order (as per example output)
void printTree(struct TreeNode* root) {
    if (!root) {
        printf("[]\n");
        return;
    }
    struct TreeNode* queue[MAX_NODES];
    int front = 0, rear = 0;
    char* res[MAX_NODES];
    int res_len = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct TreeNode* node = queue[front++];
        if (node) {
            char* buf = (char*)malloc(16);
            sprintf(buf, "%d", node->val);
            res[res_len++] = buf;
            queue[rear++] = node->left;
            queue[rear++] = node->right;
        } else {
            res[res_len++] = strdup("null");
        }
    }
    // Remove trailing "null"s
    while (res_len > 0 && strcmp(res[res_len-1], "null") == 0)
        res_len--;
    printf("[");
    for (int i = 0; i < res_len; ++i) {
        if (i) printf(",");
        printf("%s", res[i]);
        free(res[i]);
    }
    printf("]\n");
}

// Helper to free the memory of a tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main() {
    const char* inputs[] = {
        "[-10,-3,0,5,9]",
        "[1,3]"
    };
    int num_cases = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: nums = %s\n", inputs[i]);
        int nums[MAX_NODES];
        int numsSize = parseInput(inputs[i], nums);
        struct TreeNode* root = sortedArrayToBST(nums, numsSize);
        printf("Output: ");
        printTree(root);
        deleteTree(root);
    }
    return 0;
}
