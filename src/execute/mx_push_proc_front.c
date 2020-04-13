#include "ush.h"
/*
    * push process in front of process list
*/
static t_proc *create_node(pid_t pid, char *proc_name, int id) {
    t_proc *node = (t_proc *)malloc(sizeof(t_proc));
    node->id = id;
    node->pid = pid;
    node->proc_name = proc_name;
    node->next = NULL;
    return node;
}

void mx_push_proc_front(t_proc **list, pid_t pid, char *proc_name) {
    int id;
    t_proc *node;

    if (*list == NULL)
        *list = create_node(pid, proc_name, 1);
    else {
        id = list[0]->id + 1;
        node = create_node(pid, proc_name, id);
        node -> next = *list;
        *list = node;
    }
}

