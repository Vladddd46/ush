#include "ush.h"
/*
    * causes parse error if 
    no expression is given to separator.
*/

static void msg(void) {
    write(2, "u$h: parse error\n", 17);
}

int mx_parse_error(char **input_arr) {
    char *separators[10] = {"&", "&&", "||", "|", ">", ">>", "<", "<<", NULL};
    int last_el_indx = mx_strarr_size(input_arr) - 1;
    int first_el = mx_str_in_arr_index(separators, input_arr[0]);
    int last_el = mx_str_in_arr_index(separators, input_arr[last_el_indx]);

    if (first_el != -1 || last_el != -1) {
        msg();
        return 1;
    }
    for (int i = 0; i < last_el_indx; ++i) {
        if (mx_str_in_arr_index(separators, input_arr[i]) != -1 
            && mx_str_in_arr_index(separators, input_arr[i+1]) != -1) {
            msg();
            return 1;
        }
    }
    return 0;
}
