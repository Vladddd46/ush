#include "ush.h"
/*
    frees array
*/
void mx_arr_freesher(char **arr) {
    if (arr == NULL)
        return;
    
    int del = 0;
    while (arr[del]) {
        free(arr[del]);
        del++;
    }
    free(arr);
}


