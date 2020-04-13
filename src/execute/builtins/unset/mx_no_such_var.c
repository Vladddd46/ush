#include "ush.h"
/*
    * error, which occurs, when user entered:
    >>> unset unexisted_var 
*/
void mx_no_such_var_msg(char *name) {
    char *msg = "unset: not such var:";
    
    write(2, msg, mx_strlen(msg));
    write(2, name, mx_strlen(name));
    write(2, "\n", 1);
}

