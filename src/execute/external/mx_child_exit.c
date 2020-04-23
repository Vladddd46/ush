#include "ush.h"

/*
 * Exit from child process depending on 
 * executing status
 */
void mx_child_exit(int exe_status, char **cmd_expression) {
    // If error was occured while excecuting
    if (exe_status < 0) {
        if (errno == 2) 
            mx_command_not_found_msg(cmd_expression[0]);
        else
            perror(cmd_expression[0]);
        exit(errno);
    }
    else
        exit(EXIT_SUCCESS);
}

