#include "libmx.h"

/*
 * Reallocates memory of str by 
 * len(str) + added_size;
 */
char *mx_str_realloc(char *str, int added_size) {
    int str_len = mx_strlen(str);
    char *new_str = mx_strnew(str_len + added_size);
    int i = 0;

    while(str[i]) {
        new_str[i] = str[i];
        i++;
    }
    return new_str;
}





