#include "ush.h"
/*
    * replaces tilda expression with
      $HOME value.
    * in case of unset HOME
      resolution error caused
*/
void mx_home_replace(char **arg_splt) {
    char *home = getenv("HOME");

    if (home == NULL)
        mx_resolution_error("HOME");
    else {
        free(arg_splt[0]);
        arg_splt[0] = mx_string_copy(home);
    }
}


