#include "ush.h"

/* 
    * executes binary from env command
    int binary_index - index of binary must be executed. 
*/

/*
    Just show an example:
    >>> old_cwd = {"env", "-i", "ls", "-l", "-a", "-R"};
    >>> new_cwd = {"ls", "-l", "-a"};
*/
static char **correct_command_retriever(char **old_cwd, int bin_index) {
    int len = mx_strarr_size(old_cwd) - bin_index;
    char **new_cwd = mx_new_strarr(len);
    int index = 0;

    while(old_cwd[bin_index]) {
        new_cwd[index] = old_cwd[bin_index];
        index++;
        bin_index++;
    }
    return new_cwd;
}

void mx_env_exe(char **cmd, int binary_index, t_proc **proc, char *path) {
    char **new_cwd = correct_command_retriever(cmd, binary_index);
    //print debug
    mx_external(new_cwd, proc, path);
    mx_arr_freesher(new_cwd);
}


