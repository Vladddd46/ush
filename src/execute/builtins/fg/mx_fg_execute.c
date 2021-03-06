#include "ush.h"

static void free_node(t_proc **node) {
    if (node[0] != NULL) {
        free(node[0]->proc_name);
        free(node[0]);
    }
}

// Deletes proc_node from list if it`s needed.
static void proc_list_refresh(int status, pid_t pid, t_proc **proc) {
    t_proc *del;
    if (WIFEXITED(status) || WTERMSIG(status) == 2) {
        if (proc[0]->pid == pid) {
            del = proc[0];
            proc[0] = proc[0]->next;
            free_node(&del);
        }
        else  {
            t_proc *tmp = proc[0];
            while(tmp && tmp -> next) {
                if (tmp->next->pid == pid) {
                    del = tmp->next;
                    tmp->next = tmp->next->next;
                    free_node(&del);
                }
                tmp = tmp->next;
            }
        }
    }
}

void mx_fg_execute(pid_t pid, t_proc **proc) {
    int status;
    int pid_2 = getpid();

    /*
     * Changing controlling terminal
     * Sending  CONTINUE signal for process with id <pid>
     * Waiting  for ending/stopping procces with id <pid>
     * Changing back controlling terminal
     */
    mx_controlling_terminal_change(pid);
    kill(pid, SIGCONT);
    waitpid(pid, &status, WUNTRACED);
    mx_controlling_terminal_change(pid_2);
    // Refreshing proc list depending on exit <status> of process.
    proc_list_refresh(status, pid, proc);
}













