#include "ush.h"

char *mx_upper_to_lower(char *old_str) {
    char *new_str = mx_strnew(mx_strlen(old_str));
    int i = 0;

    while(old_str[i]) {
        new_str[i] = tolower(old_str[i]);
        i++;
    }
    return new_str;
}


