#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

// 定义栈
typedef struct {
    char data[MAX_SIZE];
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
int Push(Stack *s, char c) {
    if (s->top == MAX_SIZE - 1) {
        return 0; // 栈满
    }
    s->data[++s->top] = c;
    return 1;
}

// 弹栈
int Pop(Stack *s, char *c) {
    if (IsEmpty(s)) {
        return 0; // 栈空
    }
    *c = s->data[s->top--];
    return 1;
}

// 获取栈顶元素
int Peek(Stack *s, char *c) {
    if (IsEmpty(s)) {
        return 0; // 栈空
    }
    *c = s->data[s->top];
    return 1;
}

// 判断括号是否匹配
int IsMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

// 判断括号是否正确匹配
int IsValid(char *s) {
    Stack stack;
    InitStack(&stack);

    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            Push(&stack, c); // 左括号入栈
        } else if (c == ')' || c == ']' || c == '}') {
            char top;
            if (!Pop(&stack, &top) || !IsMatching(top, c)) {
                return 0; // 不匹配
            }
        }
    }

    return IsEmpty(&stack); // 栈为空则匹配成功
}

int main() {
    char input[MAX_SIZE];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // 去除换行符
    if (IsValid(input)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}