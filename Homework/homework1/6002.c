#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 1000

// 定义栈
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void InitStack(Stack *s) {
    s->top = -1;
}

// 判断栈是否为空
int IsEmpty(Stack *s) {
    return s->top == -1;
}

// 压栈
int Push(Stack *s, int e) {
    if (s->top == MAX_SIZE - 1) {
        return 0; // 栈满
    }
    s->data[++s->top] = e;
    return 1;
}

// 弹栈
int Pop(Stack *s, int *e) {
    if (IsEmpty(s)) {
        return 0; // 栈空
    }
    *e = s->data[s->top--];
    return 1;
}

// 获取栈顶元素
int Peek(Stack *s, int *e) {
    if (IsEmpty(s)) {
        return 0; // 栈空
    }
    *e = s->data[s->top];
    return 1;
}

int ComputeRPN(int n) {
    Stack s;
    InitStack(&s);

    char token[20];
    int num;

    for (int i = 0; i < n; i++) {
        scanf("%s", token);

        if (isdigit(token[0])) {  // 如果是数字
            num = atoi(token);     // 转换为整数
            Push(&s, num);         // 压栈
        } else {  // 如果是运算符
            int a, b;
            Pop(&s, &b);  // 弹出两个数
            Pop(&s, &a);

            int result;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default: 
                    printf("未知运算符\n");
                    return 0;
            }
            Push(&s, result);  // 压入计算结果
        }
    }

    int final_result;
    if (Pop(&s, &final_result) && IsEmpty(&s)) {
        return final_result;  // 返回最终结果
    } else {
        printf("表达式错误\n");
        return 0;
    }
}

int main() {
    int n;
    scanf("%d", &n);  // 输入字符串个数

    int result = ComputeRPN(n);
    printf("%d\n", result);

    return 0;
}