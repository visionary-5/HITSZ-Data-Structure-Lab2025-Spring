#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    // 设置初始指针位置为右上角
    int row = 0;                 // 第一行
    int col = matrixColSize - 1; // 最后一列
    
    // 当指针在矩阵范围内时继续搜索
    while (row < matrixRowSize && col >= 0) {
        // 找到目标值
        if (matrix[row][col] == target) {
            return true;
        } 
        // 当前值大于目标值，排除当前列
        else if (matrix[row][col] > target) {
            col--; // 向左移动
        } 
        // 当前值小于目标值，排除当前行
        else {
            row++; // 向下移动
        }
    }
    
    // 搜索完所有可能位置仍未找到
    return false;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    // 动态分配二维数组
    int** matrix = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    int K;
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        int target;
        scanf("%d", &target);
        
        bool found = searchMatrix(matrix, m, n, target);
        printf("%s\n", found ? "true" : "false");
    }
    
    // 释放内存
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}