#include "ush.h"

// Executes functions, which are not built in shell

static void free_node(t_proc **node) {
    if (node[0] != NULL) {
        free(node[0]->proc_name);
        free(node[0]);
    }
}

static int exit_status_func(int status, t_proc **proc, char *proc_name) {
    int   exit_status = 1;
    t_proc *node_to_free;

    // If proccess was stopped by ctrl+z
    if (WIFSTOPPED(status)) {
        exit_status = 0;
        mx_suspended_process_msg(proc_name);
    }
    // If procces ended sucessfully or stopped by ctrl+c
    // => deleting proc node from list 
    else if (WIFEXITED(status) || WTERMSIG(status) == 2) {
        if (WTERMSIG(status) == 2)
            exit_status = 0;
        node_to_free = proc[0];
        proc[0] = proc[0]->next;
        free_node(&node_to_free);
    }
    return exit_status;
}

int mx_external(char **cmd_expression, t_proc **proc, char *path) {
    int   exit_status = 1;
    int   status;
    int   exe_status; 
    int   parent_pid = getpid();
    pid_t proccess = fork();

    if (proccess != 0)
        mx_push_proc_front(&proc[0], proccess, cmd_expression[0]);
    if (proccess == 0) {
        mx_signals_restore();
        setpgid(getpid(), getpid());
        mx_controlling_terminal_change(getpid());
        exe_status = mx_executing(cmd_expression, path);
        mx_child_exit(exe_status, cmd_expression);
    }
    else {
        waitpid(proccess, &status, WUNTRACED);
        setenv("?", mx_itoa(status), 1);
        mx_controlling_terminal_change(parent_pid);
        mx_signals_ignore();
        exit_status = exit_status_func(status, &proc[0], cmd_expression[0]);
    }
    return exit_status;
}

