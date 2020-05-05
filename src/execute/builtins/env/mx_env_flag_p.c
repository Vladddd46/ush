#include "ush.h"

// Implementation of flag P in env built in

static void env_printer_wrapper(char **cmd) {
    mx_print_env();
    
    int walker = 3;
    while(cmd[walker]) {
        printf("%s\n", cmd[walker]);
        walker++;
    }
}

void mx_env_flag_p(char **cmd, t_proc **proc, t_local_env **local_env) {
    int binary_index;

    if (mx_strarr_size(cmd) == 2) {
        mx_option_requires_an_argument("P");
        return;
    }
    if (mx_strarr_size(cmd) == 3) {
        mx_print_env();
        return;
    }
    binary_index = mx_binary_index_finder(cmd, 3);
    if (cmd[binary_index]) {
        mx_specified_vars_setter(cmd, 3);
        mx_env_exe(cmd, binary_index, proc, cmd[2], local_env);
        mx_specified_vars_unsetter(cmd, 3);
    }
    else
        env_printer_wrapper(cmd);
}


