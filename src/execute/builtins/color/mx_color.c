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

static char *bold(char **cmd_expression) {
    char *color = NULL;

    if (mx_strcmp(cmd_expression[1], "bold_red")     == 0)
        color = "\033[1;31m";
    else if (mx_strcmp(cmd_expression[1], "bold_green")   == 0)
        color = "\033[1;32m";
    else if (mx_strcmp(cmd_expression[1], "bold_yellow")  == 0)
        color = "\033[01;33m";
    else if (mx_strcmp(cmd_expression[1], "bold_blue")    == 0)
        color = "\033[1;34m";
    else if (mx_strcmp(cmd_expression[1], "bold_magneta") == 0)
        color = "\033[1;35m";
    else if (mx_strcmp(cmd_expression[1], "bold_cyan")    == 0)
        color = "\033[1;36m";
    return color;
}

static char *not_bold(char **cmd_expression) {
    char *color = NULL;

    if (mx_strcmp(cmd_expression[1], "blue")         == 0)
        color = "\033[0;34m";
    else if (mx_strcmp(cmd_expression[1], "yellow")  == 0)
        color = "\033[0;33m";
    else if (mx_strcmp(cmd_expression[1], "red")     == 0)
        color = "\033[0;31m";
    else if (mx_strcmp(cmd_expression[1], "green")   == 0)
        color = "\033[0;32m";
    else if (mx_strcmp(cmd_expression[1], "magneta") == 0)
        color = "\033[0;35m";
    else if (mx_strcmp(cmd_expression[1], "cyan")    == 0)
        color = "\033[0;36m";
    else if (mx_strcmp(cmd_expression[1], "black")    == 0)
        color = "\033[0m";
    return color;
}

static void color_list() {
    char *colors[16] = {"blue", "yellow", "red", 
                        "green", "magneta", "cyan", 
                        "black", "bold_red", "bold_green", 
                        "bold_yellow", "bold_blue", "bold_magneta", 
                        "bold_cyan", NULL};
    int i = 0;

    while(colors[i]) {
        printf(">%s\n", colors[i]);
        i++;
    }
}

void mx_color(char **cmd_expression) {
    char *color = NULL;
    char *msg   = "color: no such color\n";
    char *msg2  = "color: <color list> to see all colors\n";

    if (too_many_args_color(cmd_expression))
        return;
    if (not_bold(cmd_expression)) 
        color = not_bold(cmd_expression);
    else if (bold(cmd_expression))
        color = bold(cmd_expression);
    
    if (mx_strcmp(cmd_expression[1], "list") == 0)
        color_list();
    else if (color != NULL)
        write(1, color, mx_strlen(color));
    else {
        write(2, msg, mx_strlen(msg));
        write(2, msg2, mx_strlen(msg2));
    }
}

