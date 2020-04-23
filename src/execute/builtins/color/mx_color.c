#include "ush.h"
// Changes color of terminal

static int too_many_args_color(char **cmd_expression) {
    char *msg;
    char *syntax = "syntax: color [yellow/blue/red/green/etc]";

    if (mx_strarr_size(cmd_expression) > 2) {
        msg = "color: too many arguments\n";
        write(2, msg, mx_strlen(msg));
        write(2, syntax, mx_strlen(syntax));
        return 1;
    }
    if (mx_strarr_size(cmd_expression) == 1) {
        msg = "color: not enough arguments\n";
        write(2, msg, mx_strlen(msg));
        write(2, syntax, mx_strlen(syntax));
        return 1;
    }
    return 0;
}

void mx_color(char **cmd_expression) {
    if (too_many_args_color(cmd_expression))
        return;

    char *color = NULL;

    if (mx_strcmp(cmd_expression[1], "yellow") == 0)
        color = "\033[0;33m";
    else if (mx_strcmp(cmd_expression[1], "red") == 0)
        color = "\033[0;31m";
    else if (mx_strcmp(cmd_expression[1], "green") == 0)
        color = "\033[0;32m";
    else if (mx_strcmp(cmd_expression[1], "blue") == 0)
        color = "\033[0;34m";
    
    if (color != NULL)
        write(1, color, mx_strlen(color));
}





