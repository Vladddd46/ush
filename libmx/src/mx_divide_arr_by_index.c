#include "libmx.h"


/*
 * Retrieves small piece of arr by indexes
 * Example:
 *  arr = {"A", "B", "C", "D", "E"}
 *  mx_divide_arr_by_index(arr, 2, 4)
 *  return {"C", "D", "E"}
 */
char **mx_divide_arr_by_index(char **arr, int index1, int index2) {
    char **subarr = mx_new_strarr((index2 + 1) - index1);
    int i = 0;
    int tmp = index1;

    while(tmp <= index2) {
        subarr[i] = arr[tmp];
        i++;
        tmp++;
    }
    return subarr;
}


