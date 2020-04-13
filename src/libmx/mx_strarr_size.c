#include "ush.h"

/*
    Counts size of str array
*/

int mx_strarr_size(char **arr) {
    int counter = 0;

    while(arr[counter])
        counter++;
    return counter;
}
