#include "ush.h"

/* 
    * checks, wheather user specified correct option 
        return 1 if False flag
        return 0 if True  flag
*/
static void error_msg(char *option) {
    char *msg  = "env: illegal option "; 
    char *msg1 = "usage: env [-iv] [-P utilpath] [-S string] [-u name]\n";
    char *msg2 = "           [name=value ...] [utility [argument ...]]\n";

    write(2, msg,    mx_strlen(msg));
    write(2, option, mx_strlen(option));
    write(2, "\n", 1);
    write(2, msg1,   mx_strlen(msg1));
    write(2, msg2,   mx_strlen(msg2));
}

int mx_invalid_option_checker(char **cmd) {
    if (cmd[1][0] == '-') {
        if (mx_strcmp("-u", cmd[1]) == 0)
            return 0;
        else if (mx_strcmp("-P", cmd[1]) == 0)
            return 0;
        else if (mx_strcmp("-i", cmd[1]) == 0)
            return 0;
        else {
            error_msg(cmd[1]);
            return 1;
        }
    }
    return 0;
}

