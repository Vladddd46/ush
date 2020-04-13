#include "ush.h"

/*
    * splits string (arg) in array {NAME,VALUE}
      splits by equal sign.
*/
char **mx_splitter(char *arg) {
    char **arr        = mx_new_strarr(2);
    int index_eq_sign = mx_char_index(arg, '=');

    // if no '=' in arg or '=' is last element
    // case: export a= || export a
    if (index_eq_sign == -1) {
        arr[0] = mx_string_copy(arg);
        arr[1] = mx_strnew(1);
    }
    else if (arg[mx_strlen(arg) - 1] == '=') {
        arr[0] = mx_substr_retriever(arg, 0, mx_strlen(arg) - 2);
        arr[1] = mx_strnew(1);
    }
    else {
        arr[0] = mx_substr_retriever(arg, 0, index_eq_sign - 1);
        arr[1] = mx_substr_retriever(arg, index_eq_sign+1, mx_strlen(arg) - 1);
    }
    return arr;
}

