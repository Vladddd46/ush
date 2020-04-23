#include "ush.h"
// Replaces str[indx1:indx2] with value

static void incrementer1(int *index, int *indx2) {
    *index += 1;
    *indx2 += 1;
}

static void incrementer2(int *index, int *tmp_index) {
    *index += 1;
    *tmp_index += 1;
}

char *mx_str_edit(char *str, char *value, int indx1, int indx2) {
    char *edited_str = mx_strnew(mx_strlen(str) + mx_strlen(value));
    char *res;
    int index = 0;
    int tmp_index = 0;

    while(index < indx1) {
        edited_str[index] = str[index];
        index++;
    }
    while(value[tmp_index]) {
        edited_str[index] = value[tmp_index];
        incrementer2(&index, &tmp_index);
    }
    while(str[indx2+1]) {
        edited_str[index] = str[indx2 + 1];
        incrementer1(&index, &indx2);
    }
    res = mx_string_copy(edited_str);
    free(edited_str);
    return res;
}



