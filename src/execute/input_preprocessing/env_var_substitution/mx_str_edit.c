#include "ush.h"
/*
    * replaces str[indx1:indx2] with value
*/
char *mx_str_edit(char *str, char *value, int indx1, int indx2) {
    int len_of_edited_str = indx1 + mx_strlen(value) + (indx2 - indx1 + 1);
    char *edited_str = mx_strnew(len_of_edited_str);
    int index = 0;
    int tmp_index = 0;

    while(index < indx1) {
        edited_str[index] = str[index];
        index++;
    }
    while(value[tmp_index]) {
        edited_str[index] = value[tmp_index];
        tmp_index++;
        index++;
    }
    while(str[indx2+1]) {
        edited_str[index] = str[indx2 + 1];
        index++;
        indx2++;
    }
    return edited_str;
}



