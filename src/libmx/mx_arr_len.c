#include "ush.h"

int mx_arr_len(char **arr) {
    int count = 0;

    while(arr[count])
        count++;
    return count;
}
