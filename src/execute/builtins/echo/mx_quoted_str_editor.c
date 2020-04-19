#include "ush.h"

/*
    * edits echo str depending on flags.
*/

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



char *mx_quoted_str_editor(char *str, char *flags) {    
    char *edited_str = mx_substr_retriever(str, 1, mx_strlen(str) - 2);;
    char *tmp = mx_strnew(mx_strlen(edited_str));
    int index = 0;
    char *result;

    if (flags[0] != 'E' || flags[1] == 'e') {
        for (int i = 0; edited_str[i]; ++i) {
            if(edited_str[i] == '\\') {
                i++;
                if (escape_char_determiner(edited_str[i]) == -1)
                    tmp[index] = edited_str[i];
                else 
                    tmp[index] = escape_char_determiner(edited_str[i]);
            }
            else 
                tmp[index] = edited_str[i];
            index++;
        }
        free(edited_str);
        edited_str = tmp;
    } 
    result = mx_string_copy(edited_str);
    free(edited_str);
    return result;
}




