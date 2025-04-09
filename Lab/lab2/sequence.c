#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }

    int rootVal = preorder[0];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = rootVal;
    root->left = root->right = NULL;

    int rootIndexInInorder = 0;
    for (int i = 0; i < inorderSize; i++) {
         if (inorder[i] == rootVal) {
             rootIndexInInorder = i;
             break;
         }
    }

    int leftSize = rootIndexInInorder; 
    int rightSize = inorderSize - rootIndexInInorder - 1;
    
    root->left = buildTree(preorder + 1, leftSize, inorder, leftSize);
    root->right = buildTree(preorder + 1 + leftSize, rightSize, inorder + leftSize + 1, rightSize);
    return root;
}

void printTree(struct TreeNode* root) {
    int front, rear;
    int index;
    TreeNode *node;
    TreeNode **queue;
    TreeNode **arr;

    //assist queue
    queue = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_SIZE);
    front = 0; rear = 0;
    queue[rear++] = root;
    arr = (TreeNode **)malloc(sizeof(TreeNode *) * MAX_SIZE);
    index = 0;
    while (front < rear)
    {
        node = queue[front++];
        if (node != NULL) {
            arr[index++] = node;  // Store the value of the node
            // Enqueue the left child (if exists)
            queue[rear++] = node->left;
            // Enqueue the right child (if exists)
            queue[rear++] = node->right;
        } else {
            arr[index++] = NULL; // Use NULL pointer to represent the null node
        }
    }
    
    for (int i = 0; i < index; i++) {
        if (arr[i] == NULL) {
            printf("null "); // Print 'null' for NULL
        } else {
            printf("%d ", arr[i]->val);
        }
    }

    free(queue);
    free(arr);
}

int main() {
    int preorderSize;
    scanf("%d", &preorderSize);
    int* preorder = (int*)malloc(preorderSize * sizeof(int));
    for (int i = 0; i < preorderSize; i++) {
        scanf("%d", &preorder[i]);
    }

    int inorderSize = preorderSize;
    int* inorder = (int*)malloc(inorderSize * sizeof(int));
    for (int i = 0; i < inorderSize; i++) {
        scanf("%d", &inorder[i]);
    }

    struct TreeNode* root = buildTree(preorder, preorderSize, inorder, inorderSize);
    printTree(root);

    return 0;
}