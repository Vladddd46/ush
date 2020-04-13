#include "ush.h"
/*
    * replaces tilda expression with
      $PWD value.
    * in case of unset PWD
      resolution error caused
*/
void mx_pwd_replace(char **arg_splt) {
    char *pwd = getenv("PWD");

    if (pwd == NULL)
        mx_resolution_error("PWD");
    else {
        free(arg_splt[0]);
        arg_splt[0] = mx_string_copy(pwd);
    }
}

