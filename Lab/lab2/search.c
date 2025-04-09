#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    int color;  // 0: blue, 1: red
};

struct TreeNode* newTreeNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    node->color = 0; // Initially blue
    return node;
}

struct TreeNode* constructTree(int size) {
    if (size == 0)
        return NULL;

    struct TreeNode** nodes = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));
    for (int i = 0; i < size; i++) {
        int val;
        scanf("%d", &val);
        if (val == -1) {
            nodes[i] = NULL;
        } else {
            nodes[i] = newTreeNode(val);
        }
    }

    for (int i = 0, j = 1; j < size; i++) {
        if (nodes[i] != NULL) {
            if (j < size)
                nodes[i]->left = nodes[j++];
            if (j < size)
                nodes[i]->right = nodes[j++];
        }
    }

    struct TreeNode* root = nodes[0];
    free(nodes);
    return root;
}

void dfs(struct TreeNode* root, int x, int y, int type) {
    if (root == NULL) return;

    // Check if the current node's value is within the [x, y] range
    if (root->val >= x && root->val <= y) {
        // Change the node's color according to the type
        root->color = type;
    }

    // Recursively traverse the left and right subtrees
    dfs(root->left, x, y, type);
    dfs(root->right, x, y, type);
}

void getNumber(struct TreeNode* root, int** ops, int opsSize) {
    // Perform each operation in sequence
    for (int i = 0; i < opsSize; i++) {
        int type = ops[i][0];
        int x = ops[i][1];
        int y = ops[i][2];

        // Perform DFS on the tree, coloring nodes according to the operation
        dfs(root, x, y, type);
    }

    // Count the number of red nodes
    int redCount = 0;
    // Traverse the tree and count the red nodes
    dfsCountRed(root, &redCount);
    printf("%d\n", redCount);
}

void dfsCountRed(struct TreeNode* root, int* redCount) {
    if (root == NULL) return;
    
    if (root->color == 1) {  // Red
        (*redCount)++;
    }

    // Continue traversing the left and right subtrees
    dfsCountRed(root->left, redCount);
    dfsCountRed(root->right, redCount);
}

void readOps(int ***ops, int *opsSize) {
    scanf("%d", opsSize);

    *ops = (int **)malloc(*opsSize * sizeof(int *));
    while(getchar() != '[') {}
    for (int i = 0; i < *opsSize; i++) {
        (*ops)[i] = (int *)malloc(3 * sizeof(int));
        while(getchar() != '[') {}
        for (int j = 0; j < 3; j++) {
            scanf("%d", &((*ops)[i][j]));
        }
        while(getchar() != ']') {}
    }
}

int main() {
    int nodeSize;
    scanf("%d", &nodeSize);
    struct TreeNode* root = constructTree(nodeSize);
    int **ops, opsSize;
    readOps(&ops, &opsSize);
    getNumber(root, ops, opsSize);

    return 0;
}
