#include <stdio.h>
#include <stdlib.h>

int main() {
    int num, ist;
    scanf("%d", &num);

    int* arr = malloc((num + 1) * sizeof(int));
    for (int i = 0; i < num; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &ist);

    int idx = 0;
    while (idx < num && arr[idx] < ist) idx++; // 找到插入位置

    // 直接从后往前移动元素
    for (int k = num; k > idx; k--) {
        arr[k] = arr[k - 1];
    }
    arr[idx] = ist;  // 插入元素

    // 统一处理输出格式
    for (int i = 0; i <= num; i++) {
        printf("%d%c", arr[i], i == num ? '\n' : ' ');
    }

    free(arr);
    return 0;
}