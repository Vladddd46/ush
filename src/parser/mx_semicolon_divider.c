#include "ush.h"

/*
 * Divides expression by semicolon
 *  Example: 
 *      "echo ";;;;;;;";pwd;ls"
 *  Output:
 *       {"echo ";;;;;;:"", "pwd", "ls"}
 */


static int status_value(int status, char chr) {
    int tmp_status = status;

    if (chr == '\"' && tmp_status == 0)
        tmp_status = 1;
    else if (chr == '\"' && tmp_status == 1)
        tmp_status = 0;
    else if (chr == '\'' && tmp_status == 0)
        tmp_status = 2;
    else if (chr == '\'' && tmp_status == 2)
        tmp_status = 0;
    return tmp_status;
}

static void restore(char **arr) {
    char *new;

    for (int i = 0; arr[i]; ++i) {
        new = mx_strnew(mx_strlen(arr[i]));
        for (int j = 0; arr[i][j]; ++j) {
            if (arr[i][j] == 20)
                new[j] = ';';
            else
                new[j] = arr[i][j];
        }
        free(arr[i]);
        arr[i] = new;
    }
}

static int syntax_exception(char *input) {
    int status = 0;
    char *msg;

    for (int i = 0; i < mx_strlen(input)-1; ++i) {
        status = status_value(status, input[i]);
        if (input[i] == ';' && input[i+1] == ';' && status == 0) {
            msg = "\nu$h: syntax error near unexpected token \';;\'";
            write(2, msg, mx_strlen(msg));
            return 1;
        }
    }
    return 0;
}

char **mx_semicolon_divider(char *input) {
    if (syntax_exception(input))
        return NULL;
    char *new_str = mx_strnew(mx_strlen(input));
    int status = 0;
    char **arr;
    
    for (int i = 0; input[i]; ++i) {
        status = status_value(status, input[i]);
        if (input[i] == ';' && status != 0)
            new_str[i] = 20;
        else
            new_str[i] = input[i];
    }
    arr = mx_str_to_arr(new_str, ';');
    free(new_str);
    if (*arr == NULL) {
        free(arr);
        return NULL;
    }
    restore(arr);
    return arr;
}




