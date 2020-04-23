#include "libmx.h"

static void mx_swap(char **arr, int index1, int index2) {
    char *tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}

static int mx_partition (char **arr, int low, int high) { 
    char *pivot = arr[high];
    // Index of smaller element 
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++)  {
        if (mx_strcmp(arr[j], pivot) < 0)  { 
            i++;  
            mx_swap(arr, i, j); 
        } 
    } 
    mx_swap(arr,i + 1, high); 
    return (i + 1); 
}

void mx_quicksort_strarr(char **arr, int left, int right) {
    if (left < right) {
        int i = mx_partition(arr, left, right);
        mx_quicksort_strarr(arr, i + 1, right);
        mx_quicksort_strarr(arr, left, right - 1);
    }
}
