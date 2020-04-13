#include "ush.h"
/*
    * takes "pretty" expression (f.e "ls && pwd || sleep 10")
    * returns array of words divided by ' ' (space)
    * PS. spaces in quotes ("   "/' ') are skipped.
*/

// changes spaces in quotes in ASCII 12,in order to divide,then restore
static char *dirty_str_maker(char *str) {
    char *dirty_str = mx_string_copy(str);
    int index = 0;

    while (str[index]) {
        if (str[index] == '\"') {
            index++;
            while (str[index] != '\"') {
                if (str[index] == ' ')
                    dirty_str[index] = 12;
                index++;
            }
        }
        else if (str[index] == '\'') {
            index++;
            while (str[index] != '\'') {
                if (str[index] == ' ')
                    dirty_str[index] = 12;
                index++;
            }
        }
        else if (str[index] == '(') {
            index++;
            while (str[index] != ')') {
                if (str[index] == ' ')
                    dirty_str[index] = 12;
                index++;
            }
        }
        else if (str[index] == '`') {
            index++;
            while (str[index] != '`') {
                if (str[index] == ' ')
                    dirty_str[index] = 12;
                index++;
            }
        }
        index++;
    }
    return dirty_str;
}

char **mx_divide_by_space(char *expression) {
    char *dirty_str = dirty_str_maker(expression);
    char **arr = mx_str_to_arr(dirty_str, ' ');
    int  z;

    free(dirty_str);
    z = 0;
    while(arr[z]) {
        for (int i = 0; arr[z][i]; ++i) {
            if (arr[z][i] == 12) {
                arr[z][i] = ' ';
            }
        }
        z++;
    }
    return arr;
}



