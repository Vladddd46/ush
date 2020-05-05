#include "ush.h"

/*
 * Checks whether cmd is built in or external and
 * executes program.
 */
int mx_execute(char **cmd_expression, t_proc **proc, t_local_env **local_env) {
    int status = 1;
    
    if (mx_is_built_in(cmd_expression[0]))
        mx_built_ins_launcher(cmd_expression, &proc[0], local_env);
    else
        status = mx_external(cmd_expression, &proc[0], 
                             getenv("PATH"), local_env);
    return status;
}


