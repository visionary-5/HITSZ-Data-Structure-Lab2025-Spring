#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BLOOM_SIZE 10000  // 布隆过滤器位数组大小
#define NUM_HASHES 3      // 使用的哈希函数数量

typedef struct {
    unsigned char *bit_array;
    int size;
} BloomFilter;

// 初始化布隆过滤器
BloomFilter* bloom_init(int size) {
    BloomFilter *filter = (BloomFilter*)malloc(sizeof(BloomFilter));
    filter->size = size;
    filter->bit_array = (unsigned char*)calloc((size + 7) / 8, sizeof(unsigned char));
    return filter;
}

// 释放布隆过滤器
void bloom_free(BloomFilter *filter) {
    free(filter->bit_array);
    free(filter);
}

// 设置位数组中的某一位
void set_bit(BloomFilter *filter, unsigned int index) {
    int byte_index = index / 8;
    int bit_offset = index % 8;
    unsigned char mask = 1 << bit_offset;
    filter->bit_array[byte_index] |= mask;
}

// 检查位数组中的某一位
int get_bit(BloomFilter *filter, unsigned int index) {
    int byte_index = index / 8;
    int bit_offset = index % 8;
    unsigned char mask = 1 << bit_offset;
    return (filter->bit_array[byte_index] & mask) != 0;
}

// 哈希函数1 DJB2哈希函数
unsigned int hash1(const char *str) {
    unsigned int hash = 5381;//初始的种子值
    int c;

    while((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % BLOOM_SIZE; // 返回哈希值
}

// 哈希函数2
unsigned int hash2(const char *str) {
    unsigned int hash = 0;
    int c;
    
    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;  // 位运算组合
    }
    
    return hash % BLOOM_SIZE;
}

// 哈希函数3
unsigned int hash3(const char *str) {
    unsigned int hash = 2166136261;  // FNV偏移基数
    int c;
    
    while ((c = *str++)) {
        hash ^= c;  // 先异或
        hash *= 16777619;  // 再乘以FNV质数
    }
    
    return hash % BLOOM_SIZE;
}

// 添加元素到布隆过滤器
void bloom_add(BloomFilter *filter, const char *item) {
     // 计算三个哈希值
    unsigned int index1 = hash1(item);
    unsigned int index2 = hash2(item);
    unsigned int index3 = hash3(item);
    
    // 将这三个位置设置为1
    set_bit(filter, index1);
    set_bit(filter, index2);
    set_bit(filter, index3);
}

// 检查元素是否可能在布隆过滤器中
int bloom_check(BloomFilter *filter, const char *item) {
    // 计算三个哈希值
    unsigned int index1 = hash1(item);
    unsigned int index2 = hash2(item);
    unsigned int index3 = hash3(item);
    
    // 检查这三个位置是否都为1
    // 只有当所有位都是1时，才返回1（可能存在）
    return get_bit(filter, index1) && 
           get_bit(filter, index2) && 
           get_bit(filter, index3);
}

int main() {
    // 创建布隆过滤器
    BloomFilter *filter = bloom_init(BLOOM_SIZE);
    
    int m;
    char str_add[100];
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        scanf("%s", str_add);
        bloom_add(filter, str_add);
    }

    int n;
    char str_check[100];
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%s", str_check);
        printf("%d\n", bloom_check(filter, str_check));
    }
    
    // 释放过滤器
    bloom_free(filter);
    
    return 0;
}