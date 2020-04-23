#include "ush.h"

static void refresh_exit_status(char **cmd_expression) {
    if (cmd_expression[0] && 
        mx_strcmp(cmd_expression[0], "which")  != 0)
        setenv("?", "0", 1);
}

// launches built-in
void mx_built_ins_launcher(char **cmd_expression, t_proc **proc) {
    if (mx_strcmp(cmd_expression[0],      "export") == 0)
        mx_export(cmd_expression);
    else if (mx_strcmp(cmd_expression[0], "unset")  == 0)
        mx_unset(cmd_expression);
    else if (mx_strcmp(cmd_expression[0], "env") == 0)
        mx_env(cmd_expression, proc);
    else if (mx_strcmp(cmd_expression[0], "pwd") == 0) 
        mx_pwd(cmd_expression);
    else if (mx_strcmp(cmd_expression[0], "which") == 0)
        mx_which(cmd_expression);
    else if (mx_strcmp(cmd_expression[0], "echo") == 0)
        mx_echo(cmd_expression);
    else if (mx_strcmp(cmd_expression[0], "fg") == 0) 
        mx_fg(cmd_expression, &proc[0]);
    else if (mx_strcmp(cmd_expression[0], "exit") == 0) 
        mx_exit(cmd_expression);
    else if (mx_strcmp(cmd_expression[0], "jobs") == 0)
        mx_jobs(proc[0]);
    else if (mx_strcmp(cmd_expression[0], "cd") == 0)
        mx_cd(cmd_expression);
    else if (mx_strcmp(cmd_expression[0], "color") == 0)
        mx_color(cmd_expression);
    else if (mx_strcmp(cmd_expression[0], "bgcolor") == 0)
        mx_bgcolor(cmd_expression);
    refresh_exit_status(cmd_expression);
}


