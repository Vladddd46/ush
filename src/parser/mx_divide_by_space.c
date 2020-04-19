#include "ush.h"
/*
    * takes "pretty" expression (f.e "ls && pwd || sleep 10")
    * returns array of words divided by ' ' (space)
    * PS. spaces in quotes ("   "/' ') and \(space) are skipped.
*/

// change spaces, which are in quotes <""> or <''> into ASCII 12
static void spaces_in_quotes(char **str, char **dirty_str, int *index) {
    if (str[0][*index] == '\"') {
        *index += 1;
        while (str[0][*index] && str[0][*index] != '\"') {
            if (str[0][*index] == ' ')
                dirty_str[0][*index] = 12;
            *index += 1;
        }
    }
    else if (str[0][*index] && str[0][*index] == '\'') {
        *index += 1;
        while (str[0][*index] != '\'') {
            if (str[0][*index] == ' ')
                dirty_str[0][*index] = 12;
            *index += 1;
        }
    }
}

// change spaces, which are in <()> or <``> into ASCII 12 
static void spaces_in_braces(char **str, char **dirty_str, int *index) {
    if (str[0][*index] == '(') {
        *index += 1;
        while (str[0][*index] && str[0][*index] != ')') {
            if (str[0][*index] == ' ')
                dirty_str[0][*index] = 12;
            *index += 1;
        }
    }
    else if (str[0][*index] == '`') {
        *index += 1;
        while (str[0][*index] && str[0][*index] != '`') {
            if (str[0][*index] == ' ')
                dirty_str[0][*index] = 12;
            *index += 1;
        }
    }
}

// change slash+space into ASCII 12
static char *slash_space_change(char *dirty_str) {
    char *str_with_handled_slash_space;
    char *tmp = mx_strnew(mx_strlen(dirty_str));
    int index = 0;
    int i     = 0;

    while(dirty_str[i]) {
        if (dirty_str[i] == '\\' && dirty_str[i + 1] == ' ') {
            tmp[index] = 12;
            i++;
        }
        else
            tmp[index] = dirty_str[i];
        i++;
        index++;
    }
    str_with_handled_slash_space = mx_string_copy(tmp);
    free(tmp);
    return str_with_handled_slash_space;
}

/* 
    changes spaces in quotes and \(space) in ASCII 12,
    in order to divide by space correctrly.
    Then restore it back. ASCCII 12 = space.
*/
static char *dirty_str_maker(char *str) {
    char *dirty_str      = mx_string_copy(str);
    char *spaces_changed;
    int index  = 0;

    while (str[index]) {
        spaces_in_quotes(&str,   &dirty_str, &index);
        spaces_in_braces(&str,   &dirty_str, &index);
        index++;
    }
    spaces_changed = slash_space_change(dirty_str);
    free(dirty_str);
    return spaces_changed;
}

char **mx_divide_by_space(char *expression) {
    char *dirty_str = dirty_str_maker(expression);
    char **arr      = mx_str_to_arr(dirty_str, ' ');
    int  z;

    free(dirty_str);
    z = 0;
    while(arr[z]) {
        for (int i = 0; arr[z][i]; ++i) {
            if (arr[z][i] == 12)
                arr[z][i] = ' ';
        }
        z++;
    }
    return arr;
}



