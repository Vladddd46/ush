#include "ush.h"

/*
 * Adds spaces ' ' before and after separator symbols
 * Example:
 *      >>> "echo 1&&echo 2; pwd"
 *      <<< return "echo 1 && echo 2 ; pwd"
 * PS. this is needed for splitting str by spaces.
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

char *mx_space_prettier(char *input_str) {
    char *sep = "|&<>";
    char *new_str = mx_strnew((mx_strlen(input_str) + 1) * 2);
    int  index = 0;
    int  status = 0;

    for (int i = 0; i < mx_strlen(input_str); ++i) {
        status = status_value(status, input_str[i]);
        if (mx_is_in_arr(sep, input_str[i]) && status == 0) {
            new_str[index] = ' ';
            index++;
            new_str[index] = input_str[i];
            index++;
            if (input_str[i + 1] == input_str[i]) {
                new_str[index] = input_str[i];
                index++;
                i++;
            }
            new_str[index] = ' ';
        }
        else
            new_str[index] = input_str[i];
        index++;
    }
    return new_str;
}





