#include "ush.h"


void mx_command_not_found_msg(char *cmd_name) { 
    char *msg = "u$h: command not found: ";

    write(2, msg, mx_strlen(msg));
    write(2, cmd_name, mx_strlen(cmd_name));
    write(2, "\n", 1);
}




