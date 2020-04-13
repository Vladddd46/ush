#include "ush.h"
/*
    * Implementation of env built-in
*/

static void flags_resolver(char **cmd, t_proc **proc) {
    if (mx_strcmp("-u", cmd[1]) == 0) {
        mx_env_flag_u(cmd, proc);
        return;
    }
    else if (mx_strcmp("-i", cmd[1]) == 0) {
        mx_env_flag_i(cmd, proc);
        return;
    }
    else if (mx_strcmp("-P", cmd[1]) == 0) {
        mx_env_flag_p(cmd, proc);
        return;
    }
    else
        mx_env_exe(cmd, 1, proc, getenv("PATH"));
}

void mx_env(char **cmd, t_proc **proc) {
    if (mx_strarr_size(cmd) == 1) {
        mx_print_env();
        return;
    }
    // checks wheather flag is valid
    if (mx_invalid_option_checker(cmd))
        return;
    // executes env depending on flags.
    flags_resolver(cmd, proc);
}

