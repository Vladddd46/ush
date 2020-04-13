#include "ush.h"


void mx_edit_str_flag_big_e(char *str, char *edited_str) {
    int walker = 1;
    int index  = 0;
    int esc_chr;

    while(walker < mx_strlen(str) - 1) {
        if (str[walker] == '\\' && esc_chr == 0) {
            esc_chr = 1;
            walker++;
            continue;
        }
        else if (esc_chr == 1) {
            esc_chr = 0;
            edited_str[index] = str[walker];
            index++;
            walker++;
            continue;
        }
        edited_str[index] = str[walker];
        index++;
        walker++;
    }
}


