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

static char *mx_subcmd_exe(char *expr, int start_indx, int end_indx, t_proc **proc) {
    char *cmd;
    char **cmd_arr;
    if (expr[start_indx] == '$')
        start_indx += 2;
    else if (expr[start_indx] == '`')
        start_indx += 1;

    cmd = mx_substr_retriever(expr, start_indx, end_indx - 1);
    if (cmd == NULL)
        return mx_strnew(1);
    cmd_arr  = mx_str_to_arr(cmd, ' ');

    char *result;
    int status;
    int pipefd[2];
    int cpy_fd = 1;
    pipe(pipefd);
    pid_t pid = fork();
    if (pid == 0) {
        close(pipefd[0]);
        cpy_fd = dup(1);
        dup2(pipefd[1], 1);

        if (mx_is_built_in(cmd_arr[0]))
            mx_built_ins_launcher(cmd_arr, &proc[0]);
        else
            mx_executing(cmd_arr, getenv("PATH"));
        dup2(cpy_fd, 1);
        exit(0);
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        result = mx_strnew(1000);
        int index = 0;
        char buff;
        close(pipefd[1]);
        while(read(pipefd[0], &buff, 1) != 0) {
            result[index] = buff;
            index++;
        }
    }
    return mx_string_copy(result);
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
            if (cmd[i][j] == '`' || (cmd[i][j] == '$' && cmd[i][j + 1] == '(')) {
                end_index = end_index_finder(cmd[i], j);
                res_of_cmd_exe = mx_subcmd_exe(cmd[i], j, end_index, proc);
                new_value = mx_str_edit(cmd[i], res_of_cmd_exe, j, end_index);
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


