#include "ush.h"
/*
    * executes cmd, user specified in expression
      for expample echo `somecmd`
      >>> execute somecmd and changing it`s stdout into pipe.
*/

// retrieves cmd from expression echo `somecmd` => somecmd
static char *cmd_retriever(char *expr, int start_indx, int end_indx) {
    char *cmd;

    if (expr[start_indx] == '$')
        start_indx += 2;
    else if (expr[start_indx] == '`')
        start_indx += 1;
    cmd = mx_substr_retriever(expr, start_indx, end_indx - 1);
    return cmd;
}

static char **cmd_to_arr(char *expr, int start_indx, int end_indx) {
    char *cmd = cmd_retriever(expr, start_indx, end_indx);
    char **cmd_arr;

    if (cmd == NULL)
        return NULL;
    cmd_arr = mx_divide_by_space(cmd);
    free(cmd);
    return cmd_arr;
}

char *mx_subcmd_exe(char *expr, int start_indx, 
                    int end_indx, t_proc **proc) {
    char **cmd_arr = cmd_to_arr(expr, start_indx, end_indx);
    char *result;

    if (cmd_arr == NULL)
        return mx_strnew(1);
    result = mx_exe(cmd_arr, proc);
    return mx_string_copy(result);
}

