#include <stdio.h>
#include <string.h>

int main() {
    char A[80], B[80];

    // 输入字符串 A 和 B
    fgets(A, sizeof(A), stdin);
    A[strcspn(A, "\n")] = '\0'; // 去除换行符

    fgets(B, sizeof(B), stdin);
    B[strcspn(B, "\n")] = '\0'; // 去除换行符

    // 判断 B 是否是 A 的子串
    if (strstr(A, B) != NULL) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}