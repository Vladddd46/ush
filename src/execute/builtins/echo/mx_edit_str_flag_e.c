#include "ush.h"

static char escape_char_determiner(char c) {
    if (c == 'a') 
        return '\a';
    else if (c == 'b')
        return '\b';
    else if (c == 'f')
        return '\f';
    else if (c == 'n')
        return '\n'; 
    else if (c == 'r')
        return '\r';
    else if (c == 't')
        return '\t';
    else if (c == 'v') 
        return '\v';
    return -1;
}

static void counters_increment(int *walker, int *index) {
    *walker += 1;
    *index  += 1;
}

void mx_edit_str_flag_e(char *str, char *edited_str) {
    int index     = 0;
    int walker    = 1;
    int esc_chr   = 0;

    while(walker < mx_strlen(str) - 1) {
        if (str[walker] == '\\' && esc_chr == 0) {
            esc_chr = 1;
            walker++;
            continue;
        }
        else if (esc_chr == 1) {
            esc_chr = 0;
            if (escape_char_determiner(str[walker]) != -1)
                edited_str[index] = escape_char_determiner(str[walker]);
            else
                edited_str[index] = str[walker];
        }
        else
            edited_str[index] = str[walker];
        counters_increment(&walker, &index);
    }
}
























