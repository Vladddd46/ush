#include "ush.h"

/*
    * finds index of binary name user specified in cmd.
    * skips flags and variables setting in cmd.
*/
int mx_binary_index_finder(char **cmd, int start) {
    int walker = start;

     while (cmd[walker]
         && mx_is_in_arr(cmd[walker], '=') 
         && cmd[walker][mx_strlen(cmd[walker])-1] != '=' 
         && cmd[walker][0] != '=') {
        walker++;
    }
    return walker;
}





