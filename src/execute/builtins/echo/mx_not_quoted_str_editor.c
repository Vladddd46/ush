#include "ush.h"

/*
    * removes omitting \ 
      from the unquoted str
*/
char *mx_not_quoted_str_editor(char *str) {
    char *edited_str = mx_strnew(mx_strlen(str));
    char *result;
    int omit   = 0;
    int walker = 0;
    int index  = 0;

    while(str[walker]) {
        if (str[walker] == '\\' && omit == 0)
            omit = 1;
        else {
            edited_str[index] = str[walker];
            omit = 0;
            index++;
        }
        walker++;
    }
    result = mx_string_copy(edited_str);
    free(edited_str);
    return result;
}





