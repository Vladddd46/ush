#include "ush.h"
// Changes back ground color of terminal
static int too_many_args_color(char **cmd_expression) {
    char *msg;
    char *syntax = "syntax: bgcolor [yellow/blue/red/green/etc]";

    if (mx_strarr_size(cmd_expression) > 2) {
        msg = "bgcolor: too many arguments\n";
        write(2, msg, mx_strlen(msg));
        write(2, syntax, mx_strlen(syntax));
        return 1;
    }
    if (mx_strarr_size(cmd_expression) == 1) {
        msg = "bgcolor: not enough arguments\n";
        write(2, msg, mx_strlen(msg));
        write(2, syntax, mx_strlen(syntax));
        return 1;
    }
    return 0;
}

static char *not_bold(char **cmd_expression) {
    char *color = NULL;

    if (mx_strcmp(cmd_expression[1], "blue")         == 0)
        color = "\033[0;44m";
    else if (mx_strcmp(cmd_expression[1], "bworn")  == 0)
        color = "\033[0;43m";
    else if (mx_strcmp(cmd_expression[1], "red")     == 0)
        color = "\033[0;41m";
    else if (mx_strcmp(cmd_expression[1], "green")   == 0)
        color = "\033[0;42m";
    else if (mx_strcmp(cmd_expression[1], "magneta") == 0)
        color = "\033[0;45m";
    else if (mx_strcmp(cmd_expression[1], "cyan")    == 0)
        color = "\033[0;46m";
    else if (mx_strcmp(cmd_expression[1], "black")    == 0)
        color = "\033[40m";
    return color;
}

static void bgcolor_list() {
    char *colors[16] = {"blue", "brown", "red", 
                        "green", "magneta", "cyan", NULL};
    int i = 0;

    while(colors[i]) {
        printf(">%s\n", colors[i]);
        i++;
    }
}

void mx_bgcolor(char **cmd_expression) {
    char *color = NULL;
    char *msg   = "bgcolor: no such color\n";
    char *msg2  = "bgcolor: <color list> to see all colors\n";

    if (too_many_args_color(cmd_expression))
        return;
    if (not_bold(cmd_expression)) 
        color = not_bold(cmd_expression);
    
    if (mx_strcmp(cmd_expression[1], "list") == 0)
        bgcolor_list();
    else if (color != NULL)
        write(1, color, mx_strlen(color));
    else {
        write(2, msg, mx_strlen(msg));
        write(2, msg2, mx_strlen(msg2));
    }
}

