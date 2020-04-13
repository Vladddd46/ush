#include "ush.h"

/*
    * error which occurs, 
      when trying to resolve ~
      but needed env variable is
      not set.

*/
void mx_resolution_error(char *var_name) {
    char *msg  = "u$h> can`t resolve '~' bacause ";
    char *msg2 = " var is not set\n";

    write(2, msg,      mx_strlen(msg));
    write(2, var_name, mx_strlen(var_name));
    write(2, msg2,     mx_strlen(msg2));
}





