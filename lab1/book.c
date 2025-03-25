#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义图书信息结构体
typedef struct {
    char bookId[20]; // 书号
    char title[100]; // 书名
    char author[50]; // 作者
    int stock;       // 库存数量
} Book;

// 定义链表节点结构体
typedef struct Node {
    Book book;
    struct Node *next;
} Node;

// 创建新节点
Node* CreateNode(Book book) {
    Node *node;
    node = (Node *) malloc(sizeof(Node));
    node->book = book;
    node->next = NULL;
    return node;
}

// 在链表尾部插入图书信息
void InsertBook(Node **head, Book book) {
    Node* newNode = CreateNode(book);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node* temp = *head;
        while(temp->next != NULL )
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// 根据书号删除图书信息
int DeleteBook(Node **head, char bookId[]) {
    if(*head == NULL)
        return 0;
    Node *temp = *head;
    Node *prev = NULL;
    if (strcmp(temp->book.bookId, bookId) == 0) {
        *head = temp->next;  
        free(temp);          
        return 1;            
    }
    while (temp != NULL && strcmp(temp->book.bookId, bookId) != 0 )
    {
        prev = temp;
        temp = temp->next;
    }    
    if(temp == NULL)
        return 0;   
    prev->next = temp->next;
    free(temp);
    return 1;
}

// 根据书号修改图书库存数量
int UpdateStock(Node *head, char bookId[], int newStock) {
    if (head == NULL)
    {
        return 0;
    }

    while (head != NULL)
    {
        if(strcmp(head->book.bookId, bookId) == 0)
        {
            head->book.stock = newStock;
            return 1;
        }
        head = head->next;
    }  
    return 0;
}

// 根据书号查找图书信息
Node* FindBook(Node *head, char bookId[]) {
    while (head != NULL)
    {
        if(strcmp(head->book.bookId, bookId) == 0)
            return head; 
        head = head->next;
    }
    return NULL;
}

// 遍历并输出所有图书信息
void TraverseList(Node *head) {
    printf("图书列表：\n");
    while (head != NULL) {
        printf("书号：%s, 书名：%s, 作者：%s, 库存：%d\n",
               head->book.bookId, head->book.title, head->book.author, head->book.stock);
        head = head->next;  
}
}

// 主函数
int main() {
    Node *head = NULL; // 链表头节点
    char bookId_find[4], bookId_update[4], bookId_delete[4];
    int num;
    scanf("%s", bookId_find);
    scanf("%s", bookId_update);
    scanf("%d", &num);
    scanf("%s", bookId_delete);

    // 添加图书信息
    Book book1 = {"001", "C程序设计", "谭浩强", 10};
    Book book2 = {"002", "数据结构", "严蔚敏", 5};
    Book book3 = {"003", "算法导论", "Thomas H. Cormen", 3};
    InsertBook(&head, book1);
    InsertBook(&head, book2);
    InsertBook(&head, book3);

    // 查找图书信息
    FindBook(head, bookId_find);

    // 修改图书库存数量
    UpdateStock(head, bookId_update, num);

    // 删除图书信息
    DeleteBook(&head, bookId_delete);

    // 遍历输出图书列表
    TraverseList(head);

    return 0;
}
