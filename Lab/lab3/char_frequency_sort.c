#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char ch;
    int freq;
}CharFreq;

int cmp(const void* a, const void* b){
    CharFreq* x = (CharFreq*)a;
    CharFreq* y = (CharFreq*)b;
    if (x->freq != y->freq)
        return y->freq - x->freq; // 频率高的排前面
    return x->ch - y->ch;     // 频率相同按照ASCII升序排
}

char* frequencySort(char* s) {
    int count[128] = {0}; //ASCII初始化为0
    for (int i = 0; s[i]; i++){
        count[(int)s[i]] ++;
    }

    CharFreq freqArr[128];
    int size = 0;

    for (int i = 0; i < 128; i++){
        if(count[i] > 0){
            freqArr[size].ch = i;
            freqArr[size].freq = count[i];
            size++;
        }
    }

    qsort(freqArr, size, sizeof(CharFreq), cmp);

    
    // 构造结果字符串
    char* result = (char*)malloc(strlen(s) + 1);
    int pos = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < freqArr[i].freq; j++) {
            result[pos++] = freqArr[i].ch;
        }
    }
    result[pos] = '\0';
    return result;
}

int main() {
    char s[1000];
    scanf("%s", s);
    
    char* result = frequencySort(s);
    printf("%s\n", result);
    
    return 0;
}