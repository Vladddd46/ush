#include "ush.h"

/*
    This func. concatenates arr1 with arr2
    Example:
    arr1 = {"Hello", "Wolrd", NULL} 
    arr2 = {"Hooray", "...", NULL}
    Result: {"Hello", "World", "Hooray", "...", NULL}
*/
char **mx_strarr_join(char **arr1, char **arr2) {
    int arr_len1 = mx_strarr_size(arr1); 
    int arr_len2 = mx_strarr_size(arr2);
    int new_len = arr_len1 + arr_len2;
    char **joined_arr = mx_new_strarr(new_len);
    int i = 0;

    for (; i < arr_len1; ++i) {
        joined_arr[i] = arr1[i];
    } 
    for (int j = 0; j < arr_len2; ++j) {
        joined_arr[i] = arr2[j];
        i++;
    }
    return joined_arr;
}
