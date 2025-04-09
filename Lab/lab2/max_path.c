#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN -1000
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

TreeNode* buildTree(char** input, int n) {
    if (n == 0 || strcmp(input[0], "null")== 0) return NULL;

    TreeNode** queue = (TreeNode**)malloc(n * sizeof(TreeNode*));
    TreeNode* root = newNode(atoi(input[0]));
    queue[0] = root;
    int front = 0, rear = 1;

    for (int i = 1; i < n; i += 2) {
        TreeNode* current = queue[front++];

        if (strcmp(input[i], "null")!= 0) {
            current->left = newNode(atoi(input[i]));
            queue[rear++] = current->left;
        }

        if (i + 1 < n && strcmp(input[i + 1], "null")!= 0) {
            current->right = newNode(atoi(input[i + 1]));
            queue[rear++] = current->right;
        }
    }

    free(queue);
    return root;
}

//recursion and compute the max_sum
int helper(TreeNode* node, int* max_sum) {
    if (node == NULL) return 0;

    int left_gain = helper(node->left, max_sum);
    left_gain = left_gain > 0 ? left_gain : 0;

    int right_gain = helper(node->right, max_sum);
    right_gain = right_gain > 0 ? right_gain : 0;

    int current_sum = node->val + left_gain + right_gain;
    if (current_sum > *max_sum) {
        *max_sum = current_sum;
    }

    int contribution = node->val + (left_gain > right_gain ? left_gain : right_gain);
    return contribution > 0 ? contribution : 0;
}

int maxPathSum(TreeNode* root) {
    int max_sum = MIN;
    helper(root, &max_sum);
    return max_sum;
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    char input[1000];
    fgets(input, sizeof(input), stdin);
    char* token = strtok(input, " \n");
    char* inputs[100];
    int n = 0;
    while (token != NULL) {
        inputs[n++] = token;
        token = strtok(NULL, " \n");
    }
    TreeNode* root = buildTree(inputs, n);

    int result = maxPathSum(root);
    printf("%d\n", result);

    freeTree(root);

    return 0;
}