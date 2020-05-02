#include "ush.h"

/*
 * Determines flags of pwd.
 * in case of too many arguments or bad option errors,
 * prints the corresponding msg to stderr and returns 1.
 * if success => puts flag option into buff char *flag 
 * and returns 0.
 */

static char valid_flag(char **cmd_expression, int i, char *flag) {
    if (strcmp(cmd_expression[i], "-P") == 0)
        return 'P';
    else if (strcmp(cmd_expression[i], "-L") == 0) {
        if (*flag != 'P')
            return 'L';
        else
            return 'P';
    }
    return -1;
}

int mx_pwd_flag_determine(char **cmd_expression, char *flag) {
    if (mx_strarr_size(cmd_expression) == 1)
        *flag = '.';
    else {
        for (int i = 1; cmd_expression[i]; ++i) {
            if (valid_flag(cmd_expression, i, flag) != -1)
                *flag = valid_flag(cmd_expression, i, flag);
            else if (cmd_expression[i][0] == '-' && 
                     strcmp(cmd_expression[i], "-") != 0) {
                mx_bad_option(cmd_expression[i], "pwd");
                return 1;
            }
            else {
                mx_too_many_arguments_error("pwd");
                return 1;
            }
        }
    }
    return 0;
}


