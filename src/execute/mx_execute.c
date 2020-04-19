#include "ush.h"
/*
    * checks whether cmd is built in or external and
      executes program.
*/


int mx_execute(char **cmd_expression, t_proc **proc) {
    int status = 1;
    
    if (mx_is_built_in(cmd_expression[0]))
        mx_built_ins_launcher(cmd_expression, &proc[0]);
    else
        status = mx_external(cmd_expression, &proc[0], getenv("PATH"));
    return status;
}


