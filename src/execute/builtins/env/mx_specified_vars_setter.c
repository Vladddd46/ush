#include "ush.h"

/*
    * Env help function.
    * used to putenv() variable user specified in cmd.
*/
void mx_specified_vars_setter(char **cmd, int start) {
    int walker = start;
    /*
        * while condition checks:
         '=' in cmd[walker] 
         && cmd[last_elem]  != '=' 
         && cmd[first_elem] != '='
        * if condition == True
            add expression cmd[walker] ("VAR=VALUE") to enviroment/
    */
    while (cmd[walker]
         && mx_is_in_arr(cmd[walker], '=') 
         && cmd[walker][mx_strlen(cmd[walker])-1] != '=' 
         && cmd[walker][0] != '=') {
        putenv(cmd[walker]);
        walker++;
    }
}



