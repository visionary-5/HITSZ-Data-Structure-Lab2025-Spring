#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 1000

int isPalindrome(char *s){
    int left = 0; 
    int right = strlen(s) - 1;

    while(left < right){
        while(left < right && !isalnum(s[left])){
            left++;
        }
        while (left < right && !isalnum(s[right]))
        {
            right--;
        }
        
        if (tolower(s[left]) != tolower(s[right])){
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

int main(){
    char s[MAX_SIZE];
    fgets(s, sizeof(s), stdin);

    if (isPalindrome(s)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}