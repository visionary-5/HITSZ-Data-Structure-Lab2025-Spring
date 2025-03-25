#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct {
    ElemType *elem;    // 空间基地址，空间存放纸牌正反面状态值,正/反分别用1/0表示
    int length;        // 存放纸牌数
    int listsize;      // 存放空间的容量
} SqList;  

int main()
{
    int cardnum;
    int cnt = 0;
    scanf("%d",&cardnum);
    SqList *cardlist;
    cardlist = (SqList*)malloc(sizeof(SqList));
    cardlist->length = cardnum;
    cardlist->listsize = cardnum + 1;
    cardlist->elem = (ElemType*)malloc((cardnum + 1)*sizeof(ElemType));

    for(int i = 1; i < cardnum + 1; i++)
    {
        cardlist->elem[i] = 1;
    }

    for(int j = 2; j < cardnum + 1; j++){
        for(int k = j; k < cardnum + 1; k+=j)
        {
            cardlist->elem[k] = 1 - cardlist->elem[k];
        }
    }

    for(int p = 1; p < cardnum + 1; p++)
    {
        if(cardlist->elem[p] == 1)
        {
            printf("%d ",p);
            cnt ++;
        }
    }
    printf("\n%d",cnt);
    return 0;
}