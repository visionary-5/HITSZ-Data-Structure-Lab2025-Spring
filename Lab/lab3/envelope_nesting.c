#include <stdio.h>
#include <stdlib.h>

// 信封结构体
typedef struct {
    int width;
    int height;
} Envelope;

//按照宽度升序，宽度相同的时候按照高度降序
int compareEnvelopes(const void* a, const void* b){
    Envelope* e1 = (Envelope*)a;
    Envelope* e2 = (Envelope*)b;

    if (e1->width != e2->width)
        return e1->width - e2->width;
    else
        return e2->height - e1->width;
}
int maxEnvelopes(Envelope* envelopes, int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    qsort(envelopes, n ,sizeof(Envelope), compareEnvelopes);

    int *dp = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        dp[i] = 1;
    }

    int max_len = 1;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if (envelopes[i].height > envelopes[j].height){
                // 更新dp[i]为max(dp[i], dp[j] + 1)
                if (dp[j] + 1 > dp[i]){
                    dp[i] = dp[j] + 1;
                }
            }
        }
        // 更新全局最大长度
        if (dp[i] > max_len){
            max_len = dp[i];
        }
    }

    free(dp);
    return max_len;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Envelope* envelopes = (Envelope*)malloc(n * sizeof(Envelope));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &envelopes[i].width, &envelopes[i].height);
    }
    
    int result = maxEnvelopes(envelopes, n);
    printf("%d\n", result);
    
    free(envelopes);
    return 0;
}