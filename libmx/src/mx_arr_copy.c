#include "libmx.h"

// Copies array of strings.
char **mx_arr_copy(char **old_arr) {
    int len     = mx_strarr_size(old_arr);
    char **copy = mx_new_strarr(len);
    int i;

    i = 0;
    while(old_arr[i]) {
        copy[i] = mx_string_copy(old_arr[i]);
        i++;
    }
    return copy;
}



