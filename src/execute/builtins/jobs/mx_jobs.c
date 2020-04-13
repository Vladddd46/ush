#include "ush.h"

/*
    implementation of jobs
*/
void mx_jobs(t_proc *proc) {
    t_proc *tmp = proc;
    
    while(tmp) {
        printf("[%d]\t%d\t%s\n", tmp->id, tmp->pid, tmp->proc_name);
        tmp = tmp->next;
    }
}


