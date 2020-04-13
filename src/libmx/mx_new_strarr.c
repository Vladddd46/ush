#include "ush.h"
/* 
    This func mallocs memmory for 2d array
    and returns this array
*/
char **mx_new_strarr(int number_of_str) {
    char **arr = (char **)malloc((number_of_str + 1) * sizeof(char *));

    arr[number_of_str] = NULL;
    return arr;
}
