#include "ush.h"
/*
 * Executes subcmd and writes it into pipe.
 * Reads from pipe and preproccess pipe output.
 * Returns str of output of substr.
 */

// Execute subcmd and writing output into pipe
static void child_proc(int pipefd[2], char **cmd_arr, t_proc **proc,
                                         t_local_env **local_env) {
    close(pipefd[0]);
    dup2(pipefd[1], 1);
    if (mx_is_built_in(cmd_arr[0]))
        mx_built_ins_launcher(cmd_arr, &proc[0], local_env);
    else
        mx_executing(cmd_arr, getenv("PATH"));
    exit(0);
}

// Reallocates mem for reading buffer
static void buffer_realloc(char **buffer_string, int *size) {
    char *tmp = mx_str_realloc(buffer_string[0], 1000);

    free(buffer_string[0]);
    buffer_string[0] = tmp;
    free(tmp);
    *size += 1000;
}

static char *parent_proc(int pipefd[2]) {
    int size = 1000;
    char *buffer_string = mx_strnew(size);
    char *result;
    int index = 0;
    char buff;

    close(pipefd[1]);
    while(read(pipefd[0], &buff, 1) != 0) {
        if (index + 1 == size)
            buffer_realloc(&buffer_string, &size);
        if (isspace(buff))
            buff = ' ';
        buffer_string[index] = buff;
        index++;
    }
    result = mx_string_copy(buffer_string);
    free(buffer_string);
    return result;
}

char *mx_exe(char **cmd_arr, t_proc **proc, t_local_env **local_env) {
    char *result = NULL;
    int  status;
    int  pipefd[2];
    pipe(pipefd);
    pid_t pid = fork();

    if (pid == 0) 
        child_proc(pipefd, cmd_arr, proc, local_env);
    else {
        waitpid(pid, &status, WUNTRACED);
        result = parent_proc(pipefd);
    }
    return result;
}
