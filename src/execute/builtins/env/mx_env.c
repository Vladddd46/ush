#include "ush.h"
// Implementation of env built-in

static void flags_resolver(char **cmd, t_proc **proc, t_local_env **local_env) {
    if (mx_strcmp("-u", cmd[1]) == 0) {
        mx_env_flag_u(cmd, proc, local_env);
        return;
    }
    else if (mx_strcmp("-i", cmd[1]) == 0) {
        mx_env_flag_i(cmd, proc, local_env);
        return;
    }
    else if (mx_strcmp("-P", cmd[1]) == 0) {
        mx_env_flag_p(cmd, proc, local_env);
        return;
    }
    else
        mx_env_exe(cmd, 1, proc, getenv("PATH"), local_env);
}

void mx_env(char **cmd, t_proc **proc, t_local_env **local_env) {
    if (mx_strarr_size(cmd) == 1) {
        mx_print_env();
        return;
    }
    // Checks wheather flag is valid
    if (mx_invalid_option_checker(cmd))
        return;
    // Executes env depending on flags.
    flags_resolver(cmd, proc, local_env);
}

