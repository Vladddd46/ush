#include "ush.h"
/*
 * Returns string of flags user specified in cmd;
 * Otherwise print error msg and return NULL;
 * Also takes arg_index as pointer and increments it
 * Until argument index is found.
 */
char *mx_which_flags_determine(char **cmd, int *arg_index) {
    char *flags = mx_strnew(2);
    char *msg;
    char *msg2;

    while(cmd[*arg_index] && cmd[*arg_index][0] == '-') {
        if (mx_strcmp(cmd[*arg_index], "-a") == 0)
            flags[0] = 'a';
        else if (mx_strcmp(cmd[*arg_index], "-s") == 0)
            flags[1] = 's';
        else {
            msg  = "which: illegal option -- z\n";
            msg2 = "usage: which [-as] program ...\n";
            write(2, msg, mx_strlen(msg));
            write(2, msg2, mx_strlen(msg2));
            free(flags);
            return NULL;
        }
        *arg_index += 1;
    }
    return flags;
}


