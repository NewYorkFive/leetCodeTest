//
//  q0005.c
//  LeetCode
//
//  Created by NowOrNever on 22/10/2019.
//  Copyright © 2019 DoubleL. All rights reserved.
//

#include "q0005.h"
#include "../common.h"


//5. Longest Palindromic Substring
//Medium
//Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
//Example 1:
//Input: "babad"
//Output: "bab"
//Note: "aba" is also a valid answer.
//Example 2:
//Input: "cbbd"
//Output: "bb"

int checkIsOddPalindrome(char *s, char *first, char *last, int *maxLength,char **target, bool *isOdd){
    char *pLeft = s - 1;
    char *pRight= s + 1;
    int result = 0;
    *isOdd = false;
    while (pLeft >= first && pRight <= last) {
        if (*pLeft == *pRight) {
            result++;
        }else{
            break;
        }
        pLeft--;
        pRight++;
    }
    if (result * 2 + 1 > *maxLength && result > 0) {
        *maxLength = result * 2 + 1;
        *target = s - result;
    }
    if (result > 0) {
        *isOdd = true;
    }
    return result;
}

int checkIsEvenPalindrome(char *s, char *first, char *last, int *maxLength,char **target, bool *isEven){
    char *pLeft = s;
    char *pRight= s + 1;
    int result = 0;
    *isEven = false;
    while (pLeft >= first && pRight <= last) {
        if (*pLeft == *pRight) {
            result++;
        }else{
            break;
        }
        pLeft--;
        pRight++;
    }
    if (result * 2 > *maxLength && result > 0) {
        *maxLength = result * 2;
        *target = s - result + 1;
    }
    if (result > 0) {
        *isEven = true;
    }
    return result;
}

char* longestPalindrome2(char* s) {
    char *target = s;
    char *p = s;
    char *last = s + strlen(s);
    int maxLength = 0;
    
    bool isOdd = false;
    bool isEven = false;
    
//    int step;
//    int step1;
//    int step2;
    
    while (p>=s && p<= last) {
        printf("\ncurrent s(%s) target(%s) maxleng(%d)",p,target ,maxLength);
        checkIsOddPalindrome(p, s, last, &maxLength, &target, &isOdd);
        checkIsEvenPalindrome(p, s, last, &maxLength, &target, &isEven);
//        step = step1 > step2 ? step1 : step2;
//        p += step;
        p++;
    }
    if (maxLength == 0) {
        char *result = malloc(sizeof(char) * 2);
        *result = *s;
        *(result + 1) = '\0';
        return result;
    }
    char *result = malloc(sizeof(char) * (maxLength + 1));
    memset(result, 0, sizeof(char) * (maxLength + 1));
    memcpy(result, target, maxLength);
    result[maxLength] = '\0';
    return result;
}

char* longestPalindrome(char* s){
    size_t length = strlen(s);
    bool dp[length + 1][length + 1];
    // initialize
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            dp[i][j] = (i == j);
        }
    }
    
    size_t end_pos = 0;
    size_t max = 0;
    for (size_t end = 1; end < length; end++) {
        // printf("\nend %d\n", end);
        for (int start = (int)end - 1; start >= 0; start--) {
            // printf("%d ", start);
            if (s[start] == s[end] && (end - start == 1 || dp[start + 1][end - 1])) {
                dp[start][end] = true;
                if (end - start > max) {
                    end_pos = end;
                    max = end - start;
                }
            }
        }
    }

    char *result = calloc(max + 2, sizeof(char));
    memcpy(result, s + end_pos - max, max + 1);
    return result;
}
int question5(){
    char *s = "aaaaa";
    printf("\nlongest %s",longestPalindrome(s));
    printf("\nfinished");
    return 0;
};
