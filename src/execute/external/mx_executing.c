#include "ush.h"

/*
    * executes cmd_expression[0] binary and returns execute status
    * if cmd_expression[0] is std binary => external_path == path
        to it`s binary. otherwise external_path == NULL
        
*/
int mx_executing(char **cmd_expression, char *path) {
    int exe_status = 0;
    char *external_path = mx_find_external_storage_path(cmd_expression[0], path);
    
    if (external_path != NULL)
        exe_status = execv(external_path, cmd_expression);
    else 
        exe_status = execv(cmd_expression[0], cmd_expression);
    return exe_status;
}


