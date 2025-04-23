#include <stdio.h>
#include <stdlib.h>

int getMappedValue(int num, int *mapping){
    if(num == 0){
        return mapping[0];
    }

    int mapped = 0;
    int power = 1;

    while (num > 0)
    {
        int digit = num % 10;
        mapped += mapping[digit] * power;
        power *= 10;
        num /= 10;
    }

    return mapped;
}


void sortJumbled(int *mapping, int *nums, int numsSize) {
    int *res_nums = (int *)malloc(numsSize * sizeof(int));
    int *mapped_values = (int *)malloc(numsSize * sizeof(int));
    
    // 复制原始数组并计算映射值
    for (int i = 0; i < numsSize; i++) {
        res_nums[i] = nums[i];
        mapped_values[i] = getMappedValue(nums[i], mapping);
    }
    
    // 冒泡排序 (稳定排序)
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (mapped_values[j] > mapped_values[j + 1]) {
                // 交换映射值
                int temp_mapped = mapped_values[j];
                mapped_values[j] = mapped_values[j + 1];
                mapped_values[j + 1] = temp_mapped;
                
                // 同步交换原始值
                int temp_orig = res_nums[j];
                res_nums[j] = res_nums[j + 1];
                res_nums[j + 1] = temp_orig;
            }
        }
    }
    
    // 输出结果
    for(int i = 0; i < numsSize; i++)
        printf("%d ", res_nums[i]);
    printf("\n");
    
    free(mapped_values);
    free(res_nums);
}

void readInput(int **mapping, int **nums, int *numsSize) {
    scanf("%d", numsSize);

    *mapping = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        scanf("%d", &((*mapping)[i]));
    }

    *nums = (int *)malloc((*numsSize) * sizeof(int));
    for (int i = 0; i < *numsSize; i++) {
        scanf("%d", &((*nums)[i]));
    }
}

int main() {
    int *mapping, *nums, numsSize;
    readInput(&mapping, &nums, &numsSize);
    sortJumbled(mapping, nums, numsSize);

    return 0;
}