#include "ush.h"

/*
    * Env help function.
    * used to unsetenv() variable user specified in cmd.
*/
void mx_specified_vars_unsetter(char **cmd, int start) {
    char *var_name;
    int walker = start;
    /*
        * while condition checks:
         '=' in cmd[walker] 
         && cmd[last_elem]  != '=' 
         && cmd[first_elem] != '='
        * if condition == True
            unset var user specified in cmd[walker] ("VAR=VALUE") expression
    */
    while (cmd[walker]
         && mx_is_in_arr(cmd[walker], '=') 
         && cmd[walker][mx_strlen(cmd[walker])-1] != '=' 
         && cmd[walker][0] != '=') {
        var_name = mx_substr_retriever(cmd[walker], 0, 
                                       mx_char_index(cmd[walker], '=') - 1);
        unsetenv(var_name);
        free(var_name);
        walker++;
    }
}


