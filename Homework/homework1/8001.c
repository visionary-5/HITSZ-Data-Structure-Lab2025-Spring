#include <stdio.h>
#include <string.h>

// 辅助函数：反转字符串的指定部分
void reverse(char *s, int start, int end) {
    while (start < end) {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

// 主函数：按规则反转字符串
void reverseStr(char *s, int k) {
    int len = strlen(s);

    for (int i = 0; i < len; i += 2 * k) {
        // 反转前 k 个字符
        if (i + k <= len) {
            reverse(s, i, i + k - 1);
        } else {
            // 剩余字符少于 k 个，全部反转
            reverse(s, i, len - 1);
        }
    }
}

int main() {
    char s[1000];
    int k;

    // 输入字符串和整数 k
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0'; // 去除换行符

    scanf("%d", &k);

    // 按规则反转字符串
    reverseStr(s, k);

    // 输出结果
    printf("%s\n", s);

    return 0;
}