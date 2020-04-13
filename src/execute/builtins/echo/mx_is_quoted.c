#include "ush.h"

/*
    * determines, whether echo arguments 
      is in quotes: "arg" or 'arg'
    * 1 - is quoted
    * 0 - is not quoted
*/
int mx_is_quoted(char *str) {
    int last_index = mx_strlen(str) - 1;

    if (str[0] == '\"' && str[last_index] == '\"')
        return 1;
    if (str[0] == '\'' && str[last_index] == '\'')
        return 1;
    return 0;
}

