#include <stdio.h>
#include <string.h>
#define MAX_NUM 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int herbCollection(int C, int n, int time[], int value[]){
    int dp[C+1];
    memset(dp, 0, sizeof(dp));

    for(int i = 0; i < n; i++){
        for(int j = time[i]; j <= C; j++){
            dp[j] = max(dp[j], dp[j - time[i]] + value[i]);
        }
    }

    return dp[C];
}

int main()
{
    int total_time;
    int herb_num;
    int time[MAX_NUM];
    int value[MAX_NUM];
    int result;
    scanf("%d %d", &total_time, &herb_num);
    for(int i = 0; i < herb_num; i++){
        scanf("%d %d", &time[i], &value[i]);
    }
    result = herbCollection(total_time, herb_num, time, value);
    printf("%d", result);
    return 0;
}