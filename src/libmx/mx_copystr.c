#include "ush.h"

char *mx_copystr(char *str) {
    char *new_str;

    if (str == NULL)
        return NULL;
    new_str = mx_strnew(mx_strlen(str));
    for (int i = 0; i < mx_strlen(str); ++i)
        new_str[i] = new_str[i];
    return new_str;
}
