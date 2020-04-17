#include "ush.h"

static char *processed_str(char *oldstr) {
    char *new_str = mx_strnew(mx_strlen(oldstr));
    char *res;
    int i_start = 0;
    int i_end   = mx_strlen(oldstr) - 1;
    int index = 0;

    if (oldstr[i_start] == oldstr[i_end] && 
        (oldstr[i_start] == '\'' || oldstr[i_start] == '\"')) {
        i_start += 1;
        i_end   -= 1;
    }
    for (;i_start <= i_end; i_start++) {
        if (oldstr[i_start] == '\\')
            i_start += 1;
        new_str[index] = oldstr[i_start];
        index++;
    }
    res = mx_string_copy(new_str);
    free(new_str);
    return res;
}

static void other(char **cmd) {
    int i = 0;
    char *new_str;

    while(cmd[i]) {
        new_str = processed_str(cmd[i]);
        free(cmd[i]);
        cmd[i] = new_str;
        i++;
    }
}

void mx_arguments_preprocessor(char **cmd) {
    
    if (mx_strcmp(cmd[0], "echo") == 0){
        // echo();
    }
    else
        other(cmd);
}


