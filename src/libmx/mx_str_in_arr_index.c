#include "ush.h"


int mx_str_in_arr_index(char **arr, char *str) {
    int i = 0;
    
    while(arr[i]) {
        if (mx_strcmp(arr[i], str) == 0)
            return i;
        i++;
    }
    return -1;
}


