#include "ush.h"

/*
    * edits echo str depending on flags.
*/

// skips slash char "\" in str
static void slash_skipper(char *str, char *edited_str) {
    int walker = 1;
    int end_index = mx_strlen(str) - 1;
    int omit = 0;
    int index = 0;

    while(walker < end_index) {
        if (omit == 0 && str[walker] == '\\') {
            omit = 1;
            walker++;
            continue;
        }
        omit = 0;
        edited_str[index] = str[walker];
        index++;
        walker++;
    }
}

char *mx_quoted_str_editor(char *str, char *flags) {    
    char *edited_str = mx_strnew(mx_strlen(str));
    char *result;

    if (flags[0] == 'E' && str[0] != '\'') {
        mx_edit_str_flag_big_e(str, edited_str);
    }
    else if (flags[1] == 'e')
        mx_edit_str_flag_e(str, edited_str);
    else {
        if (str[0] == '\'' && str[mx_strlen(str) - 1] == '\'')
            edited_str = mx_substr_retriever(str, 1, mx_strlen(str) - 2);
        else
            slash_skipper(str, edited_str);
    }
    result = mx_string_copy(edited_str);
    free(edited_str);
    return result;
}




