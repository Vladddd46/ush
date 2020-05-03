#include "ush.h"

/*
 * Changes cwd and refreshes all values 
 * in local enviroment and in enviroment 
 * if PWD or OLDPWD var exists
 */
void mx_cwd_changer(t_local_env **local_env, char *new_cwd, char *old_cwd) {
    mx_local_var_value_resetter(local_env, "PWD", mx_string_copy(new_cwd));
    mx_local_var_value_resetter(local_env, "OLDPWD", mx_string_copy(old_cwd));

    if (getenv("PWD") != NULL)
        setenv("PWD", mx_string_copy(new_cwd), 1);
    if (getenv("OLDPWD") != NULL)
        setenv("OLDPWD", mx_string_copy(old_cwd), 1);
    chdir(new_cwd);
}


