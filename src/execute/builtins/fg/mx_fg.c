#include "ush.h"

// Implementation of fg builtin

static void renew_suspended_process_by_id(t_proc **proc, int id, char *arg) {
    t_proc *tmp = proc[0];
    int found = 1;
    
    while (tmp) {
        if (tmp->id == id) {
            mx_fg_execute(tmp->pid, proc);
            found = 0;
            break;
        }
        tmp = tmp->next;
    }
    // Process with such <id> was not found in proc list.
    if (found)
        mx_no_such_job(arg);
}

static void renew_suspended_process_by_name(t_proc **proc, char *arg) {
    t_proc *tmp = proc[0];
    int found = 1;

    while (tmp) {
        if (mx_strcmp(arg, tmp->proc_name) == 0 
            || arg[0] == tmp->proc_name[0]) {
            mx_fg_execute(tmp->pid, proc);
            found = 0;
            break;
        }
        tmp = tmp->next;
    }
    // Process with such <name> was not found in proc list.
    if (found)
        mx_no_job_found(arg);
}

static void argv_in_proc_list_finder(char *arg, t_proc **proc) {
    int id = atoi(arg);

    if (id == 0 && mx_strcmp(arg, "0") != 0)
        id = -1;
    /* 
     * If id == -1 => searching by job name (str)
     * Else searching by id (int)
     */
    if (id != -1)
        renew_suspended_process_by_id(proc, id, arg);
    else 
        renew_suspended_process_by_name(proc, arg);
}

static void fg_with_args(char **cmd_expr, t_proc **proc) {
    char **res;
    int walker = 1;

    while(cmd_expr[walker]) {
        // Unvalid argument
        if (cmd_expr[walker][0] != '%')
            mx_no_job_found(cmd_expr[walker]);
        else {
            res = mx_str_to_arr(cmd_expr[walker], '%');
            // If "%%%%%%%%%%%" => pure fg is excecuted
            if (res[0] == NULL)
                mx_fg_execute(proc[0]->pid, proc);
            // Finding and excecuting proccess specified by user
            else
                argv_in_proc_list_finder(res[0], proc);
            mx_arr_freesher(res);
        }  
        walker++;
    }
}

void mx_fg(char **command_expression, t_proc **proc) {
    // Process list is empty
    if (mx_no_current_job_err(proc[0]))
        return;
    // Fg with no args
    if (mx_strarr_size(command_expression) == 1) {
        mx_fg_execute(proc[0]->pid, proc);
    }
    else
        fg_with_args(command_expression, &proc[0]);
}





