#include "ush.h"

/*
    * implementation of cmd substitution functinonal
    $(command) or `command`
*/

// finds ending index of subcmd expression
static int end_index_finder(char *expr, int start) {
    int end_index = start;

    if (expr[end_index] == '$') {
        while(expr[end_index] && expr[end_index] != ')')
            end_index++;
    }
    else if (expr[end_index] == '`') {
        end_index++;
        while(expr[end_index] && expr[end_index] != '`')
            end_index++;
    }
    return end_index;
}

static int condition(char **cmd, int i, int j) {
    if (j == 0 && cmd[i][j] == '`')
        return 1;
    else if (j != 0 && cmd[i][j - 1] != '\\' && cmd[i][j] == '`')
        return 1;
    return 0;
}

void mx_cmd_substitution(char **cmd, t_proc **proc) {
    char *res_of_cmd_exe;
    char *new_value;
    int end_index;
    int i = 0;
    int j;
    while(cmd[i]) {
        j = 0;
        while(cmd[i][j]) {
            if (condition(cmd, i, j)  || (cmd[i][j] == '$' && cmd[i][j + 1] == '(')) {
                end_index      = end_index_finder(cmd[i], j);
                res_of_cmd_exe = mx_subcmd_exe(cmd[i], j, end_index, proc);
                new_value      = mx_str_edit(cmd[i], res_of_cmd_exe, j, end_index);
                free(cmd[i]);
                free(res_of_cmd_exe);
                cmd[i] = new_value;
                j = -1;
            }
            j++;
        }
        i++;
    }
}


