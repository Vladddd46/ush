#include "ush.h"
/*
 * Replaces tilda expression with
 * $OLDPWD value.
 * in case of unset OLDPWD
 * resolution error caused
 */
void mx_oldpwd_replace(char **arg_splt) {
    char *oldpwd = getenv("OLDPWD");

    if (oldpwd == NULL)
        mx_resolution_error("OLDPWD");
    else {
        free(arg_splt[0]);
        arg_splt[0] = mx_string_copy(oldpwd);
    }
}

